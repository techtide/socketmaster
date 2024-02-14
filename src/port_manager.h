#ifndef PORT_MANAGER_H
#define PORT_MANAGER_H

#include <string>
#include <unordered_map>
#include "configuration.h"

class PortManager {
public:
    PortManager();

    // Initialize port manager with configuration
    bool init(const Configuration& config);

    // Get the port ID by name
    int getPortId(const std::string& name) const;

    // Get the list of managed ports
    const std::unordered_map<std::string, int>& getPortMap() const;

    const int getPortByName(std::string_view name) const;

    const std::string_view getNameFromPortNumber(int portNumber) const; 

private:
    std::unordered_map<std::string, int> portMap;
};

#endif // PORT_MANAGER_H
