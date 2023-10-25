#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include <vector>
#include "Components.hpp"
#include "EwECS/SparseArray.hpp"
#include "Packet.hpp"
#include "PlayerColor.hpp"
#include "Values.hpp"
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
            std::array<int, MAX_NUMBER_PLAYER> _clientColors;
            std::vector<std::unique_ptr<udp::endpoint>> _waitingQueue = std::vector<std::unique_ptr<udp::endpoint>>();

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
             * @param aPacketFactory The packet factory
             * @return ServerHandler & The instance of the singleton
             */
            void start(std::string &, unsigned short, PacketFactory &);

            /**
             * @brief Handle packet reception
             * @param aType The type of the packet
             * @param aPayload The received payload
             * @param aEndpoint The endpoint of the sender
             */
            void receivePacket(uint8_t, IPayload *, const udp::endpoint &);

            /**
             * @brief Handle aknowledgment reception
             * @param aEndpoint The endpoint of the sender
             */
            void receiveAknowledgment(const udp::endpoint &);

            /**
             * @brief Register a client to the server
             * @param aClientId The id of the client
             */
            void addClient(unsigned short);

            /**
             * @brief Get the client color
             * @param aClientId The id of the client
             * @return int The client color
             */
            RType::PLAYER_COLOR getClientColor(size_t);

            /**
             * @brief Add a client to the client color list
             *
             * @param aClientId The id of the client to add
             * @return The client color (if -1, the server is full and the client is not added)
             */
            RType::PLAYER_COLOR addClientColor(size_t);

            /**
             * @brief Remove a client from the server
             * @param aClientId The id of the client to remove
             */
            void removeClient(size_t);

            /**
             * @brief Get the number of clients connected to the server
             * @return int The number of clients connected to the server
             */
            int getNumberClients() const;

            /**
             * @brief Tell the client there is an error
             * @param aClientId The id of the client to send the message to
             */
            void sendError(unsigned short aClientId);

            /**
             * @brief Send a packet to a client
             * @param aHeader The packet header
             * @param aPayload The packet payload
             * @param aClientId The id of the client to send the message to
             */
            template<typename Payload>
            void send(PacketHeader &aHeader, Payload &aPayload, unsigned short aClientId,
                      ECS::Core::SparseArray<Component::Connection> &aConnection)
            {
                if (aConnection[aClientId].has_value()) {
                    aConnection[aClientId].value().status = Network::ConnectionStatus::PENDING;
                    NetworkHandler::getInstance().send<Payload>(aHeader, aPayload, _clients[aClientId]);
                }
            }

            /**
             * @brief Send a packet to a client
             * @param aType The packet type to send
             * @param aPayload The packet payload
             * @param aClientId The id of the client to send the message to
             */
            template<typename Payload>
            void send(int8_t aType, Payload &aPayload, unsigned short aClientId,
                      ECS::Core::SparseArray<Component::Connection> &aConnection)
            {
                if (aConnection[aClientId].has_value()) {
                    aConnection[aClientId].value().status = Network::ConnectionStatus::PENDING;
                    NetworkHandler::getInstance().send<Payload>(aType, aPayload, _clients[aClientId]);
                }
            }

            /**
             * @brief Broadcast a message to all clients. Each client receives a packet with a unique uuid.
             * @param aType The packet type to send
             * @param aPayload The payload to send
             * @param aConnections Connection components of clients
             */
            template<typename Payload>
            void broadcast(int8_t aType, Payload &aPayload, ECS::Core::SparseArray<Component::Connection> &aConnection)
            {
                for (auto &client : _clients) {
                    send(aType, aPayload, client.first, aConnection);
                }
            }

            /**
             * @brief Check if the server is full
             * @return true if the server is full, false otherwise
             */
            [[nodiscard]] bool isFull() const;
    };

} // namespace Network

#endif
