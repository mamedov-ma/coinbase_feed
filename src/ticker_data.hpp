#pragma once
#include <optional>
#include <string>

#include <nlohmann/json.hpp>

struct TickerData
{
    std::string product_id;
    double price;
    double best_bid;
    double best_ask;
    std::string time;

    static std::optional<TickerData> from_json(std::string const& raw);
};