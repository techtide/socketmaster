#include "port_manager.h"

PortManager::PortManager() {}

bool PortManager::init(const Configuration& config) {
    // Initialize port manager with ports from configuration
    const auto& serverConfigs = config.getServerConfigs();
    for (const auto& serverConfig : serverConfigs) {
        portMap.emplace(serverConfig.name, serverConfig.port);
    }
    return true; // Assume initialization is always successful for simplicity
}

int PortManager::getPortId(const std::string& name) const {
    auto it = portMap.find(name);
    if (it != portMap.end()) {
        return it->second;
    }
    return -1; // Not found
}

const std::unordered_map<std::string, int>& PortManager::getPortMap() const {
    return portMap;
}
