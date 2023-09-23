#include <iostream>
#include "ServerNetworkHandler.hpp"

int main()
{
    try {
        ServerNetworkHandler &srv = ServerNetworkHandler::getInstance();
        (void) srv;
        std::string exitWord;
        std::cin >> exitWord;
        // network.send("hello from client");
    } catch (std::exception &e) {
        std::cerr << "[Error]" << e.what() << std::endl;
    }
    return 0;
}
