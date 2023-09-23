#include <boost/asio.hpp>
#include <iostream>
#include "ClientNetworkHandler.hpp"
// #include "Packets.hpp"
// #include "GameEvent.hpp"

int main()
{
    try {
        Network::ClientNetworkHandler &network = Network::ClientNetworkHandler::getInstance();

        // boost::array<char, 1> buffer  = {{ 0 }};

        network.send(boost::asio::buffer("hello from client"));
        network.send(boost::asio::buffer("hello again from client"));
        network.send(boost::asio::buffer("hello again AGAIN from client"));

        // Network::ClientToServerPacket packet = {
        //     Game::ClientEvent::CONNECT
        // };

        std::string exitWord;
        std::cin >> exitWord;
    } catch (std::exception &e) {
        std::cerr << "[Error]" << e.what() << std::endl;
    }
    return 0;
}
