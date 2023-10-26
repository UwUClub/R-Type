#include "Timer.hpp"

#ifndef TIMER_SPAWNENEMY_HPP
    #define TIMER_SPAWNENEMY_HPP

namespace Timer {
    class TimerSpawnWall : public Timer
    {
        public:
            TimerSpawnWall()
            {}

            TimerSpawnWall(const TimerSpawnWall &) = delete;

            static TimerSpawnWall &getInstance()
            {
                static TimerSpawnWall instance;
                return instance;
            }
    };
} // namespace Timer

#endif