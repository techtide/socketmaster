#include <iostream>
#include <boost/program_options.hpp>
#include <boost/asio.hpp>
#include "logger.h"
#include "port_manager.h"
#include "WebSocketServer.h"
#include "configuration.h"

namespace po = boost::program_options;

int main(int argc, char* argv[]) {
    try {
        // Declare the supported command-line options
        po::options_description desc("Allowed options");
        desc.add_options()
            ("help", "produce help message")
            ("config", po::value<std::string>(), "set configuration file")
            ("log", po::value<std::string>()->default_value("server.log"), "set log file")
            ("verbose", "enable verbose logging");

        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);

        if (vm.count("help")) {
            std::cout << desc << std::endl;
            return 1;
        }

        // Load configuration from file
        std::string configFilePath;
        if (vm.count("config")) {
            configFilePath = vm["config"].as<std::string>();
        } else {
            std::cerr << "Error: Configuration file not specified" << std::endl;
            return 1;
        }

        Configuration config;
        if (!config.load(configFilePath)) {
            std::cerr << "Error: Failed to load configuration file" << std::endl;
            return 1;
        }

        // Initialize logger
        std::string logFilePath = vm["log"].as<std::string>();
        Logger logger;
        if (!logger.init(logFilePath)) {
            std::cerr << "Error: Failed to initialize logger" << std::endl;
            return 1;
        }

        // Create and initialize port manager
        PortManager portManager;
        if (!portManager.init(config)) {
            std::cerr << "Error: Failed to initialize port manager" << std::endl;
            return 1;
        }

        // Create and start WebSocket server
        boost::asio::io_context io_context;
        WebSocketServer server(io_context, portManager, logger);
        server.start();

        // Run the IO context
        io_context.run();

    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
