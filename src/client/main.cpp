#include <boost/asio.hpp>
#include <iostream>
#include "ClientNetworkHandler.hpp"
// #include "Packets.hpp"
// #include "GameEvent.hpp"

int main(int ac, char **av)
{
    if (ac < 3) {
        std::cerr << "Usage: " << av[0] << " <host> <port>" << std::endl;
        return 84;
    }

    try {
        std::string host(av[1]);
        std::string port(av[2]);
        Network::ClientNetworkHandler &network = Network::ClientNetworkHandler::getInstance(host, port);

        // Network::ClientToServerPacket packet = {
        //     Game::ClientEvent::CONNECT
        // };

        network.send(boost::asio::buffer("hello from client"));
        network.send(boost::asio::buffer("hello again from client"));
        network.send(boost::asio::buffer("hello again AGAIN from client"));

        std::string exitWord;
        std::cin >> exitWord;

        network.stop();
    } catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    return 0;
}
