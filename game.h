#ifndef _GAME_H_SNAKE_
#define _GAME_H_SNAKE_

#include "config.h"

typedef struct
{
    uint8_t snakeX;
    uint8_t snakeY;
} SnakeBody;

typedef struct
{
    uint16_t snakeLength;
    SnakeBody bodyPart[SNAKE_ARRAY_SIZE];
} Snake;

typedef struct
{
    uint8_t foodX;
    uint8_t foodY;
} Food;

void snakeGame(uint8_t *endStatus);
void setUpGame(int8_t *x, int8_t *y);
void makeMove(const uint8_t move, int8_t *x, int8_t *y, uint8_t *previousMove);
uint8_t setMovement(uint8_t move, uint8_t previousMove);
void showMove(Snake *fullSnake, SnakeBody *snakeCurrentHead);
Food generateFood(const Snake *fullSnake);

#endif