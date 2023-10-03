#ifndef HITBOX_HPP_
    #define HITBOX_HPP_

namespace Component {
    struct HitBox {
        /**
         * @brief Construct a new Hit Box object
         * 
         */
        HitBox()
            : width(0),
              height(0)
        {}
        /**
         * @brief Construct a new Hit Box object
         * 
         * @param aWidth Width of the hitbox
         * @param aHeight Height of the hitbox
         */
        HitBox(float aWidth, float aHeight)
            : width(aWidth),
              height(aHeight)
        {}
        float width;
        float height;
    };
} // namespace Component


#endif /* !HITBOX_HPP_ */
