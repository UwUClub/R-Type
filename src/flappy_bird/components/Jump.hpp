#ifndef JUMP_HPP_
#define JUMP_HPP_

namespace ECS::Utils {
    struct Jump
    {
            Jump()
                : Jump(1)
            {}
            Jump(int aStrength)
                : strength(aStrength)
            {}
            Jump(int aStrength, float aHeight)
                : strength(aStrength),
                  height(aHeight)
            {}
            bool isJumping = false;
            int strength;
            float initialAltitude;
            float height = 100;
    };
} // namespace ECS::Utils

#endif // !
