#include "ServerNetworkHandler.hpp"
#include <algorithm>
#include <boost/bind.hpp>
#include <boost/serialization/serialization.hpp>
#include <iostream>
#include "EventManager.hpp"
#include "Packets.hpp"
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>

namespace Network {

    using boost::asio::ip::udp;

    ServerNetworkHandler::ServerNetworkHandler()
        : _socket(_ioService),
          _readBuffer()
    {}

    ServerNetworkHandler::~ServerNetworkHandler()
    {
        for (auto &sender : _senders) {
            sender.second.join();
        }
    }

    void ServerNetworkHandler::start(std::string &aHost, unsigned short aPort)
    {
        boost::asio::ip::udp::endpoint endpoint(boost::asio::ip::address::from_string(aHost), aPort);
        _socket.open(endpoint.protocol());
        _socket.bind(endpoint);
        std::cout << "Server " << endpoint << " listening" << std::endl;
        listen();
    }

    void ServerNetworkHandler::listen()
    {
        _readEndpoint = udp::endpoint();

        _socket.async_receive_from(boost::asio::buffer(_readBuffer), _readEndpoint,
                                   boost::bind(&ServerNetworkHandler::handleRequest, this,
                                               boost::asio::placeholders::error,
                                               boost::asio::placeholders::bytes_transferred));

        if (!_ioThread.joinable()) {
            _ioThread = std::thread(boost::bind(&boost::asio::io_service::run, &_ioService));
        }
    }

    void ServerNetworkHandler::handleRequest(const boost::system::error_code &aError, std::size_t aBytesTransferred)
    {
        (void) aError;
        (void) aBytesTransferred;

        RType::Packet packet;
        RType::unserializePacket<std::array<char, READ_BUFFER_SIZE>>(&packet, _readBuffer);

        std::cout << "Received " << packet.uuid << std::endl;

        if (packet.type == -1) { // receive aknowledgment
            if (_senders.find(packet.uuid) != _senders.end() && _senders[packet.uuid].joinable()) {
                _senders[packet.uuid].join();
                _senders.erase(packet.uuid);
            }
        } else {
            auto client =
                std::find_if(_clients.begin(), _clients.end(), [this](const std::pair<size_t, udp::endpoint> &aPair) {
                    return aPair.second == _readEndpoint;
                });

            auto packetType = static_cast<RType::ServerEventType>(packet.type);

            if (client == _clients.end() && packetType == RType::ServerEventType::CONNECT && _clients.size() < 4) {
                std::cout << "New client connected" << std::endl;
                ECS::Event::EventManager::getInstance()->pushEvent(
                    new RType::ServerGameEvent(RType::ServerEventType::CONNECT, 0, packet.payload, _readEndpoint));

                send(RType::Packet(packet.uuid), _readEndpoint); // send aknowledgment
            }
            if (client != _clients.end() && packetType != RType::ServerEventType::CONNECT) {
                size_t id = client->first;
                auto *evt = new RType::ServerGameEvent(packetType, id, packet.payload, _readEndpoint);

                ECS::Event::EventManager::getInstance()->pushEvent(evt);

                send(RType::Packet(packet.uuid), id); // send aknowledgment
            }
        }
        listen();
    }

    void ServerNetworkHandler::addClient(std::size_t aClientId, udp::endpoint aEndpoint)
    {
        _clients[aClientId] = aEndpoint;
        std::cout << "Player " << aClientId << " joined" << std::endl;
    }

    int ServerNetworkHandler::getNumberClients() const
    {
        return _clients.size();
    }

    void ServerNetworkHandler::send(const RType::Packet &aPacket, size_t aClientId)
    {
        udp::endpoint clientEndpoint = _clients[aClientId];
        send(aPacket, clientEndpoint);
    }

    void ServerNetworkHandler::send(const RType::Packet &aPacket, udp::endpoint aClientEndpoint)
    {
        _senders[aPacket.uuid] = std::thread([this, aPacket, aClientEndpoint]() {
            try {
                boost::asio::streambuf buf;
                RType::serializePacket(&buf, aPacket);

                _socket.send_to(buf.data(), aClientEndpoint);
            } catch (std::exception &e) {
                std::cerr << "ClientNetworkHandler send error: " << e.what() << std::endl;
            }
        });
    }

    void ServerNetworkHandler::broadcast(int aType, std::vector<float> aPayload)
    {
        for (auto &client : _clients) {
            send(RType::Packet(aType, aPayload), client.first);
        }
    }

    void ServerNetworkHandler::stop()
    {
        _ioService.stop();
        _socket.close();
        if (_ioThread.joinable()) {
            _ioThread.join();
        }
    }

} // namespace Network
