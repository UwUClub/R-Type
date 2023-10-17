#ifndef JUMP_HPP_
#define JUMP_HPP_

namespace Component {
    struct Jump
    {
            Jump()
                : Jump(1)
            {}
            Jump(float aStrength)
                : strength(aStrength)
            {}
            Jump(float aStrength, float aHeight)
                : strength(aStrength),
                  height(aHeight)
            {}
            bool isJumping = false;
            float strength;
            float initialAltitude;
            float height = 100;
    };
} // namespace Component

#endif // !
