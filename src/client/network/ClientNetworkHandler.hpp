#include <boost/array.hpp>
#include <boost/asio.hpp>

#ifndef ClientNetworkHandler_HPP
    #define ClientNetworkHandler_HPP

constexpr unsigned short READ_BUFFER_SIZE = 128;

namespace Network {

    using boost::asio::ip::udp;

    class ClientNetworkHandler
    {
        private:
            boost::asio::io_context _ioContext;
            udp::endpoint _serverEndpoint;
            udp::resolver _resolver;
            udp::socket _socket;
            boost::array<char, READ_BUFFER_SIZE> _readBuffer;
            std::thread _ioThread;

            /**
             * @brief Connect to the server
             */
            ClientNetworkHandler();

            /**
             * @brief Handle a request from server
             * @param error The error code
             * @param bytesTransferred The number of bytes transferred
             */
            void handleRequest(const boost::system::error_code &, std::size_t);

        public:
  
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
             * @brief Listen to the server
             */
            void listen();

            /**
             * @brief Send a message to the server
             * @param buffer The message to send
             */
            void send(const boost::asio::const_buffer &);
    };

} // namespace Network

#endif
