#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <map>

#ifndef ServerNetworkHandler_HPP
    #define ServerNetworkHandler_HPP

namespace Network {

    constexpr unsigned short UDP_PORT = 13;
    constexpr unsigned short READ_BUFFER_SIZE = 128;

    using boost::asio::ip::udp;

    class ServerNetworkHandler
    {
        private:
            boost::asio::ip::port_type _port = UDP_PORT;
            boost::asio::io_context _ioContext;
            udp::socket _socket;
            boost::array<char, READ_BUFFER_SIZE> _readBuffer;
            udp::endpoint _readEndpoint;
            std::map<size_t, udp::endpoint> _clients;
            std::thread _ioThread;

            /**
             * @brief Launch the server
             */
            explicit ServerNetworkHandler();

            /**
             * @brief Handle a request from a client
             * @param error The error code
             * @param bytesTransferred The number of bytes transferred
             */
            void handleRequest(const boost::system::error_code &, std::size_t);

        public:
            /**
             * @brief Destroy the ServerNetworkHandler object
             */
            ~ServerNetworkHandler();

            /**
             * @brief Get the instance of the singleton
             * @return ServerNetworkHandler & The instance of the singleton
             */
            static ServerNetworkHandler &getInstance()
            {
                static ServerNetworkHandler instance;
                return instance;
            }

            /**
             * @brief Listen to clients
             */
            void listen();

            /**
             * @brief Send a message to the server
             * @param buffer The message to send
             * @param clientId The id of the client to send the message to
             */
            void send(const boost::asio::const_buffer, size_t);
    };

} // namespace Network

#endif
