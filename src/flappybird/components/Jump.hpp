#ifndef JUMP_HPP_
#define JUMP_HPP_

namespace Component {
    struct Jump
    {
            Jump()
                : isJumping(false),
                  initialAltitude(0)
            {}
            Jump(float aStrength, float aHeight, float aFloating)
                : isJumping(false),
                  initialAltitude(0),
                  strength(aStrength),
                  height(aHeight),
                  floating(aFloating)
            {}
            float strength;
            float height;
            float floating;
            bool isJumping;
            float initialAltitude;
    };
} // namespace Component

#endif // !
