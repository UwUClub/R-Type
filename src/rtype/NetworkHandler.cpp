#include "NetworkHandler.hpp"
#include <bitset>
#include <boost/bind.hpp>
#include <chrono>
#include <iostream>
#include <string>
#include "EventManager.hpp"
#include "Packets.hpp"
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>

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
                                   boost::bind(&NetworkHandler::tryHandleRequest, this,
                                               boost::asio::placeholders::error,
                                               boost::asio::placeholders::bytes_transferred));

        if (!_ioThread.joinable()) {
            _ioThread = boost::thread(boost::bind(&boost::asio::io_service::run, &_ioService));
        }
    }

    void NetworkHandler::tryHandleRequest(const boost::system::error_code &aError, std::size_t aBytesTransferred)
    {
        (void) aError;

        try {
            handleRequest(aBytesTransferred);
        } catch (const std::exception &e) {
            std::cout << "Unserialization error: " << e.what() << std::endl;
        }
        _readInbound.consume(_readInbound.size());
        listen();
    }

    void NetworkHandler::handleRequest(std::size_t aBytesTransferred)
    {
        _readInbound.commit(aBytesTransferred);
        std::istream is(&_readInbound);
        RType::Packet packet;

        if (_readInbound.size() < 40) {
            return;
        }

        // Read uuid
        char uuid[37] = {};
        is.read(uuid, 36);
        uuid[36] = '\0';
        packet.uuid = std::string(uuid);

        // Check invalid uuid
        if (boost::uuids::string_generator()(packet.uuid).version() == boost::uuids::uuid::version_unknown) {
            return;
        }

        // Read type
        int type = -2;
        is.read(reinterpret_cast<char *>(&type), sizeof(int));
        packet.type = type;

        // Read payload
        while (is.peek() != EOF) {
            float i;
            is.read(reinterpret_cast<char *>(&i), sizeof(float));
            packet.payload.push_back(i);
        }

        if (packet.type == -1) { // receive aknowledgment
            _onReceiveAknowledgment(packet.uuid, _readEndpoint);
            if (_senders.find(packet.uuid) != _senders.end() && _senders[packet.uuid].first.joinable()) {
                _senders[packet.uuid].second = false;
                _senders[packet.uuid].first.join();
                _senders.erase(packet.uuid);
            }
        } else {
            RType::Packet aknowledgment(packet.uuid);
            send(aknowledgment, _readEndpoint);
            _onReceive(packet, _readEndpoint);
        }
    }

    void NetworkHandler::send(const RType::Packet &aPacket, const udp::endpoint &aClientEndpoint)
    {
        boost::asio::streambuf buf;
        std::ostream os(&buf);

        os.write(aPacket.uuid.c_str(), 36);
        os.write(reinterpret_cast<const char *>(&aPacket.type), sizeof(aPacket.type));
        for (auto &i : aPacket.payload) {
            os.write(reinterpret_cast<const char *>(&i), sizeof(i));
        }

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
