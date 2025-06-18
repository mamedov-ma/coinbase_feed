#pragma once
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/context.hpp>
#include <string>
#include <thread>
#include <atomic>

class WebSocketClient {
public:
    WebSocketClient();
    ~WebSocketClient();

    void run();
    void stop();

private:
    void connect();
    void listen();

    boost::asio::io_context ioc_;
    boost::asio::ssl::context ssl_ctx_;
    boost::asio::ip::tcp::resolver resolver_;
    boost::beast::websocket::stream<boost::beast::ssl_stream<boost::asio::ip::tcp::socket>> ws_;
    std::thread listener_thread_;
    std::atomic<bool> running_;
};