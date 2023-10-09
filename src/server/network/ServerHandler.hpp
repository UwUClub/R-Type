#include <boost/asio.hpp>
#include <iostream>
#include "Packets.hpp"
#include <unordered_map>

#ifndef SERVERHANDLER_HPP
    #define SERVERHANDLER_HPP

namespace Network {

    constexpr unsigned short READ_BUFFER_SIZE = 1024;

    using boost::asio::ip::udp;

    class ServerHandler
    {
        private:
            std::unordered_map<size_t, udp::endpoint> _clients;

            /**
             * @brief Launch the server
             */
            ServerHandler() = default;

        public:
            /**
             * @brief Destroy the ServerHandler object
             */
            ~ServerHandler() = default;

            /**
             * @brief Get the instance of the singleton
             * @return ServerHandler & The instance of the singleton
             */
            static ServerHandler &getInstance()
            {
                static ServerHandler instance;
                return instance;
            }

            /**
             * @brief Start the server
             * @param aHost The host to listen to
             * @param aPort The port to listen to
             * @return ServerHandler & The instance of the singleton
             */
            void start(std::string &, unsigned short);

            /**
             * @brief Handle packet reception
             * @param aPacket The received packet
             * @param aEndpoint The endpoint of the server
             */
            void receivePacket(const RType::Packet &, udp::endpoint &);

            /**
             * @brief Register a client to the server
             * @param aClientId The id of the client
             * @param aEndpoint The endpoint of the client
             */
            void addClient(std::size_t, udp::endpoint);

            /**
             * @brief Get the number of clients connected to the server
             * @return int The number of clients connected to the server
             */
            int getNumberClients() const;

            /**
             * @brief Send a message to the server
             * @param aPacket The packet to send
             * @param aClientId The id of the client to send the message to
             */
            void send(const RType::Packet &, size_t);

            /**
             * @brief Broadcast a message to all clients. Each client receives a packet with a unique uuid.
             * @param aType The packet type to send
             * @param aPayload The payload to send
             */
            void broadcast(int, std::vector<float>);
    };

} // namespace Network

#endif