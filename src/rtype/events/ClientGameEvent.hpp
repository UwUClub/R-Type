#include <cstddef>
#include <vector>
#include "Event.hpp"

#ifndef CLIENTGAMEEVENT_HPP
    #define CLIENTGAMEEVENT_HPP

namespace RType {

    enum class ClientEventType
    {
        PLAYER_SPAWN = 0,
        PLAYER_DISCONNECTION = 1,
        PLAYER_POSITION = 2,
        PLAYER_SHOOT = 3,
        PLAYER_DEATH = 4,
        ENEMY_SPAWN = 5,
        ENEMY_DEATH = 6,
        ENEMY_SHOOT = 7,
    };

    /**
     * @brief Game event class is the base class of all game events
     */
    class ClientGameEvent : public ECS::Event::Event
    {
        private:
            ClientEventType _type;
            std::vector<float> _payload;

        public:
            //-------------------CONSTRUCTORS / DESTRUCTOR-------------------//
            /**
             * @brief Construct a new Game Event object
             * @param aType the type of the event
             */
            explicit ClientGameEvent(ClientEventType aType);

            /**
             * @brief Construct a new Game Event object
             * @param aType the type of the event
             * @param aPayload the payload of the event
             */
            explicit ClientGameEvent(ClientEventType aType, std::vector<float> aPayload);

            /**
             * @brief Get event type
             * @return ClientEventType
             */
            ClientEventType getType() const;

            /**
             * @brief Get the payload of the event
             * @return std::vector<float>
             */
            std::vector<float> getPayload() const;
    };
} // namespace RType

#endif // !