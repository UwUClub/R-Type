#include <iostream>
#include "NetworkHandler.hpp"

int main()
{
    try {
        NetworkHandler::getInstance();
        std::string test;
        std::cin >> test;
        // network.send("hello from client");
    } catch (std::exception &e) {
        std::cerr << "[Error]" << e.what() << std::endl;
    }
    return 0;
}
