#include "ServerHandler.hpp"
#include <boost/bind.hpp>
#include <iostream>
#include "EwECS/Event/EventManager.hpp"
#include "NetworkHandler.hpp"
#include "Packets.hpp"
#include "PlayerColor.hpp"
#include "ServerGameEvent.hpp"
#include "Values.hpp"

namespace Network {

    using boost::asio::ip::udp;

    void ServerHandler::start(std::string &aHost, unsigned short aPort)
    {
        NetworkHandler &network = NetworkHandler::getInstance();
        udp::endpoint endpoint(boost::asio::ip::address::from_string(aHost), aPort);

        for (int i = 0; i < MAX_NUMBER_PLAYER; i++) {
            _clientColors[i] = -1;
        }

        network.onReceive([this](const RType::Packet &aPacket, udp::endpoint &aClientEndpoint) {
            if (aPacket.type == AKNOWLEDGMENT_PACKET_TYPE) {
                receiveAknowledgment(aClientEndpoint);
            } else if (aPacket.type == ERROR_PACKET_TYPE) {
                // receive error packet
            } else if (aPacket.type >= 0 && aPacket.type < RType::ServerEventType::MAX_SRV_EVT) {
                receivePacket(aPacket, aClientEndpoint);
            } else {
                NetworkHandler &network = NetworkHandler::getInstance();
                network.send(RType::Packet(ERROR_PACKET_TYPE), aClientEndpoint);
            }
        });

        network.start(endpoint.protocol());
        network.bind(endpoint);
        std::cout << "Server " << endpoint << " listening" << std::endl;
    }

    void ServerHandler::receivePacket(const RType::Packet &aPacket, const udp::endpoint &aClientEndpoint)
    {
        auto client = std::find_if(_clients.begin(), _clients.end(),
                                   [aClientEndpoint](const std::pair<size_t, udp::endpoint> &aPair) {
                                       return aPair.second == aClientEndpoint;
                                   });
        auto packetType = static_cast<RType::ServerEventType>(aPacket.type);

        int entityId = -1;
        if (client != _clients.end()) {
            entityId = client->first;
        }
        ECS::Event::EventManager::getInstance()->pushEvent<RType::ServerGameEvent>(
            RType::ServerGameEvent(packetType, entityId, aPacket.payload, aClientEndpoint));
    }

    void ServerHandler::receiveAknowledgment(const udp::endpoint &aClientEndpoint)
    {
        auto client = std::find_if(_clients.begin(), _clients.end(),
                                   [aClientEndpoint](const std::pair<size_t, udp::endpoint> &aPair) {
                                       return aPair.second == aClientEndpoint;
                                   });
        if (client == _clients.end()) {
            return;
        }
        ECS::Event::EventManager::getInstance()->pushEvent<RType::ServerGameEvent>(
            RType::ServerGameEvent(RType::ServerEventType::AKNOWLEDGMENT, client->first, {}, aClientEndpoint));
    }

    void ServerHandler::addClient(size_t aClientId, const udp::endpoint &aEndpoint)
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

    void ServerHandler::send(const RType::Packet &aPacket, size_t aClientId,
                             ECS::Core::SparseArray<Component::Connection> &aConnection)
    {
        if (aConnection[aClientId].has_value()) {
            aConnection[aClientId].value().status = Network::ConnectionStatus::PENDING;
            NetworkHandler::getInstance().send(aPacket, _clients[aClientId]);
        }
    }

    void ServerHandler::broadcast(int aType, std::vector<float> &aPayload,
                                  ECS::Core::SparseArray<Component::Connection> &aConnection)
    {
        for (auto &client : _clients) {
            if (aConnection[client.first].has_value()) {
                aConnection[client.first].value().status = Network::ConnectionStatus::PENDING;
                NetworkHandler::getInstance().send(RType::Packet(aType, aPayload), client.second);
            }
        }
    }

    bool ServerHandler::isFull() const
    {
        return _clients.size() >= MAX_NUMBER_PLAYER;
    }

} // namespace Network
