#include "ClientHandler.hpp"
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <chrono>
#include <iostream>
#include <string>
#include "ClientGameEvent.hpp"
#include "EwECS/Event/EventManager.hpp"
#include "EwECS/Logger.hpp"
#include "NetworkHandler.hpp"
#include "Packet.hpp"
#include "Values.hpp"

namespace Network {

    using boost::asio::ip::udp;

    ClientHandler::ClientHandler()
        : _resolver(udp::resolver(NetworkHandler::getInstance().getIoService()))
    {}

    void ClientHandler::start(std::string &aHost, std::string &aPort, PacketFactory &aPacketFactory)
    {
        NetworkHandler &network = NetworkHandler::getInstance();
        _serverEndpoint = *_resolver.resolve(udp::v4(), aHost, aPort).begin();

        network.onReceive([this](int8_t aType, IPayload *aPayload, udp::endpoint &aEndpoint) {
            (void) aEndpoint;
            if (aEndpoint == _serverEndpoint) {
                if (aType >= 0 && aType < RType::ClientEventType::MAX_CLI_EVT) {
                    receivePacket(aType, aPayload);
                }
            }
        });

        network.start(udp::v4(), aPacketFactory);
        ECS::Logger::log("Connecting to server");
    }

    void ClientHandler::receivePacket(uint8_t aType, IPayload *aPayload)
    {
        auto packetType = static_cast<RType::ClientEventType>(aType);

        ECS::Event::EventManager::getInstance()->pushEvent<RType::ClientGameEvent>(
            RType::ClientGameEvent(packetType, aPayload));
    }

    void ClientHandler::send(int8_t aType)
    {
        NetworkHandler::getInstance().send(aType, _serverEndpoint);
    }

} // namespace Network
