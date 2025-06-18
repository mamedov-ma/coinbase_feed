#include "ema_calculator.hpp"

#include <gtest/gtest.h>

TEST(EmaCalculatorTest, ComputesCorrectly)
{
    EmaCalculator ema(0.5); // α = 0.5

    ema.add(10);
    EXPECT_TRUE(ema.has_value());
    EXPECT_DOUBLE_EQ(ema.value(), 10.0);

    ema.add(20);
    // EMA = 0.5*20 + 0.5*10 = 15
    EXPECT_DOUBLE_EQ(ema.value(), 15.0);

    ema.add(30);
    // EMA = 0.5*30 + 0.5*15 = 22.5
    EXPECT_DOUBLE_EQ(ema.value(), 22.5);
}