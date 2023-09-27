#include <cstddef>
#include "Event.hpp"

#ifndef CLIENTGAMEEVENT_HPP
    #define CLIENTGAMEEVENT_HPP

namespace RTypeProtocol {

    enum class ClientEventType
    {
        PLAYER_CONNECTION = 0,
        PLAYER_DISCONNECTION = 1,
        PLAYER_POSITION = 2,
        PLAYER_SHOOT = 3,
        PLAYER_DEATH = 4,
        MONSTER_SPAWN = 5,
        MONSTER_DEATH = 6,
        MONSTER_POSITION = 7,
        MONSTER_SHOOT = 8,
    };

    /**
     * @brief Game event class is the base class of all game events
     */
    class ClientGameEvent : public ECS::Event::Event
    {
        private:
            ClientEventType _type;
            std::size_t _id;

        public:
            //-------------------CONSTRUCTORS / DESTRUCTOR-------------------//
            /**
             * @brief Construct a new Game Event object
             * @param aType the type of the event
             * @param aId the id of the client who triggers the event
             */
            explicit ClientGameEvent(ClientEventType aType, size_t aId);
    };
} // namespace RTypeProtocol

#endif // !
