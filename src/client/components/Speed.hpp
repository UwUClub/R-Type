
#include <string>
#include <SDL_render.h>

#ifndef SPEED_HPP
    #define SPEED_HPP

namespace Component {
    struct Speed
    {
            Speed()
                : speed(0)
            {}
            explicit Speed(float aSpeed)
                : speed(aSpeed)
            {}
            float speed;
    };
} // namespace Component
#endif // DEBUG