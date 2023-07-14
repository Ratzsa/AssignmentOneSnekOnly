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

void setMarker(const uint8_t x, const uint8_t y);
void clearMarker(const uint8_t x, const uint8_t y);
void clearScreen();
void startScreen();


int main()
{
    // Set up joystick
    BIT_CLEAR(DDRD, JOYSTICK_BUTTON);
    BIT_SET(PIND, JOYSTICK_BUTTON);
    BIT_CLEAR(DDRC, JOYSTICK_VERTICAL);
    BIT_CLEAR(DDRC, JOYSTICK_HORIZONTAL);

    // Set up unused pin
    BIT_CLEAR(DDRC, UNUSED_PIN);
    BIT_CLEAR(PIND, UNUSED_PIN);
    
    // Set up serial, display and millis
    init_serial();
	max7219_init();
    millis_init();
    sei();
    

    // Clear screen in preparation for game
    clearScreen();
    _delay_ms(75);

    // Display startScreen, then clear the screen and use the timing when joystick is pressed to seed random
    startScreen();
    clearScreen();
    srand(millis_get());
    
    while(1)
    {        
        snakeGame();
        endScreen();
    }    

    return 0;
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
    bool onStartScreen = true;
    clearScreen();
    _delay_ms(50); // Delay to let the hardware catch up, not sure if necessary.
    setMarker(0,2);
    setMarker(0,3);
    setMarker(0,4);
    setMarker(1,1);
    setMarker(1,5);
    setMarker(2,1);
    setMarker(2,3);
    setMarker(2,5);
    setMarker(3,3);
    setMarker(3,4);
    setMarker(4,2);
    setMarker(4,3);
    setMarker(4,4);
    setMarker(4,5);
    setMarker(5,1);
    setMarker(5,4);
    setMarker(6,1);
    setMarker(6,4);
    setMarker(7,2);
    setMarker(7,3);
    setMarker(7,4);
    setMarker(7,5);
    setMarker(8,1);
    setMarker(8,2);
    setMarker(8,3);
    setMarker(8,4);
    setMarker(8,5);
    setMarker(9,2);
    setMarker(10,3);
    setMarker(11,2);
    setMarker(12,1);
    setMarker(12,2);
    setMarker(12,3);
    setMarker(12,4);
    setMarker(12,5);
    setMarker(13,1);
    setMarker(13,2);
    setMarker(13,3);
    setMarker(13,4);
    setMarker(13,5);    
    setMarker(14,1);
    setMarker(14,3);
    setMarker(14,5);
    setMarker(15,1);
    setMarker(15,5);
    
    while(onStartScreen)
    {
        if(!BIT_CHECK(PIND, JOYSTICK_BUTTON))
        {
            onStartScreen = false;
        }
    }
}

void endScreen()
{
    bool onEndScreen = true;
    clearScreen();
    _delay_ms(50); // Delay to let the hardware catch up, not sure if necessary.
    setMarker(1,1);
    setMarker(1,2);
    setMarker(1,3);
    setMarker(1,4);
    setMarker(1,5);
    setMarker(2,1);
    setMarker(2,3);
    setMarker(2,5);
    setMarker(3,1);
    setMarker(3,3);
    setMarker(3,5);
    setMarker(3,5);
    setMarker(5,1);
    setMarker(5,2);
    setMarker(5,3);
    setMarker(5,4);
    setMarker(5,5);
    setMarker(6,2);
    setMarker(7,3);
    setMarker(8,4);
    setMarker(9,1);
    setMarker(9,2);
    setMarker(9,3);
    setMarker(9,4);
    setMarker(9,5);
    setMarker(11,1);
    setMarker(11,2);
    setMarker(11,3);
    setMarker(11,4);
    setMarker(11,5);
    setMarker(12,1);
    setMarker(12,5);
    setMarker(13,1);
    setMarker(13,5);
    setMarker(14,2);
    setMarker(14,3);
    setMarker(14,4);

    while(onEndScreen)
    {
        if(!BIT_CHECK(PIND, JOYSTICK_BUTTON))
        {
            onEndScreen = false;
        }
    }
}