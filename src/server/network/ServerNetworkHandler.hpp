#include <boost/asio.hpp>
#include <iostream>
#include <map>
#include "Packets.hpp"

#ifndef ServerNetworkHandler_HPP
    #define ServerNetworkHandler_HPP

namespace Network {

    constexpr unsigned short READ_BUFFER_SIZE = 1024;

    using boost::asio::ip::udp;

    class ServerNetworkHandler
    {
        private:
            boost::asio::io_service _ioService;
            udp::socket _socket;
            std::array<char, READ_BUFFER_SIZE> _readBuffer;
            udp::endpoint _readEndpoint;
            std::map<size_t, udp::endpoint> _clients;
            std::thread _ioThread;

            /**
             * @brief Launch the server
             * @param aHost The host to listen to
             * @param aPort The port to listen to
             */
            explicit ServerNetworkHandler(std::string &, unsigned short);

            /**
             * @brief Handle a request from a client
             * @param aError The error code
             * @param aBytesTransferred The number of bytes transferred
             */
            void handleRequest(const boost::system::error_code &, std::size_t);

        public:
            /**
             * @brief Destroy the ServerNetworkHandler object
             */
            ~ServerNetworkHandler() = default;

            /**
             * @brief Get the instance of the singleton
             * @param aPort The port to listen to
             * @return ServerNetworkHandler & The instance of the singleton
             */
            static ServerNetworkHandler &getInstance(std::string &aHost, unsigned short aPort)
            {
                static ServerNetworkHandler instance(aHost, aPort);
                return instance;
            }

            /**
             * @brief Listen to clients
             */
            void listen();

            /**
             * @brief Send a message to the server
             * @param aPacket The packet to send
             * @param aClientId The id of the client to send the message to
             */
            void send(const RTypeProtocol::Packet &, size_t);

            /**
             * @brief Stop the server
             */
            void stop();
    };

} // namespace Network

#endif
