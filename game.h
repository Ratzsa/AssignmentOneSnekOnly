#ifndef _GAME_H_SNAKE_
#define _GAME_H_SNAKE_

void snakeGame();
void setUpGame(uint8_t *x, uint8_t *y);
void makeMove(const uint8_t move, uint8_t *x, uint8_t *y, uint8_t *previousMove);
uint8_t setMovement(uint8_t move, uint8_t previousMove);

#endif