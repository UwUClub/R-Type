#include <array>
#include <boost/asio.hpp>
#include "Packets.hpp"
#include "Values.hpp"
#include <unordered_map>

#ifndef CLIENTHANDLER_HPP
    #define CLIENTHANDLER_HPP

namespace Network {

    using boost::asio::ip::udp;

    class ClientHandler
    {
        private:
            udp::resolver _resolver;
            udp::endpoint _serverEndpoint;

            /**
             * @brief Get the instance of the singleton
             */
            ClientHandler();

        public:
            /**
             * @brief Destroy the ClientHandler object
             */
            ~ClientHandler() = default;

            /**
             * @brief Get the instance of the singleton
             * @return ClientHandler & The instance of the singleton
             */
            static ClientHandler &getInstance()
            {
                static ClientHandler instance;
                return instance;
            }

            /**
             * @brief Run the client
             * @param aHost The host to connect to
             * @param aPort THe port to connect to
             */
            void start(std::string &, std::string &);

            /**
             * @brief Handle packet reception
             * @param aPacket The received packet
             */
            void receivePacket(const RType::Packet &);

            /**
             * @brief Send a packet to the server
             * @param aPacket The packet to send
             */
            void send(RType::Packet &aPacket);
    };

} // namespace Network

#endif
