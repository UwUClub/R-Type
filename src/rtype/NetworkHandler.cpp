#include "NetworkHandler.hpp"
#include <boost/bind.hpp>
#include <chrono>
#include <iostream>
#include <string>
#include "EventManager.hpp"
#include "Packets.hpp"
#include <boost/archive/binary_iarchive.hpp>

namespace Network {

    using boost::asio::ip::udp;

    void NetworkHandler::start(const boost::asio::basic_socket<boost::asio::ip::udp>::protocol_type &aProtocol)
    {
        _socket.open(aProtocol);
        listen();
    }

    void NetworkHandler::bind(const udp::endpoint &aEndpoint)
    {
        _socket.bind(aEndpoint);
    }

    void NetworkHandler::onReceive(std::function<void(const RType::Packet &, udp::endpoint &)> aOnReceive)
    {
        _onReceive = aOnReceive;
    }

    void NetworkHandler::onReceiveAknowledgment(
        std::function<void(const std::string &, udp::endpoint &)> aOnReceiveAknowledgment)
    {
        _onReceiveAknowledgment = aOnReceiveAknowledgment;
    }

    void NetworkHandler::listen()
    {
        _readBuffer = _readInbound.prepare(READ_BUFFER_SIZE);
        _socket.async_receive_from(boost::asio::buffer(_readBuffer), _readEndpoint,
                                   boost::bind(&NetworkHandler::handleRequest, this, boost::asio::placeholders::error,
                                               boost::asio::placeholders::bytes_transferred));

        if (!_ioThread.joinable()) {
            _ioThread = boost::thread(boost::bind(&boost::asio::io_service::run, &_ioService));
        }
    }

    void NetworkHandler::handleRequest(const boost::system::error_code &aError, std::size_t aBytesTransferred)
    {
        (void) aError;
        (void) aBytesTransferred;

        try {
            _readInbound.commit(aBytesTransferred);
            std::istream archiveStream(&_readInbound);
            if (archiveStream.peek() != EOF && archiveStream.peek() != 0) {
                RType::Packet packet;
                boost::archive::binary_iarchive archive(archiveStream);
                archive >> packet;
                if (packet.type == -1) { // receive aknowledgment
                    _onReceiveAknowledgment(packet.uuid, _readEndpoint);
                    if (_senders.find(packet.uuid) != _senders.end() && _senders[packet.uuid].first.joinable()) {
                        _senders[packet.uuid].second = false;
                        _senders[packet.uuid].first.join();
                        _senders.erase(packet.uuid);
                    }
                } else {
                    answerAknowledgment(packet.uuid, _readEndpoint);
                    _onReceive(packet, _readEndpoint);
                }
            }
        } catch (const std::exception &e) {
            std::cout << "Unserialization error: " << e.what() << std::endl;
        }
        listen();
    }

    void NetworkHandler::send(const RType::Packet &aPacket, udp::endpoint &aClientEndpoint)
    {
        boost::asio::streambuf buf;
        RType::serializePacket(&buf, aPacket);
        _socket.send_to(buf.data(), aClientEndpoint);

        // _senders[aPacket.uuid].second = true;
        // _senders[aPacket.uuid].first = std::thread([this, aPacket, aClientEndpoint]() {
        //     try {
        //         boost::asio::streambuf buf;
        //         RType::serializePacket(&buf, aPacket);

        //         while (_senders[aPacket.uuid].second.load()) {
        //             _socket.send_to(buf.data(), aClientEndpoint);
        //             std::this_thread::sleep_for(std::chrono::milliseconds(200));
        //         }
        //     } catch (std::exception &e) {
        //         std::cerr << "NetworkHandler send error: " << e.what() << std::endl;
        //     }
        // });
    }

    void NetworkHandler::answerAknowledgment(const std::string &aPacketUuid, udp::endpoint &aEndpoint)
    {
        try {
            boost::asio::streambuf buf;
            RType::Packet packet(aPacketUuid);
            RType::serializePacket(&buf, packet);
            _socket.send_to(buf.data(), aEndpoint);
        } catch (std::exception &e) {
            std::cerr << "NetworkHandler send error: " << e.what() << std::endl;
        }
    }

    boost::asio::io_service &NetworkHandler::getIoService()
    {
        return _ioService;
    }

    void NetworkHandler::stop()
    {
        for (auto &sender : _senders) {
            sender.second.second = false;
            if (sender.second.first.joinable()) {
                sender.second.first.join();
            }
        }
        _ioService.stop();
        if (_ioThread.joinable()) {
            _ioThread.join();
        }
        _socket.close();
    }

} // namespace Network
