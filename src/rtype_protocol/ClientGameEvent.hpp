#ifndef GAMEEVENT_HPP
#define GAMEEVENT_HPP

#include "Event/Event.hpp"
#include "Utils.hpp"

namespace RTypeProtocol {

    enum class ClientEventType
    {
        PLAYER_CONNECTION = 0,
        PLAYER_DISCONNECTION = 1,
        PLAYER_POSITION = 2,
        PLAYER_SHOOT = 3,
        PLAYER_HEALTH = 4,
        PLAYER_DEATH = 5,
        MONSTER_SPAWN = 6,
        MONSTER_DEATH = 7,
        MONSTER_POSITION = 8,
        MONSTER_SHOOT = 9,
    };

    /**
     * @brief Game event class is the base class of all game events
     */
    class ClientGameEvent : public ECS::Event::Event
    {
        private:
            ClientEventType _type;
            size_t _id;

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
