#include "csv_logger.hpp"
#include "ema_calculator.hpp"
#include "ticker_data.hpp"

#include <iostream>

#include <ixwebsocket/IXWebSocket.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
    ix::WebSocket ws;
    EmaCalculator ema_price(0.039);
    EmaCalculator ema_mid(0.039);
    CsvLogger logger("../data/log.csv");

    ws.setUrl("wss://ws-feed.exchange.coinbase.com");
    logger.write_header();

    ws.setOnMessageCallback([&](ix::WebSocketMessagePtr const& msg) {
        if (msg->type == ix::WebSocketMessageType::Message)
        {
            auto parsed = TickerData::from_json(msg->str);
            if (parsed)
            {
                auto const& data = *parsed;
                double mid_price = (data.best_bid + data.best_ask) / 2.0;
                ema_price.add(data.price);
                ema_mid.add(mid_price);
                if (ema_price.has_value())
                {
                    logger.log(data.time, data.product_id, data.price,
                        data.best_bid, data.best_ask,
                        mid_price,
                        ema_price.value(), ema_mid.value());
                }
                else
                {
                    std::cout << "Skipping log: EMA not initialized yet\n";
                }
            }
        }
        else if (msg->type == ix::WebSocketMessageType::Open)
        {
            std::cout << "Connected to Coinbase.\n";
            json sub = {
                {"type", "subscribe"},
                {"channels", {{{"name", "ticker"}, {"product_ids", {"BTC-USD"}}}}}};
            ws.send(sub.dump());
        }
    });

    ws.start();

    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}