#include <cstddef>
#include <vector>
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
            std::size_t _onlineEntityId;
            std::vector<float> _payload;

        public:
            //-------------------CONSTRUCTORS / DESTRUCTOR-------------------//
            /**
             * @brief Construct a new Game Event object
             * @param aType the type of the event
             * @param aOnlineEntityId the online id of the entity who triggers the event
             */
            explicit ClientGameEvent(ClientEventType aType, size_t aOnlineEntityId);

            /**
             * @brief Construct a new Game Event object
             * @param aType the type of the event
             * @param aOnlineEntityId the online id of the entity who triggers the event
             * @param aPayload the payload of the event
             */
            explicit ClientGameEvent(ClientEventType aType, size_t aOnlineEntityId, std::vector<float> aPayload);

            /**
             * @brief Get event type
             * @return ClientEventType
             */
            ClientEventType getType() const;

            /**
             * @brief Get the online id of the entity who triggers the event
             * @return std::size_t
             */
            std::size_t getOnlineEntityId() const;

            /**
             * @brief Get the payload of the event
             * @return std::vector<float>
             */
            std::vector<float> getPayload() const;
    };
} // namespace RTypeProtocol

#endif // !