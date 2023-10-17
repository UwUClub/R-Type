#ifndef WEIGHT_HPP_
#define WEIGHT_HPP_

#include "ConfigReader.hpp"
#include "Values.hpp"

namespace Component {
    struct Weight
    {
            Weight()
                : weight(0),
                  initialFallVelocity(0),
                  fallVelocity(0)
            {}
            Weight(float aWeight, float aFallVelocity)
                : weight(aWeight),
                  initialFallVelocity(aFallVelocity),
                  fallVelocity(aFallVelocity)
            {}
            void resetFallVelocity()
            {
                fallVelocity = initialFallVelocity;
            }
            float weight;
            float initialFallVelocity;
            float fallVelocity;
    };
} // namespace Component

#endif // !
