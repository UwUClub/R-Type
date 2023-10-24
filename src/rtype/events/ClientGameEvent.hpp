#include <cstddef>
#include <vector>
#include "Packet.hpp"

#ifndef CLIENTGAMEEVENT_HPP
    #define CLIENTGAMEEVENT_HPP

namespace RType {

    enum ClientEventType
    {
        PLAYER_SPAWN = 0,
        PLAYER_DISCONNECTION = 1,
        PLAYER_POSITION = 2,
        PLAYER_SHOOT = 3,
        PLAYER_BONUS = 4,
        PLAYER_DEATH = 5,
        ENEMY_SPAWN = 6,
        ENEMY_DEATH = 7,
        ENEMY_SHOOT = 8,
        SERVER_FULL = 9,
        MAX_CLI_EVT = 10
    };

    /**
     * @brief Game event class is the base class of all game events
     */
    class ClientGameEvent
    {
        private:
            ClientEventType _type;
            std::shared_ptr<Network::IPayload> _payload;

        public:
            //-------------------CONSTRUCTORS / DESTRUCTOR-------------------//
            /**
             * @brief Construct a new Game Event object
             * @param aType the type of the event
             */
            explicit ClientGameEvent(ClientEventType aType);

            ClientGameEvent(const ClientGameEvent &gameEvent) = default;
            ClientGameEvent(ClientGameEvent &&gameEvent) = default;
            ClientGameEvent &operator=(const ClientGameEvent &gameEvent) = default;
            ClientGameEvent &operator=(ClientGameEvent &&gameEvent) noexcept = default;

            /**
             * @brief Construct a new Game Event object
             * @param aType the type of the event
             * @param aPayload the payload of the event
             */
            explicit ClientGameEvent(ClientEventType aType, Network::IPayload *aPayload);

            /**
             * @brief Get event type
             * @return ClientEventType
             */
            [[nodiscard]] ClientEventType getType() const;

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
