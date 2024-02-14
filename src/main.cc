#include "server.h"
#include "port_manager.h"
#include "configuration.h"
#include "logger.h"

int main() {
    // Load configuration
    Configuration config;
    if (!config.load("config.ini")) {
        // Handle error loading configuration
        return 1;
    }

    // Initialize logger
    Logger logger;
    if (!logger.init(config.getLogFilePath())) {
        // Handle error initializing logger
        return 1;
    }

    // Create port manager
    PortManager portManager;
    if (!portManager.init(config)) {
        // Handle error initializing port manager
        return 1;
    }

    // Start server
    WebSocketServer server(portManager, logger);
    if (!server.start()) {
        // Handle error starting server
        return 1;
    }

    // Wait for termination signal
    server.waitForTermination();

    return 0;
}
