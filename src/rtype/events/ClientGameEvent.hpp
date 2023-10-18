#include <cstddef>
#include <vector>

#ifndef CLIENTGAMEEVENT_HPP
    #define CLIENTGAMEEVENT_HPP

namespace RType {

    enum class ClientEventType
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
    };

    /**
     * @brief Game event class is the base class of all game events
     */
    class ClientGameEvent
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
            explicit ClientGameEvent(ClientEventType aType, const std::vector<float> &aPayload);

            /**
             * @brief Get event type
             * @return ClientEventType
             */
            [[nodiscard]] ClientEventType getType() const;

            /**
             * @brief Get the payload of the event
             * @return std::vector<float>
             */
            [[nodiscard]] const std::vector<float> &getPayload() const;
    };
} // namespace RType

#endif // !
