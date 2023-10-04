#include <boost/asio.hpp>
#include <iostream>
#include "Packets.hpp"
#include "Values.hpp"
#include <unordered_map>

#ifndef NetworkHandler_HPP
    #define NetworkHandler_HPP

namespace Network {

    using boost::asio::ip::udp;

    class NetworkHandler
    {
        private:
            boost::asio::io_service _ioService;
            udp::socket _socket = udp::socket(_ioService);
            std::array<char, READ_BUFFER_SIZE> _readBuffer = std::array<char, READ_BUFFER_SIZE>();
            udp::endpoint _readEndpoint;
            std::function<void(const RType::Packet &, udp::endpoint &)> _onReceive;
            std::thread _ioThread;

            using Sender = std::pair<std::thread, std::atomic<bool>>;
            std::unordered_map<std::string, Sender> _senders;
            std::vector<std::string> _receivedPacketUuids;

            /**
             * @brief Launch the server
             */
            explicit NetworkHandler();

            /**
             * @brief Handle a request from a client
             * @param aError The error code
             * @param aBytesTransferred The number of bytes transferred
             */
            void handleRequest(const boost::system::error_code &, std::size_t);

        public:
            /**
             * @brief Destroy the NetworkHandler object
             */
            ~NetworkHandler();

            /**
             * @brief Get the instance of the singleton
             * @param aPort The port to listen to
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
            void onReceive(std::function<void(const RType::Packet &, udp::endpoint &)>);

            /**
             * @brief Listen to clients
             */
            void listen();

            /**
             * @brief Send a message to the server
             * @param aPacket The packet to send
             * @param aClientEndpoint The id of the client to send the message to
             */
            void send(const RType::Packet &, udp::endpoint &);

            /**
             * @brief Answer to a sender as the packet has been received
             * @param aPacketUuid The uuid of the packet
             * @param aEndpoint The endpoint of the sender
             */
            void answerAknowledgment(const std::string &, udp::endpoint &);

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
