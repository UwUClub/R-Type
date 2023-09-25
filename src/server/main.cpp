#include <iostream>
#include "ServerNetworkHandler.hpp"

int main()
{
    try {
        Network::ServerNetworkHandler &network = Network::ServerNetworkHandler::getInstance();

        std::string exitWord;
        std::cin >> exitWord;

        network.stop();
    } catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    return 0;
}
