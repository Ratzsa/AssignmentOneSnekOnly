#ifndef _CONFIG_SNAKE_GAME
#define _CONFIG_SNAKE_GAME

typedef struct
{
    int8_t snakeX;
    int8_t snakeY;
} SnakeBody;

typedef struct
{
    uint8_t snakeLength;
    SnakeBody bodyPart[128];    
} Snake;

typedef struct
{
    uint8_t foodX;
    uint8_t foodY;
} Food;

#define BIT_SET(a, b) ((a) |= (1ULL << (b)))
#define BIT_CLEAR(a,b) ((a) &= ~(1ULL<<(b)))
#define BIT_FLIP(a,b) ((a) ^= (1ULL<<(b)))
#define BIT_CHECK(a,b) (!!((a) & (1ULL<<(b)))) 

// SET number of LED matrix displays in use. Wokwi simulation uses 2.
// This is used in max72xx.h
#define NUMBER_OF_SEGMENTS 2

// SET MAX_COLUMNS to number of segments times 8.
// 1 segment -> 8, 2 segments -> 16, 3 segments -> 24, 4 segments -> 32, 5 segments -> no, 6 segments -> stop, 7 segments -> what are you doing
#define MAX_COLUMNS 16
#define MAX_ROWS 8
#define ANALOG_HIGH 768
#define ANALOG_LOW 256

#define JOYSTICK_BUTTON 2
#define JOYSTICK_VERTICAL 0
#define JOYSTICK_HORIZONTAL 1

#define MOVE_UP 0
#define MOVE_RIGHT 1
#define MOVE_DOWN 2
#define MOVE_LEFT 3

#define HORIZONTAL_AXIS 0
#define VERTICAL_AXIS 1

#define UNUSED_PIN 3

#endif