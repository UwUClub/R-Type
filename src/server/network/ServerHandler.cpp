#include "ServerHandler.hpp"
#include <boost/bind.hpp>
#include <iostream>
#include "EwECS/Event/EventManager.hpp"
#include "NetworkHandler.hpp"
#include "Packet.hpp"
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

        network.onReceive([this](uint8_t aType, IPayload &aPayload, udp::endpoint &aClientEndpoint) {
            if (aType == AKNOWLEDGMENT_PACKET_TYPE) {
                receiveAknowledgment(aClientEndpoint);
            } else if (aType == ERROR_PACKET_TYPE) {
                // receive error packet
            } else if (aType >= 0 && aType < RType::ServerEventType::MAX_SRV_EVT) {
                receivePacket(aType, aPayload, aClientEndpoint);
            } else {
                NetworkHandler &network = NetworkHandler::getInstance();
                network.send(ERROR_PACKET_TYPE, aClientEndpoint);
            }
        });

        network.start(endpoint.protocol());
        network.bind(endpoint);
        std::cout << "Server " << endpoint << " listening" << std::endl;
    }

    void ServerHandler::receivePacket(uint8_t aType, IPayload &aPayload, const udp::endpoint &aClientEndpoint)
    {
        auto client = std::find_if(_clients.begin(), _clients.end(),
                                   [aClientEndpoint](const std::pair<size_t, udp::endpoint> &aPair) {
                                       return aPair.second == aClientEndpoint;
                                   });
        auto packetType = static_cast<RType::ServerEventType>(aType);

        unsigned short entityId = 0;
        if (client != _clients.end()) {
            entityId = client->first;
        } else if (packetType == RType::ServerEventType::CONNECT) {
            _waitingQueue.push_back(std::make_unique<udp::endpoint>(aClientEndpoint));
        } else {
            return;
        }
        ECS::Event::EventManager::getInstance()->pushEvent<RType::ServerGameEvent>(
            RType::ServerGameEvent(packetType, entityId, &aPayload));
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
            RType::ServerGameEvent(RType::ServerEventType::AKNOWLEDGMENT, client->first, {}));
    }

    void ServerHandler::addClient(unsigned short aClientId)
    {
        if (_waitingQueue.size() > 0) {
            _clients[aClientId] = *_waitingQueue[0];
            _waitingQueue.erase(_waitingQueue.begin());
            std::cout << "Player " << aClientId << " joined" << std::endl;
        }
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

    void ServerHandler::sendError(unsigned short aClientId)
    {
        NetworkHandler &network = NetworkHandler::getInstance();
        network.send(ERROR_PACKET_TYPE, _clients[aClientId]);
    }

    bool ServerHandler::isFull() const
    {
        return _clients.size() >= MAX_NUMBER_PLAYER;
    }

} // namespace Network
