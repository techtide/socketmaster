#ifndef WEBSOCKET_SESSION_H
#define WEBSOCKET_SESSION_H

#include <boost/beast.hpp>
#include <boost/asio.hpp>
#include <memory>
#include "logger.h"

class WebSocketSession : public std::enable_shared_from_this<WebSocketSession> {
public:
    explicit WebSocketSession(boost::asio::ip::tcp::socket socket, Logger& logger);

    // Start the WebSocket session
    void start();

private:
    void doHandshake();

    boost::beast::websocket::stream<boost::asio::ip::tcp::socket> ws_;
    boost::asio::ip::tcp::socket socket_;
    boost::beast::flat_buffer buffer_;
    Logger& logger_;
};

#endif // WEBSOCKET_SESSION_H
