#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "game.h"
#include "config.h"
#include "millis.h"

void snakeGame()
{
    bool inGame = true;
    bool gameIsRunning;

    volatile millis_t timeAtLastMove;
    uint8_t x = 0;
    uint8_t y = 0;
    uint8_t move;
    timeAtLastMove = millis_get();

    while(inGame)
    {
        // GAME SETUP
        setUpGame(&x, &y);
        setMarker(x, y);
        if(x < 7)
        {
            move = MOVE_LEFT;
        }
        else
        {
            move = MOVE_RIGHT;
        }
        uint8_t previousMove = HORIZONTAL_AXIS;
        uint16_t timeBetweenMoves = 1250;
        // END OF GAME SETUP

        gameIsRunning = true;
        volatile millis_t timeAtLastMove = 0;

        while(gameIsRunning)
        {
            move = setMovement(move, previousMove);

            if(millis_get() - timeAtLastMove > timeBetweenMoves)
            {
                makeMove(move, &x, &y, &previousMove);
                timeAtLastMove = millis_get();
                clearScreen();
                setMarker(x, y);
            }
        }
    }
}

void setUpGame(uint8_t *x, uint8_t *y)
{
    *x = rand() % MAX_COLUMNS;
    *y = rand() % MAX_ROWS;
}

void makeMove(const uint8_t move, uint8_t *x, uint8_t *y, uint8_t *previousMove)
{
    switch(move)
    {
        case MOVE_UP:
            (*y)--;
            *previousMove = VERTICAL_AXIS;
            break;

        case MOVE_RIGHT:
            (*x)++;
            *previousMove = HORIZONTAL_AXIS;
            break;

        case MOVE_DOWN:
            (*y) ++;
            *previousMove = VERTICAL_AXIS;
            break;

        case MOVE_LEFT:
            (*x)--;
            *previousMove = HORIZONTAL_AXIS;
            break;

        default:
            break;
    }
}

uint8_t setMovement(uint8_t move, uint8_t previousMove)
{
    int16_t horizontalMove = analogRead(JOYSTICK_HORIZONTAL);
    int16_t verticalMove = analogRead(JOYSTICK_VERTICAL);

    // Set movement
    if(horizontalMove < ANALOG_LOW && previousMove == VERTICAL_AXIS)
    {
        move = MOVE_RIGHT;
    }

    if(horizontalMove > ANALOG_HIGH && previousMove == VERTICAL_AXIS)
    {
        move = MOVE_LEFT;
    }

    if(verticalMove < ANALOG_LOW && previousMove == HORIZONTAL_AXIS)
    {
        move = MOVE_DOWN;
    }

    if(verticalMove > ANALOG_HIGH && previousMove == HORIZONTAL_AXIS)
    {
        move = MOVE_UP;
    }

    return move;        
}