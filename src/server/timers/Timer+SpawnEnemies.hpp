#include "Timer.hpp"

#ifndef TIMER_SPAWNENEMIES_HPP
    #define TIMER_SPAWNENEMIES_HPP

namespace Timer {
    class TimerSpawnEnemies : public Timer
    {
        public:
            TimerSpawnEnemies()
            {}

            TimerSpawnEnemies(const TimerSpawnEnemies &) = delete;

            static TimerSpawnEnemies &getInstance()
            {
                static TimerSpawnEnemies instance;
                return instance;
            }
    };
} // namespace Timer

#endif