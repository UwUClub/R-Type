#include <array>
#include <boost/asio.hpp>
#include "NetworkHandler.hpp"
#include "Packet.hpp"
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
             * @param aType The type of the packet
             * @param aPayload The received payload
             */
            void receivePacket(uint8_t, IPayload &);

            /**
             * @brief Send a packet to the server
             * @param aType The packet type
             */
            void send(int8_t aType);

            /**
             * @brief Send a packet to the server
             * @param aType The packet type
             * @param aPayload The packet payload
             */
            template<typename Payload>
            void send(int8_t aType, Payload &aPayload)
            {
                NetworkHandler::getInstance().send<Payload>(aType, aPayload, _serverEndpoint);
            }
    };

} // namespace Network

#endif
