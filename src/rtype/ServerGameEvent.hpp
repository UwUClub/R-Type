#include <boost/asio.hpp>
#include "Event.hpp"

#ifndef SERVERGAMEEVENT_HPP
    #define SERVERGAMEEVENT_HPP

namespace RTypeProtocol {

    using boost::asio::ip::udp;

    enum class ServerEventType
    {
        CONNECT = 0,
        DISCONNECT = 1,
        CRASH = 2,
        MOVE_LEFT = 3,
        MOVE_UP = 4,
        MOVE_RIGHT = 5,
        MOVE_DOWN = 6,
        SHOOT = 7
    };

    /**
     * @brief Game event class is the base class of all game events
     */
    class ServerGameEvent : public ECS::Event::Event
    {
        private:
            ServerEventType _type;
            std::size_t _entityId;
            udp::endpoint _clientEndpoint;

        public:
            //-------------------CONSTRUCTORS / DESTRUCTOR-------------------//
            /**
             * @brief Construct a new Game Event object
             * @param aType the type of the event
             * @param aEntityId the id of the client who triggers the event
             * @param aClientEndpoint the endpoint of the client who triggers the event
             */
            explicit ServerGameEvent(ServerEventType aType, size_t aEntityId, udp::endpoint aClientEndpoint);

            /**
             * @brief Get event type
             * @return EventType
             */
            ServerEventType getType() const;

            /**
             * @brief Get entity id
             * @return size_t
             */
            std::size_t getEntityId() const;

            /**
             * @brief Get client endpoint
             * @return udp::endpoint
             */
            udp::endpoint getClientEndpoint() const;
    };
} // namespace RTypeProtocol

#endif // !
