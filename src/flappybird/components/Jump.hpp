#ifndef JUMP_HPP_
#define JUMP_HPP_

namespace Component {
    struct Jump
    {
            Jump()
                : strength(0),
                  height(0),
                  floating(0),
                  isJumping(false),
                  initialAltitude(0)
            {}
            Jump(float aStrength, float aHeight, float aFloating)
                : strength(aStrength),
                  height(aHeight),
                  floating(aFloating),
                  isJumping(false),
                  initialAltitude(0)
            {}

            float strength;
            float height;
            float floating;
            bool isJumping;
            float initialAltitude;
    };
} // namespace Component

#endif // !
