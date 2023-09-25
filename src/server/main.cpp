#include <iostream>
#include "ServerNetworkHandler.hpp"

int main(int ac, char **av)
{
    if (ac < 2) {
        std::cerr << "Usage: " << av[0] << " <port>" << std::endl;
        return 84;
    }

    try {
        unsigned short port = static_cast<unsigned short>(std::stoi(av[1]));
        Network::ServerNetworkHandler &network = Network::ServerNetworkHandler::getInstance(port);

        std::string exitWord;
        std::cin >> exitWord;

        network.stop();
    } catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    return 0;
}
