#include "ClientNetworkHandler.hpp"
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include <string>
#include "EventManager.hpp"
#include "Packets.hpp"

namespace Network {

    using boost::asio::ip::udp;

    ClientNetworkHandler::~ClientNetworkHandler()
    {
        for (auto &sender : _senders) {
            sender.second.join();
        }
    }

    void ClientNetworkHandler::start(std::string &aHost, std::string &aPort)
    {
        _serverEndpoint = *_resolver.resolve(udp::v4(), aHost, aPort).begin();
        _socket.open(udp::v4());
        std::cout << "Connected to " << _serverEndpoint << std::endl;
        listen();
    }

    void ClientNetworkHandler::listen()
    {
        _socket.async_receive_from(boost::asio::buffer(_readBuffer), _serverEndpoint,
                                   boost::bind(&ClientNetworkHandler::handleRequest, this,
                                               boost::asio::placeholders::error,
                                               boost::asio::placeholders::bytes_transferred));

        if (!_ioThread.joinable()) {
            _ioThread = std::thread(boost::bind(&boost::asio::io_service::run, &_ioService));
        }
    }

    void ClientNetworkHandler::handleRequest(const boost::system::error_code &aError, std::size_t aBytesTransferred)
    {
        (void) aError;
        (void) aBytesTransferred;

        RType::Packet packet;
        RType::unserializePacket<std::array<char, READ_BUFFER_SIZE>>(&packet, _readBuffer);

        if (packet.type == -1) { // receive aknowledgment
            if (_senders.find(packet.uuid) != _senders.end() && _senders[packet.uuid].joinable()) {
                _senders[packet.uuid].join();
                _senders.erase(packet.uuid);
            }
        } else {
            RType::ClientEventType packetType = static_cast<RType::ClientEventType>(packet.type);

            auto *evt = new RType::ClientGameEvent(packetType, packet.payload);
            ECS::Event::EventManager::getInstance()->pushEvent(evt);

            send(RType::Packet(packet.uuid)); // send aknowledgment
        }

        listen();
    }

    void ClientNetworkHandler::send(const RType::Packet &aPacket)
    {
        _senders[aPacket.uuid] = std::thread([this, aPacket]() {
            try {
                boost::asio::streambuf buf;
                RType::serializePacket(&buf, aPacket);
                _socket.send_to(buf.data(), _serverEndpoint);
            } catch (std::exception &e) {
                std::cerr << "ClientNetworkHandler send error: " << e.what() << std::endl;
            }
        });
    }

    void ClientNetworkHandler::stop()
    {
        _ioService.stop();
        if (_ioThread.joinable()) {
            _ioThread.join();
        }
    }

} // namespace Network
