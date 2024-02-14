#ifndef WEBSOCKET_SERVER_H
#define WEBSOCKET_SERVER_H

#include <boost/asio.hpp>
#include "port_manager.h"
#include "logger.h"

class WebSocketServer {
public:
    WebSocketServer(boost::asio::io_context& io_context, PortManager& portManager, Logger& logger);

    // Start the WebSocket server
    void start();

    // Stop the WebSocket server
    void stop();

private:
    void doAccept();

    boost::asio::io_context& io_context_;
    PortManager& portManager_;
    Logger& logger_;
    std::vector<boost::asio::ip::tcp::acceptor> acceptors_;
};

#endif // WEBSOCKET_SERVER_H
