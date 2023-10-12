#ifndef UTILS_HPP
#define UTILS_HPP

namespace ECS::Utils {
    struct Vector2i
    {
            Vector2i()
                : x(0),
                  y(0)
            {}
            Vector2i(int aX, int aY)
                : x(aX),
                  y(aY)
            {}
            int x;
            int y;
    };

    struct Vector2f
    {
            Vector2f()
                : x(0),
                  y(0)
            {}
            Vector2f(float aX, float aY)
                : x(aX),
                  y(aY)
            {}
            float x;
            float y;
    };
} // namespace ECS::Utils

#endif // !
