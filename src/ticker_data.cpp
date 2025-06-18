#include "ticker_data.hpp"
#include <iostream>

using json = nlohmann::json;

std::optional<TickerData> TickerData::from_json(const std::string& raw) {
    try {
        json j = json::parse(raw);

        if (j["type"] != "ticker") return std::nullopt;

        TickerData data;
        data.product_id = j.at("product_id").get<std::string>();
        data.price = std::stod(j.at("price").get<std::string>());
        data.best_bid = std::stod(j.at("best_bid").get<std::string>());
        data.best_ask = std::stod(j.at("best_ask").get<std::string>());
        data.time = j.at("time").get<std::string>();

        return data;
    } catch (const std::exception& e) {
        std::cerr << "[Parse error] " << e.what() << std::endl;
        return std::nullopt;
    }
}