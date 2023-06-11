#include <gtest/gtest.h>

extern "C"
{
    #include "game.h"
}

class SnakeTest : public testing::Test
{
protected:
    void SetUp() override
    {
        // initialize
    }
};

TEST_F(SnakeTest,SetUpGameTestGetRandomValueOfZeroToFifteenForXMaxValue)
{
    uint8_t x = 0;
    uint8_t y = 0;
    uint8_t tooHigh = 16;

    setUpGame(&x, &y);

    ASSERT_LT(x, tooHigh);
}

TEST_F(SnakeTest,SetUpGameTestGetRandomValueOfZeroToSevenForYMaxValue)
{
    uint8_t x = 0;
    uint8_t y = 0;
    uint8_t tooHigh = 7;

    setUpGame(&x, &y);

    ASSERT_LT(y, tooHigh);
}