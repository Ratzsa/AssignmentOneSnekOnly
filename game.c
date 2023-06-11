#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
// #include "uart.h"
// #include "max72xx.h"
// #include "analogRead.h"
// #include <util/delay.h>
#include <stdbool.h>
#include <time.h>
#include "game.h"

void setUpGame(uint8_t *x, uint8_t *y)
{
    *x = rand() % MAX_COLUMNS;
    *y = rand() % MAX_ROWS;
}