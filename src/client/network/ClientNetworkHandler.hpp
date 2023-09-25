#include <boost/asio.hpp>

#ifndef ClientNetworkHandler_HPP
    #define ClientNetworkHandler_HPP

constexpr unsigned short READ_BUFFER_SIZE = 128;

namespace Network {

    using boost::asio::ip::udp;

    class ClientNetworkHandler
    {
        private:
            boost::asio::io_service _ioService;
            udp::endpoint _serverEndpoint;
            udp::resolver _resolver;
            udp::socket _socket;
            std::array<char, READ_BUFFER_SIZE> _readBuffer;
            std::thread _ioThread;

            /**
             * @brief Connect to the server
             * @param aHost The host to connect to
             * @param aPort The port to connect to
             */
            ClientNetworkHandler(std::string &, std::string &);

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
            ~ClientNetworkHandler() = default;

            /**
             * @brief Get the instance of the singleton
             * @param aHost The host to connect to
             * @param aPort THe port to connect to
             * @return ClientNetworkHandler & The instance of the singleton
             */
            static ClientNetworkHandler &getInstance(std::string &aHost, std::string &aPort)
            {
                static ClientNetworkHandler instance(aHost, aPort);
                return instance;
            }

            /**
             * @brief Listen to the server
             */
            void listen();

            /**
             * @brief Send a message to the server
             * @param aBuffer The message to send
             */
            void send(const boost::asio::const_buffer &);

            /**
             * @brief Stop the client
             */
            void stop();
    };

} // namespace Network

#endif
