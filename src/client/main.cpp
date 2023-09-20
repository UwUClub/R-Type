#include <boost/asio.hpp>
#include <iostream>
#include "NetworkHandler.hpp"

int main(int argc, char *argv[])
{
    if (argc != 2) {
        std::cerr << "Usage: client <host>" << std::endl;
        return 1;
    }
    try {
        NetworkHandler network = NetworkHandler(argv[1]);
        // network.run(argv[1]);
        network.send(boost::asio::buffer("hello from client"));
        network.send(boost::asio::buffer("hello again from client"));
        network.send(boost::asio::buffer("hello again AGAIN from client"));
    } catch (std::exception &e) {
        std::cerr << "[Error]" << e.what() << std::endl;
    }
    return 0;
}
