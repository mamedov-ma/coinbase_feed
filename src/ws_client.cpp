#include "ws_client.hpp"
#include <iostream>
#include <nlohmann/json.hpp>
#include <boost/asio/connect.hpp>
#include <boost/beast/websocket.hpp>

using tcp = boost::asio::ip::tcp;
namespace websocket = boost::beast::websocket;
namespace ssl = boost::asio::ssl;
using json = nlohmann::json;

WebSocketClient::WebSocketClient()
    : ssl_ctx_(ssl::context::tlsv12_client),
      resolver_(ioc_),
      ws_(ioc_, ssl_ctx_),
      running_(false) {
    ssl_ctx_.set_verify_mode(ssl::verify_none);
}

WebSocketClient::~WebSocketClient() {
    stop();
}

void WebSocketClient::run() {
    running_ = true;
    listener_thread_ = std::thread([this]() { connect(); });
}

void WebSocketClient::stop() {
    running_ = false;
    ioc_.stop();
    if (listener_thread_.joinable()) {
        listener_thread_.join();
    }
}

void WebSocketClient::connect() {
    try {
        auto const results = resolver_.resolve("echo.websocket.events", "443");
        ws_.handshake("echo.websocket.events", "/");

        // SSL handshake
        ws_.next_layer().handshake(boost::asio::ssl::stream_base::client);

        ws_.set_option(websocket::stream_base::decorator(
            [](websocket::request_type& req) {
                req.set(boost::beast::http::field::host, "ws-feed.exchange.coinbase.com");
                req.set(boost::beast::http::field::user_agent, "Mozilla/5.0 (CoinbaseHFTBot)");
                req.set(boost::beast::http::field::upgrade, "websocket");
                req.set(boost::beast::http::field::connection, "Upgrade");
                req.set("Sec-WebSocket-Version", "13");
            }
        ));

        ws_.handshake("ws-feed.exchange.coinbase.com", "/");
        std::cout << "WebSocket connected & handshake successful.\n";
        json sub_msg = {
            {"type", "subscribe"},
            {"channels", {{{"name", "ticker"}, {"product_ids", {"BTC-USD"}}}}}
        };
        ws_.write(boost::asio::buffer(sub_msg.dump()));

        listen();
    } catch (const std::exception& ex) {
        std::cerr << "WebSocket connect error: " << ex.what() << std::endl;
    }
}

void WebSocketClient::listen() {
    boost::beast::flat_buffer buffer;

    while (running_) {
        try {
            ws_.read(buffer);
            std::string message = boost::beast::buffers_to_string(buffer.data());
            std::cout << "Received: " << message << std::endl;
            buffer.consume(buffer.size());
        } catch (const std::exception& ex) {
            std::cerr << "WebSocket read error: " << ex.what() << std::endl;
            break;
        }
    }
}