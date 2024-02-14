#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>
#include <iostream>

class Logger {
public:
    Logger();
    ~Logger();

    // Initialize logger with log file path
    bool init(const std::string& filePath);

    // Log a message
    void log(const std::string& message);

private:
    std::ofstream outFile;
};

#endif // LOGGER_H
