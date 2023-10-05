#include "Timer.hpp"

namespace Timer {
    float Timer::get() const
    {
        return _value;
    }

    void Timer::add(float aValue)
    {
        _value += aValue;
    }

    void Timer::reset()
    {
        _value = float(0);
    }
} // namespace Timer
