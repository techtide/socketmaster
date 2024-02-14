#include "server.h"

WebSocketServer::WebSocketServer(boost::asio::io_context& io_context, PortManager& portManager, Logger& logger)
    : io_context_(io_context), portManager_(portManager), logger_(logger) {}

void WebSocketServer::start() {
    // Get the ports managed by the PortManager
    const auto& ports = portManager_.getPortMap();

    // Create an acceptor for each port
    for (auto kv : ports) {
        std::string_view name = kv.first;
        int port = kv.second;
        boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), port);
        boost::asio::ip::tcp::acceptor acceptor(io_context_, endpoint);
        acceptors_.push_back(std::move(acceptor));
    }

    // Start accepting connections
    for (auto& acceptor : acceptors_) {
        doAccept();
    }
}

void WebSocketServer::stop() {
    for (auto& acceptor : acceptors_) {
        acceptor.close();
    }
}

void WebSocketServer::doAccept() {
    for (auto& acceptor : acceptors_) {
        acceptor.async_accept(
            [this](boost::system::error_code ec, boost::asio::ip::tcp::socket socket) {
                if (!ec) {
                    // Log connection
                    logger_.log("Accepted connection from " + socket.remote_endpoint().address().to_string());
                    
                    // Create a WebSocket session and start it
                    std::make_shared<WebSocketSession>(std::move(socket))->start();
                } else {
                    logger_.log("Accept error: " + ec.message());
                }

                // Continue accepting connections
                doAccept();
            });
    }
}
