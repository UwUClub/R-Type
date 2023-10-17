#ifndef WEIGHT_HPP_
#define WEIGHT_HPP_

#include "Values.hpp"
namespace Component {
    struct Weight
    {
            Weight()
                : weight(1),
                  fallVelocity(INITIAL_FALL_VELOCITY)
            {}
            Weight(float aWeight)
                : weight(aWeight),
                  fallVelocity(INITIAL_FALL_VELOCITY)
            {}
            void resetFallVelocity()
            {
                fallVelocity = INITIAL_FALL_VELOCITY;
            }
            float weight;
            float fallVelocity;
    };
} // namespace Component

#endif // !
