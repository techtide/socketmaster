#include "logger.h"

Logger::Logger() {}

Logger::~Logger() {
    if (outFile.is_open()) {
        outFile.close();
    }
}

bool Logger::init(const std::string& filePath) {
    outFile.open(filePath, std::ios::app);
    if (!outFile.is_open()) {
        std::cerr << "Error: Failed to open log file: " << filePath << std::endl;
        return false;
    }
    return true;
}

void Logger::log(const std::string& message) {
    if (outFile.is_open()) {
        outFile << message << std::endl;
    }
}
