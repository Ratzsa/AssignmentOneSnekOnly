#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <util/delay.h>
#include "game.h"
#include "config.h"
#include "millis.h"

void snakeGame(uint8_t *endStatus)
{
    bool inGame = true;
    bool gameIsRunning;
    bool hasMoved = false;
    volatile millis_t timeAtLastMove;
    uint8_t move;
    timeAtLastMove = millis_get();

    clearScreen();

    // GAME SETUP
    SnakeBody snakeHead;
    Snake inGameSnake;
    inGameSnake.snakeLength = 1;

    setUpGame(&snakeHead.snakeX, &snakeHead.snakeY);
    setMarker(snakeHead.snakeX, snakeHead.snakeY);

    if(snakeHead.snakeX > (MAX_COLUMNS / 2))
    {
        move = MOVE_LEFT;
    }
    else
    {
        move = MOVE_RIGHT;
    }

    uint8_t previousMove = HORIZONTAL_AXIS;
    uint16_t timeBetweenMoves = TIME_BETWEEN_MOVES;
    inGameSnake.bodyPart[0] = snakeHead;

    // Setting up the first piece of food
    Food apple = generateFood(&inGameSnake);
    setMarker(apple.foodX, apple.foodY);

    // END OF GAME SETUP

    gameIsRunning = true;
    // volatile millis_t timeAtLastMove = 0;

    while(gameIsRunning)
    {
        // Only checking end game status if snake has moved
        if(hasMoved)
        {
            // LOSE GAME status checks
            if(snakeHead.snakeX < 0 || snakeHead.snakeY < 0 || snakeHead.snakeX >= MAX_COLUMNS || snakeHead.snakeY >= MAX_ROWS)
            {
                gameIsRunning = false;
                inGame = false;
                break;
            }

            for(uint8_t i = 1; i < inGameSnake.snakeLength; i++)
            {
                if((snakeHead.snakeX == inGameSnake.bodyPart[i].snakeX && snakeHead.snakeY == inGameSnake.bodyPart[i].snakeY) && inGameSnake.snakeLength > 1)
                {
                    gameIsRunning = false;
                    inGame = false;
                    break;
                }
            }
            // End of LOSE GAME status checks

            // WIN GAME status check
            if(inGameSnake.snakeLength == MAX_SNAKE_LENGTH)
            {
                *endStatus = 1;
                gameIsRunning = false;
                inGame = false;
                break;
            }
            // End of WIN GAME status check
            hasMoved = false;
        }


        move = setMovement(move, previousMove);

        if(millis_get() - timeAtLastMove > timeBetweenMoves)
        {
            makeMove(move, &snakeHead.snakeX, &snakeHead.snakeY, &previousMove);
            showMove(&inGameSnake, &snakeHead);
            timeAtLastMove = millis_get();
            hasMoved = true;
        }

        if((snakeHead.snakeX == apple.foodX) && (snakeHead.snakeY == apple.foodY))
        {
            inGameSnake.snakeLength += 1;
            apple = generateFood(&inGameSnake);
            _delay_ms(50);
            setMarker(apple.foodX, apple.foodY);

            // Adding a difficulty curve, reducing time between moves after every 5 pieces of food
            if(inGameSnake.snakeLength % 5 == 0)
            {
                timeBetweenMoves -= TIME_BETWEEN_MOVES_REDUCTION;
            }
        }
    }
}

void setUpGame(int8_t *x, int8_t *y)
{
    *x = rand() % MAX_COLUMNS;
    *y = rand() % MAX_ROWS;
}

void makeMove(const uint8_t move, int8_t *x, int8_t *y, uint8_t *previousMove)
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
        fullSnake->bodyPart[i] = fullSnake->bodyPart[i - 1];
    }

    fullSnake->bodyPart[0] = *snakeCurrentHead;
    clearMarker(fullSnake->bodyPart[fullSnake->snakeLength].snakeX, fullSnake->bodyPart[fullSnake->snakeLength].snakeY);
    setMarker(snakeCurrentHead->snakeX, snakeCurrentHead->snakeY);
}

Food generateFood(const Snake *fullSnake)
{
    Food generatedApple;
    bool noCollide = false;
    while(!noCollide)
    {
        generatedApple.foodX = rand() % MAX_COLUMNS;
        generatedApple.foodY = rand() % MAX_ROWS;
        uint8_t checkCollideCounter = 0;
        for(uint8_t i = 0; i < fullSnake->snakeLength; i++)
        {
            if((generatedApple.foodX == fullSnake->bodyPart[i].snakeX) && (generatedApple.foodY == fullSnake->bodyPart[i].snakeY))
            {
                checkCollideCounter++;
            }
        }

        if(checkCollideCounter == 0)
        {
            noCollide = true;
        }
    }

    return generatedApple;
}