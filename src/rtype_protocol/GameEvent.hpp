#ifndef GAMEEVENT_HPP
#define GAMEEVENT_HPP

#include "Event/Event.hpp"
#include "Utils.hpp"

namespace RTypeProtocol {

    enum class ClientEvent
    {
        CONNECT = 0,
        DISCONNECT = 1,
        CRASH = 2,
        MOVE_UP = 3,
        MOVE_DOWN = 4,
        SHOOT = 5
    };

    /**
     * @brief Game event class is the base class of all game events
     */
    class GameEvent : public ECS::Event::Event
    {
        private:
            ClientEvent _value;

        public:
            //-------------------CONSTRUCTORS / DESTRUCTOR-------------------//
            /**
             * @brief Construct a new Game Event object
             * @param aValue the value of the event
             */
            explicit GameEvent(ClientEvent aValue);
    };
} // namespace RTypeProtocol

#endif // !
