#ifndef UTILS_HPP
#define UTILS_HPP

namespace ECS::Utils {
    struct Vector2i
    {
                Vector2i(int x, int y) : x(x), y(y) {}
            int x;
            int y;
    };

    struct Vector2f
    {
                Vector2f(float x, float y) : x(x), y(y) {}
            float x;
            float y;
    };
} // namespace ECS::Utils

#endif // !
