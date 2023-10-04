#include "ServerHandler.hpp"
#include <algorithm>
#include <boost/bind.hpp>
#include <boost/serialization/serialization.hpp>
#include <iostream>
#include "EventManager.hpp"
#include "NetworkHandler.hpp"
#include "Packets.hpp"

namespace Network {

    using boost::asio::ip::udp;

    void ServerHandler::start(std::string &aHost, unsigned short aPort)
    {
        NetworkHandler &network = NetworkHandler::getInstance();
        udp::endpoint endpoint(boost::asio::ip::address::from_string(aHost), aPort);

        network.onReceive([this](const RType::Packet &aPacket, udp::endpoint &aClientEndpoint) {
            receivePacket(aPacket, aClientEndpoint);
        });

        network.start(endpoint.protocol());
        network.bind(endpoint);
        std::cout << "Server " << endpoint << " listening" << std::endl;
    }

    void ServerHandler::receivePacket(const RType::Packet &aPacket, udp::endpoint &aClientEndpoint)
    {
        auto client = std::find_if(_clients.begin(), _clients.end(),
                                   [this, aClientEndpoint](const std::pair<size_t, udp::endpoint> &aPair) {
                                       return aPair.second == aClientEndpoint;
                                   });

        auto packetType = static_cast<RType::ServerEventType>(aPacket.type);

        if (client == _clients.end() && packetType == RType::ServerEventType::CONNECT && _clients.size() < 4) {
            std::cout << "New client connected" << std::endl;
            ECS::Event::EventManager::getInstance()->pushEvent(
                new RType::ServerGameEvent(RType::ServerEventType::CONNECT, 0, aPacket.payload, aClientEndpoint));
        }
        if (client != _clients.end() && packetType != RType::ServerEventType::CONNECT) {
            size_t id = client->first;
            auto *evt = new RType::ServerGameEvent(packetType, id, aPacket.payload, aClientEndpoint);

            ECS::Event::EventManager::getInstance()->pushEvent(evt);
        }
    }

    void ServerHandler::addClient(std::size_t aClientId, udp::endpoint aEndpoint)
    {
        _clients[aClientId] = aEndpoint;
        std::cout << "Player " << aClientId << " joined" << std::endl;
    }

    int ServerHandler::getNumberClients() const
    {
        return _clients.size();
    }

    void ServerHandler::send(const RType::Packet &aPacket, size_t aClientId)
    {
        NetworkHandler::getInstance().send(aPacket, _clients[aClientId]);
    }

    void ServerHandler::broadcast(int aType, std::vector<float> aPayload)
    {
        for (auto &client : _clients) {
            NetworkHandler::getInstance().send(RType::Packet(aType, aPayload), client.second);
        }
    }

} // namespace Network
