#pragma once
#include <string>
#include <optional>
#include <nlohmann/json.hpp>

struct TickerData {
    std::string product_id;
    double price;
    double best_bid;
    double best_ask;
    std::string time;

    static std::optional<TickerData> from_json(const std::string& raw);
};