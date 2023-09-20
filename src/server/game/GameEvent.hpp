#ifndef GAMEEVENT_HPP
#define GAMEEVENT_HPP

#include "Event.hpp"
#include "Utils.hpp"

namespace Game {

    enum class ClientEvent
    {
        CONNECT = 0,
        DISCONNECT = 1,
        CRASH = 2,
        MOVE = 3,
        SHOOT = 4
    };

    /**
     * @brief Game event class is the base class of all game events
     */
    class GameEvent : public ECS::Event::Event
    {
        public:
            //-------------------CONSTRUCTORS / DESTRUCTOR-------------------//
            /**
             * @brief Construct a new Game Event object
             */
            GameEvent();
    };
} // namespace Game

#endif // !
