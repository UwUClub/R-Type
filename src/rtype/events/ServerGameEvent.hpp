#include <boost/asio.hpp>

#ifndef SERVERGAMEEVENT_HPP
    #define SERVERGAMEEVENT_HPP

namespace RType {

    using boost::asio::ip::udp;

    enum class ServerEventType
    {
        CONNECT = 0,
        DISCONNECT = 1,
        AKNOWLEDGMENT = 2,
        MOVE = 3,
        SHOOT = 4,
        BONUS = 5,
    };

    /**
     * @brief Game event class is the base class of all game events
     */
    class ServerGameEvent
    {
        private:
            ServerEventType _type;
            int _entityId;
            std::vector<float> _payload;
            udp::endpoint _clientEndpoint;

        public:
            //-------------------CONSTRUCTORS / DESTRUCTOR-------------------//
            /**
             * @brief Construct a new Game Event object
             * @param aType the type of the event
             * @param aEntityId the entity id
             * @param aPayload the payload
             * @param aClientEndpoint the endpoint of the client who triggers the event
             */
            explicit ServerGameEvent(ServerEventType aType, int aEntityId, const std::vector<float> &aPayload,
                                     const udp::endpoint &aClientEndpoint);

            /**
             * @brief Get event type
             * @return EventType
             */
            [[nodiscard]] ServerEventType getType() const;

            /**
             * @brief Get entity id
             * @return The entity id
             */
            [[nodiscard]] int getEntityId() const;

            /**
             * @brief Get payload
             * @return The payload
             */
            [[nodiscard]] const std::vector<float> &getPayload() const;

            /**
             * @brief Get client endpoint
             * @return udp::endpoint
             */
            [[nodiscard]] const udp::endpoint &getClientEndpoint() const;
    };
} // namespace RType

#endif // !
