#include <stdio.h>
#include <stdint.h>
#include "uart.h"
#include "max72xx.h"
#include "analogRead.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include "game.h"
#include "millis.h"
#include "config.h"

void initSnake();
void setMarker(const uint8_t x, const uint8_t y);
void clearMarker(const uint8_t x, const uint8_t y);
void clearScreen();
void startScreen();
void setArray(uint8_t textArray[DRAW_X][DRAW_Y]);
void buttonClick();

int main()
{
    // Initialization
    initSnake();
    // Get timing of joystick button input for random seed
    srand(millis_get());

    uint8_t endStatus = 0;

    while(1)
    {
        endStatus = 0;
        snakeGame(&endStatus);
        if(endStatus == 1)
        {
            winScreen();
        }
        else
        {
            endScreen();
        }
    }

    return 0;
}

void initSnake()
{
    // Set up joystick
    BIT_CLEAR(DDRD, JOYSTICK_BUTTON);
    BIT_SET(PIND, JOYSTICK_BUTTON);
    BIT_CLEAR(DDRC, JOYSTICK_VERTICAL);
    BIT_CLEAR(DDRC, JOYSTICK_HORIZONTAL);

    // Set up serial, display and millis
    init_serial();
	max7219_init();
    millis_init();
    sei();

    // Clear screen in preparation for game
    clearScreen();
    _delay_ms(75);

    // Display startScreen, then clear the screen
    startScreen();
    clearScreen();
}

// Sets a specific LED
void setMarker(const uint8_t x, const uint8_t y)
{
    max7219b_set(x, y);
    max7219b_out();
}

// Clears a specific LED
void clearMarker(const uint8_t x, const uint8_t y)
{
    max7219b_clr(x, y);
    max7219b_out();
}

void clearScreen()
{
    for(int x = 0; x < MAX_COLUMNS; x++)
    {
        for(int y = 0; y < MAX_ROWS; y++)
        {
            max7219b_clr(x, y);
            max7219b_out();
        }
    }
}

void startScreen()
{
    uint8_t startText[DRAW_X][DRAW_Y] = {{0, 0, 1, 1, 1, 0, 0, 0},
                                         {0, 1, 0, 0, 0, 1, 0, 0},
                                         {0, 1, 0, 1, 0, 1, 0, 0},
                                         {0, 0, 0, 1, 1, 0, 0, 0},
                                         {0, 0, 1, 1, 1, 1, 0, 0},
                                         {0, 1, 0, 0, 1, 0, 0, 0},
                                         {0, 1, 0, 0, 1, 0, 0, 0},
                                         {0, 0, 1, 1, 1, 1, 0, 0},
                                         {0, 1, 1, 1, 1, 1, 0, 0},
                                         {0, 0, 1, 0, 0, 0, 0, 0},
                                         {0, 0, 0, 1, 0, 0, 0, 0},
                                         {0, 0, 1, 0, 0, 0, 0, 0},
                                         {0, 1, 1, 1, 1, 1, 0, 0},
                                         {0, 1, 1, 1, 1, 1, 0, 0},
                                         {0, 1, 0, 1, 0, 1, 0, 0},
                                         {0, 1, 0, 0, 0, 1, 0, 0}};
    clearScreen();
    _delay_ms(50); // Delay to let the hardware catch up, not sure if necessary.

    setArray(startText);

    buttonClick();
}

void endScreen()
{
    uint8_t endText[DRAW_X][DRAW_Y] =  {{0, 0, 0, 0, 0, 0, 0, 0},
                                        {0, 1, 1, 1, 1, 1, 0, 0},
                                        {0, 1, 0, 1, 0, 1, 0, 0},
                                        {0, 1, 0, 1, 0, 1, 0, 0},
                                        {0, 0, 0, 0, 0, 0, 0, 0},
                                        {0, 1, 1, 1, 1, 1, 0, 0},
                                        {0, 0, 1, 0, 0, 0, 0, 0},
                                        {0, 0, 0, 1, 0, 0, 0, 0},
                                        {0, 0, 0, 0, 1, 0, 0, 0},
                                        {0, 1, 1, 1, 1, 1, 0, 0},
                                        {0, 0, 0, 0, 0, 0, 0, 0},
                                        {0, 1, 1, 1, 1, 1, 0, 0},
                                        {0, 1, 0, 0, 0, 1, 0, 0},
                                        {0, 1, 0, 0, 0, 1, 0, 0},
                                        {0, 0, 1, 1, 1, 0, 0, 0},
                                        {0, 0, 0, 0, 0, 0, 0, 0}};
    clearScreen();
    _delay_ms(50); // Delay to let the hardware catch up, not sure if necessary.

    setArray(endText);

    buttonClick();
}

void winScreen()
{
    uint8_t winText[DRAW_X][DRAW_Y] =  {{0, 0, 0, 0, 0, 0, 0, 0},
                                        {0, 1, 1, 1, 1, 0, 0, 0},
                                        {0, 0, 0, 0, 0, 1, 0, 0},
                                        {0, 0, 1, 1, 1, 0, 0, 0},
                                        {0, 0, 0, 0, 0, 1, 0, 0},
                                        {0, 1, 1, 1, 1, 0, 0, 0},
                                        {0, 0, 0, 0, 0, 0, 0, 0},
                                        {0, 1, 1, 1, 1, 1, 0, 0},
                                        {0, 0, 0, 0, 0, 0, 0, 0},
                                        {0, 1, 1, 1, 1, 1, 0, 0},
                                        {0, 0, 1, 0, 0, 0, 0, 0},
                                        {0, 0, 0, 1, 0, 0, 0, 0},
                                        {0, 0, 0, 0, 1, 0, 0, 0},
                                        {0, 1, 1, 1, 1, 1, 0, 0},
                                        {0, 0, 0, 0, 0, 0, 0, 0},
                                        {0, 1, 1, 1, 0, 1, 0, 0}};
    clearScreen();
    _delay_ms(50); // Delay to let the hardware catch up, not sure if necessary.

    setArray(winText);

    buttonClick();
}

void setArray(uint8_t textArray[DRAW_X][DRAW_Y])
{
    for(uint8_t x = 0; x < DRAW_X; x++)
    {
        for(uint8_t y = 0; y < DRAW_Y; y++)
        {
            if(textArray[x][y] == 1)
            {
                setMarker(x, y);
            }
        }
    }
}

void buttonClick()
{
    while(BIT_CHECK(PIND, JOYSTICK_BUTTON))
    {
        // Hi, this is at the bottom of the file!
    }
}