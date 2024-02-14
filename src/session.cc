#include "session.h"

WebSocketSession::WebSocketSession(boost::asio::ip::tcp::socket socket, Logger& logger)
    : socket_(std::move(socket)), ws_(std::move(socket_)), logger_(logger) {}

void WebSocketSession::start() {
    doHandshake();
}

void WebSocketSession::doHandshake() {
    ws_.async_accept(
        [self = shared_from_this()](boost::system::error_code ec) {
            if (!ec) {
                // Handshake successful, start reading
                self->ws_.async_read(
                    self->buffer_,
                    [](boost::system::error_code ec, std::size_t) {
                        if (ec) {
                            // Log read error
                            logger_.log("Read error: " + ec.message());
                        }
                        // Handle message
                    });
            } else {
                // Log handshake error
                logger_.log("Handshake error: " + ec.message());
            }
        });
}
