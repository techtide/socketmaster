#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <string>
#include <vector>

struct ServerConfig {
    std::string name;
    int port;
};

class Configuration {
public:
    Configuration();

    // Load configuration from file
    bool load(const std::string& filename);

    // Get server configurations
    const std::vector<ServerConfig>& getServerConfigs() const;

private:
    std::vector<ServerConfig> serverConfigs;
};

#endif // CONFIGURATION_H
