#ifndef PLAYERMOVESTATE_HPP_
#define PLAYERMOVESTATE_HPP_

struct PlayerMoveState
{
        PlayerMoveState() = default;
        ~PlayerMoveState() = default;

        static PlayerMoveState &getInstance()
        {
            static PlayerMoveState instance;
            return instance;
        }

        bool runningX = false;
        bool runningY = false;
        float speedX = 0;
        float speedY = 0;
};

#endif /* !PLAYERMOVESTATE_HPP_ */
