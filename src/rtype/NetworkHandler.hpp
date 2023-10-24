#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <iostream>
#include "Packet.hpp"
#include "Serialization.hpp"
#include "Values.hpp"
#include <unordered_map>

#ifndef NETWORKHANDLER_HPP
    #define NETWORKHANDLER_HPP

namespace Network {
    enum ConnectionStatus
    {
        PENDING,
        CONNECTED,
    };

    using boost::asio::ip::udp;
    using Sender = std::pair<std::thread, std::atomic<bool>>;
    using Buffer = std::vector<unsigned char>;
    using ReceiveCallback = std::function<void(uint8_t, IPayload &, udp::endpoint &)>;

    class NetworkHandler
    {
        private:
            boost::asio::io_service _ioService;
            udp::socket _socket = udp::socket(_ioService);

            boost::asio::streambuf _readInbound;
            boost::asio::streambuf::mutable_buffers_type _readBuffer = _readInbound.prepare(READ_BUFFER_SIZE);

            std::unordered_map<unsigned char, std::function<IPayload &(Buffer &)>> _packetFactory;

            udp::endpoint _readEndpoint;
            ReceiveCallback _onReceive;
            boost::thread _ioThread;

            std::unordered_map<std::string, Sender> _senders;

            /**
             * @brief Launch the server
             */
            NetworkHandler() = default;

            /**
             * @brief Handle a request from a client
             *
             * @param aError The error code
             * @param aBytesTransferred The number of bytes transferred
             */
            void tryHandleRequest(const boost::system::error_code &, std::size_t);

            /**
             * @brief Handle a request from a client
             *
             * @param aBytesTransferred The number of bytes transferred
             */
            void handleRequest(std::size_t);

        public:
            /**
             * @brief Destroy the NetworkHandler object
             */
            ~NetworkHandler() = default;

            /**
             * @brief Get the instance of the singleton
             * @return NetworkHandler & The instance of the singleton
             */
            static NetworkHandler &getInstance()
            {
                static NetworkHandler instance;
                return instance;
            }

            /**
             * @brief Start handler with specific protocol
             * @param aProtocol The protocol to use
             */
            void start(const boost::asio::basic_socket<boost::asio::ip::udp>::protocol_type &);

            /**
             * @brief Start handler with specific protocol
             * @param aEndpoint The endpoint to bind to
             */
            void bind(const udp::endpoint &);

            /**
             * @brief Set the on receive callback
             * @param aOnReceive The callback to set
             */
            void onReceive(ReceiveCallback);

            /**
             * @brief Listen to clients
             */
            void listen();

            /**
             * @brief Send a packet
             * @param aType The packet type
             * @param aEndpoint The id of the client to send the message to
             */
            void send(int8_t, const udp::endpoint &);

            /**
             * @brief Send a packet
             * @param aType The packet type
             * @param aPayload The payload to send
             * @param aEndpoint The id of the client to send the message to
             */
            template<typename Payload>
            void send(int8_t aType, Payload &aPayload, const udp::endpoint &aEndpoint)
            {
                boost::asio::streambuf buf = boost::asio::streambuf();
                PacketHeader header(aType);
                auto strBuff = Network::Serialization::serialize<Payload>(header, aPayload);

                _socket.send_to(buf.data(), aEndpoint);
            }

            /**
             * @brief Get the io service
             */
            boost::asio::io_service &getIoService();

            /**
             * @brief Stop the handler
             */
            void stop();
    };

} // namespace Network

#endif
