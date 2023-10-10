#include "ServerHandler.hpp"
#include <boost/bind.hpp>
#include <boost/serialization/serialization.hpp>
#include <iostream>
#include "EventManager.hpp"
#include "NetworkHandler.hpp"
#include "Packets.hpp"
#include "PlayerColor.hpp"
#include "Values.hpp"

namespace Network {

    using boost::asio::ip::udp;

    void ServerHandler::start(std::string &aHost, unsigned short aPort)
    {
        NetworkHandler &network = NetworkHandler::getInstance();
        udp::endpoint endpoint(boost::asio::ip::address::from_string(aHost), aPort);

        for (int i = 0; i < MAX_NUMBER_PLAYER; i++) {
            _clientColors[i] = RType::PLAYER_COLOR::NONE;
        }

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

    void ServerHandler::addClient(size_t aClientId, udp::endpoint aEndpoint)
    {
        _clients[aClientId] = aEndpoint;
        std::cout << "Player " << aClientId << " joined" << std::endl;
    }

    RType::PLAYER_COLOR ServerHandler::addClientColor(size_t aClientId)
    {
        RType::PLAYER_COLOR color = RType::PLAYER_COLOR::NONE;

        for (int i = 0; i < MAX_NUMBER_PLAYER; i++) {
            color = static_cast<RType::PLAYER_COLOR>(i);
            if (_clientColors[i] == -1) {
                _clientColors[i] = aClientId;
                return color;
            }
        }
        return RType::PLAYER_COLOR::NONE;
    }

    RType::PLAYER_COLOR ServerHandler::getClientColor(size_t aClientId)
    {
        for (int i = 0; i < MAX_NUMBER_PLAYER; i++) {
            if (_clientColors[i] == aClientId) {
                return static_cast<RType::PLAYER_COLOR>(i);
            }
        }
        return RType::PLAYER_COLOR::NONE;
    }

    void ServerHandler::removeClient(size_t aClientId)
    {
        _clients.erase(aClientId);
        for (int i = 0; i < MAX_NUMBER_PLAYER; i++) {
            if (_clientColors[i] == aClientId) {
                _clientColors[i] = -1;
            }
        }
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
