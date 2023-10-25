#include <memory>
#include "EwECS/Network/Packet.hpp"

#ifndef SERVERGAMEEVENT_HPP
    #define SERVERGAMEEVENT_HPP

namespace RType {

    enum ServerEventType
    {
        AKNOWLEDGMENT = -1,
        CONNECT = 0,
        DISCONNECT = 1,
        MOVE = 2,
        SHOOT = 3,
        BONUS = 4,
        MAX_SRV_EVT = 5
    };

    /**
     * @brief Game event class is the base class of all game events
     */
    class ServerGameEvent
    {
        private:
            ServerEventType _type;
            unsigned short _entityId;
            std::shared_ptr<ECS::Network::IPayload> _payload;

        public:
            //-------------------CONSTRUCTORS / DESTRUCTOR-------------------//
            /**
             * @brief Construct a new Game Event object
             * @param aType the type of the event
             * @param aEntityId the entity id
             * @param aPayload the payload
             */
            ServerGameEvent(ServerEventType aType, unsigned short aEntityId, ECS::Network::IPayload *aPayload);

            ServerGameEvent(const ServerGameEvent &gameEvent) = default;
            ServerGameEvent(ServerGameEvent &&gameEvent) = default;
            ServerGameEvent &operator=(const ServerGameEvent &gameEvent) = default;
            ServerGameEvent &operator=(ServerGameEvent &&gameEvent) noexcept = default;

            /**
             * @brief Get event type
             * @return EventType
             */
            [[nodiscard]] ServerEventType getType() const;

            /**
             * @brief Get entity id
             * @return The entity id
             */
            [[nodiscard]] unsigned short getEntityId() const;

            /**
             * @brief Get payload
             * @return The payload
             */
            template<typename Payload>
            [[nodiscard]] const Payload &getPayload() const
            {
                return *reinterpret_cast<Payload *>(_payload.get());
            }
    };
} // namespace RType

#endif // !
