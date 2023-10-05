#include <chrono>

#ifndef TIMER_HPP
    #define TIMER_HPP

namespace Timer {
    class Timer
    {
        private:
            float _value;

        public:
            Timer() = default;

            ~Timer() = default;

            /**
             * @brief Get the value of the timer
             * @return The value
             */
            [[nodiscard]] float get() const;

            /**
             * @brief Increment a value to the timer
             * @param aValue value to increment
             */
            void add(float);

            /**
             * @brief Reset the timer
             */
            void reset();
    };

} // namespace Timer

#endif