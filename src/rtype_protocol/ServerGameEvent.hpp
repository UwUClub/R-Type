#include <cstddef>
#include "Event.hpp"

#ifndef SERVERGAMEEVENT_HPP
    #define SERVERGAMEEVENT_HPP

namespace RTypeProtocol {

    enum class ServerEventType
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
    class ServerGameEvent : public ECS::Event::Event
    {
        private:
            ServerEventType _type;
            std::size_t _id;

        public:
            //-------------------CONSTRUCTORS / DESTRUCTOR-------------------//
            /**
             * @brief Construct a new Game Event object
             * @param aType the type of the event
             * @param aId the id of the client who triggers the event
             */
            explicit ServerGameEvent(ServerEventType aType, size_t aId);
    };
} // namespace RTypeProtocol

#endif // !
