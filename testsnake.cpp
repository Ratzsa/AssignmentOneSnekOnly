#include <gtest/gtest.h>

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

extern "C"
{
    #include "game.h"
    #include "config.h"
    #include "main.c"
    #include "analogRead.h"
}

class SnakeTest : public testing::Test
{
protected:
    void SetUp() override
    {
        // initialize
    }
};

TEST_F(SnakeTest,SetUpGameTestGetRandomValueOfZeroToFifteenForXMaxValueTestOnce)
{
    uint8_t x = 0;
    uint8_t y = 0;
    uint8_t tooHigh = 16;

    setUpGame(&x, &y);

    ASSERT_LT(x, tooHigh);
}

TEST_F(SnakeTest,SetUpGameTestGetRandomValueOfZeroToSevenForYMaxValueTestOnce)
{
    uint8_t x = 0;
    uint8_t y = 0;
    uint8_t tooHigh = 7;

    setUpGame(&x, &y);

    ASSERT_LT(y, tooHigh);
}

TEST_F(SnakeTest,SetUpGameTestGetRandomValueOfZeroToFifteenForXMaxValueTestOneHundredTimes)
{
    uint8_t x = 0;
    uint8_t y = 0;
    uint8_t tooHigh = 16;
    bool exceededLimit = false;

    for(int i = 0; i < 100; i++)
    {
        setUpGame(&x, &y);
        if(x >= tooHigh)
        {
            exceededLimit = true;
        }
    }

    ASSERT_FALSE(exceededLimit);
}

TEST_F(SnakeTest,SetUpGameTestGetRandomValueOfZeroToFifteenForYMaxValueTestOneHundredTimes)
{
    uint8_t x = 0;
    uint8_t y = 0;
    uint8_t tooHighX = MAX_COLUMNS;
    uint8_t tooHighY = MAX_ROWS;
    bool exceededLimit = false;

    for(int i = 0; i < 100; i++)
    {
        setUpGame(&x, &y);
        if(y >= tooHighY)
        {
            exceededLimit = true;
        }
    }

    ASSERT_FALSE(exceededLimit);
}