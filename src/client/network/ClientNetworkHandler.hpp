#include <array>
#include <boost/asio.hpp>
#include "Packets.hpp"
#include "Values.hpp"
#include <unordered_map>

#ifndef CLIENTNETWORKHANDLER_HPP
    #define CLIENTNETWORKHANDLER_HPP

namespace Network {

    using boost::asio::ip::udp;

    class ClientNetworkHandler
    {
        private:
            boost::asio::io_service _ioService;
            udp::endpoint _serverEndpoint;
            udp::resolver _resolver = udp::resolver(_ioService);
            udp::socket _socket = udp::socket(_ioService);
            std::array<char, READ_BUFFER_SIZE> _readBuffer = std::array<char, READ_BUFFER_SIZE>();
            std::thread _ioThread;
            std::unordered_map<std::string, std::thread> _senders;

            /**
             * @brief Get the instance of the singleton
             */
            ClientNetworkHandler() = default;

            /**
             * @brief Handle a request from server
             * @param aError The error code
             * @param aBytesTransferred The number of bytes transferred
             */
            void handleRequest(const boost::system::error_code &, std::size_t);

        public:
            /**
             * @brief Destroy the ClientNetworkHandler object
             */
            ~ClientNetworkHandler();

            /**
             * @brief Get the instance of the singleton
             * @return ClientNetworkHandler & The instance of the singleton
             */
            static ClientNetworkHandler &getInstance()
            {
                static ClientNetworkHandler instance;
                return instance;
            }

            /**
             * @brief Run the client
             * @param aHost The host to connect to
             * @param aPort THe port to connect to
             */
            void start(std::string &, std::string &);

            /**
             * @brief Listen to the server
             */
            void listen();

            /**
             * @brief Send a message to the server
             * @param aPacket The packet to send
             */
            void send(const RType::Packet &);

            /**
             * @brief Stop the client
             */
            void stop();
    };

} // namespace Network

#endif
