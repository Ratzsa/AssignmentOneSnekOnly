#include <gtest/gtest.h>

extern "C"
{
    #include "game.h"
    #include "config.h"
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
    uint8_t tooHigh = 8;
    bool exceededLimit = false;

    for(int i = 0; i < 100; i++)
    {
        setUpGame(&x, &y);
        if(y >= tooHigh)
        {
            exceededLimit = true;
        }
    }

    ASSERT_FALSE(exceededLimit);
}