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
    volatile millis_t timeAtNewPart;
    // uint8_t x = 0;
    // uint8_t y = 0;
    uint8_t move;
    timeAtLastMove = millis_get();
    timeAtNewPart = millis_get();

    clearScreen();    

    while(inGame)
    {
        // GAME SETUP
        SnakeBody snakeHead;
        Snake inGameSnake;
        inGameSnake.snakeLength = 1;
        setUpGame(&snakeHead.snakeX, &snakeHead.snakeY);
        setMarker(snakeHead.snakeX, snakeHead.snakeY);
        if(snakeHead.snakeX > 8)
        {
            move = MOVE_LEFT;
        }
        else
        {
            move = MOVE_RIGHT;
        }
        uint8_t previousMove = HORIZONTAL_AXIS;
        uint16_t timeBetweenMoves = 1250;
        inGameSnake.bodyPart[0] = snakeHead;
        Food apple;
        // END OF GAME SETUP

        gameIsRunning = true;
        volatile millis_t timeAtLastMove = 0;

        while(gameIsRunning)
        {
            // END GAME status checks
            if(snakeHead.snakeX == -1 || snakeHead.snakeY == -1 || snakeHead.snakeX == MAX_COLUMNS || snakeHead.snakeY == MAX_ROWS)
            {
                gameIsRunning = false;
                inGame = false;
            }

            for(uint8_t i = 1; i < inGameSnake.snakeLength; i++)
            {
                if((snakeHead.snakeX == inGameSnake.bodyPart[i].snakeX && snakeHead.snakeY == inGameSnake.bodyPart[i].snakeY) && inGameSnake.snakeLength > 1)
                {
                    gameIsRunning = false;
                    inGame = false;
                }
            }
            // End of END GAME status checks

            move = setMovement(move, previousMove);

            if(millis_get() - timeAtLastMove > timeBetweenMoves)
            {
                makeMove(move, &snakeHead.snakeX, &snakeHead.snakeY, &previousMove);
                showMove(&inGameSnake, &snakeHead);
                timeAtLastMove = millis_get();
            }

            if(millis_get() - timeAtNewPart > 7500)
            {
                inGameSnake.snakeLength++;
                timeAtNewPart = millis_get();
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

void showMove(Snake *fullSnake, SnakeBody *snakeCurrentHead)
{
    for(uint8_t i = fullSnake->snakeLength; i > 0; i--)
    {
        fullSnake->bodyPart[i] = fullSnake->bodyPart[i-1];
    }

    fullSnake->bodyPart[0] = *snakeCurrentHead;
    clearMarker(fullSnake->bodyPart[fullSnake->snakeLength].snakeX, fullSnake->bodyPart[fullSnake->snakeLength].snakeY);
    setMarker(snakeCurrentHead->snakeX, snakeCurrentHead->snakeY);
}