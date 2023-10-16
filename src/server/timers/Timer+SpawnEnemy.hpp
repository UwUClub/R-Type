#include "Timer.hpp"

#ifndef TIMER_SPAWNENEMY_HPP
    #define TIMER_SPAWNENEMY_HPP

namespace Timer {
    class TimerSpawnEnemy : public Timer
    {
        public:
            TimerSpawnEnemy()
            {}

            TimerSpawnEnemy(const TimerSpawnEnemy &) = delete;

            static TimerSpawnEnemy &getInstance()
            {
                static TimerSpawnEnemy instance;
                return instance;
            }
    };
} // namespace Timer

#endif