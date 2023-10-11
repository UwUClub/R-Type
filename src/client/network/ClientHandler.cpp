#include "ClientHandler.hpp"
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <chrono>
#include <iostream>
#include <string>
#include "EventManager.hpp"
#include "NetworkHandler.hpp"
#include "Packets.hpp"

namespace Network {

    using boost::asio::ip::udp;

    ClientHandler::ClientHandler()
        : _resolver(udp::resolver(NetworkHandler::getInstance().getIoService()))
    {}

    void ClientHandler::start(std::string &aHost, std::string &aPort)
    {
        NetworkHandler &network = NetworkHandler::getInstance();
        _serverEndpoint = *_resolver.resolve(udp::v4(), aHost, aPort).begin();

        network.onReceive([this](const RType::Packet &aPacket, udp::endpoint &aEndpoint) {
            (void) aEndpoint;

            if (aEndpoint == _serverEndpoint) {
                receivePacket(aPacket);
            }
        });

        network.onReceiveAknowledgment([this](const std::string &aUuid, udp::endpoint &aEndpoint) {
            (void) aUuid;
            (void) aEndpoint;
        });

        network.start(udp::v4());
        std::cout << "Connected to " << _serverEndpoint << std::endl;
    }

    void ClientHandler::receivePacket(const RType::Packet &aPacket)
    {
        RType::ClientEventType packetType = static_cast<RType::ClientEventType>(aPacket.type);

        auto *evt = new RType::ClientGameEvent(packetType, aPacket.payload);
        ECS::Event::EventManager::getInstance()->pushEvent(evt);
    }

    void ClientHandler::send(RType::Packet &aPacket)
    {
        NetworkHandler::getInstance().send(aPacket, _serverEndpoint);
    }

} // namespace Network
