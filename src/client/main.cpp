#include <boost/asio.hpp>
#include <iostream>
#include "ClientNetworkHandler.hpp"
// #include "Packets.hpp"
// #include "GameEvent.hpp"

int main()
{
    try {
        Network::ClientNetworkHandler &network = Network::ClientNetworkHandler::getInstance();

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
