#ifndef WEIGHT_HPP_
#define WEIGHT_HPP_

#include "ConfigReader.hpp"
#include "Values.hpp"
namespace Component {
    struct Weight
    {
            Weight()
                : weight(1),
                  fallVelocity(0)
            {
                resetFallVelocity();
            }
            Weight(float aWeight)
                : weight(aWeight),
                  fallVelocity(0)
            {
                resetFallVelocity();
            }
            void resetFallVelocity()
            {
                auto &physicsConf = ConfigReader::getInstance().getPhysics();
                fallVelocity = (float) physicsConf["initial_fall_velocity"];
            }
            float weight;
            float fallVelocity;
    };
} // namespace Component

#endif // !
