#include "ticker_data.hpp"
#include <gtest/gtest.h>

TEST(TickerDataTest, ParsesValidJson) {
    std::string json_str = R"({
        "type": "ticker",
        "product_id": "BTC-USD",
        "price": "66500.10",
        "best_bid": "66499.99",
        "best_ask": "66500.25",
        "time": "2024-06-18T12:00:00Z"
    })";

    auto result = TickerData::from_json(json_str);
    ASSERT_TRUE(result.has_value());

    TickerData data = *result;
    EXPECT_EQ(data.product_id, "BTC-USD");
    EXPECT_DOUBLE_EQ(data.price, 66500.10);
    EXPECT_DOUBLE_EQ(data.best_bid, 66499.99);
    EXPECT_DOUBLE_EQ(data.best_ask, 66500.25);
    EXPECT_EQ(data.time, "2024-06-18T12:00:00Z");
}

TEST(TickerDataTest, SkipsNonTickerType) {
    std::string json_str = R"({"type": "subscriptions"})";
    auto result = TickerData::from_json(json_str);
    EXPECT_FALSE(result.has_value());
}