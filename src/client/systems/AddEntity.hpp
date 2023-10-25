#ifndef ADDENTITY_HPP_
#define ADDENTITY_HPP_

#include "Components.hpp"
#include "EwECS/SFMLDisplayClass/LoadedSprite.hpp"
#include "EwECS/Utils.hpp"
#include "EwECS/Physic/HitBox.hpp"

class AddEntity
{
    public:
        /**
         * @brief Create a new entity object
         *
         * @param aPos Position of the entity
         * @param aSpeed Speed of the entity
         * @param aType Type of the entity
         * @param aSprite Sprite of the entity
         * @param aHitBox Hitbox of the entity
         * @param aIsAlive IsAlive of the entity
         * @return size_t The index of the entity
         */
        static size_t addEntity(ECS::Utils::Vector2f aPos, Component::Speed aSpeed, Component::TypeEntity aType,
                                Component::LoadedSprite aSprite, Component::HitBox aHitBox,
                                Component::IsAlive aIsAlive);
};

#endif /* !ADDENTITY_HPP_ */
