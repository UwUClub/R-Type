
#include <string>
#include <SDL_render.h>

#ifndef SPEED_HPP
    #define SPEED_HPP

namespace Component {
    struct Speed
    {
            /**
             * @brief Construct a new Speed object
             *
             */
            Speed()
                : speed(0)
            {}
            /**
             * @brief Construct a new Speed object
             *
             * @param aSpeed The speed of the entity
             */
            explicit Speed(float aSpeed)
                : speed(aSpeed)
            {}
            float speed;
    };
} // namespace Component
#endif // DEBUG