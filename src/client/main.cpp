#include <boost/asio.hpp>
#include <iostream>
#include "ClientNetworkHandler.hpp"
// #include "Packets.hpp"
// #include "GameEvent.hpp"

void runClientNetwork(boost::asio::io_service *aIoService)
{
    try {
       Network::ClientNetworkHandler::getInstance(aIoService);
    } catch (std::exception &e) {
        std::cerr << "[Error]" << e.what() << std::endl;
    }
}

int main()
{
    boost::asio::io_service *ioService = new boost::asio::io_service();
    std::thread clientThread(runClientNetwork, ioService);

    // Network::ClientToServerPacket packet = {
    //     Game::ClientEvent::CONNECT
    // };

    // network.send(boost::asio::buffer("hello from client"));
    // network.send(boost::asio::buffer("hello again from client"));
    // network.send(boost::asio::buffer("hello again AGAIN from client"));

    std::string exitWord;
    std::cin >> exitWord;

    ioService->stop();
    clientThread.join();
    return 0;
}
