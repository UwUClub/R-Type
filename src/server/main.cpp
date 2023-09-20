#include <iostream>
#include "NetworkHandler.hpp"

#define UDP_PORT 13

int main()
{
    try {
        NetworkHandler network = NetworkHandler(UDP_PORT);
        std::string test;
        std::cin >> test;
        // network.send("hello from client");
    } catch (std::exception &e) {
        std::cerr << "[Error]" << e.what() << std::endl;
    }
    return 0;
}
