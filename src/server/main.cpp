#include <iostream>
#include "ServerNetworkHandler.hpp"

void runServerNetwork(boost::asio::io_service *aIoService)
{
    try {
        Network::ServerNetworkHandler &network = Network::ServerNetworkHandler::getInstance(aIoService);
        (void) network;
    } catch (std::exception &e) {
        std::cerr << "[Error]" << e.what() << std::endl;
    }
}

int main()
{
    boost::asio::io_service *ioService = new boost::asio::io_service(); 
    std::thread serverThread(runServerNetwork, ioService);

    std::string exitWord;
    std::cin >> exitWord;
    
    ioService->stop();
    serverThread.join();
    return 0;
}
