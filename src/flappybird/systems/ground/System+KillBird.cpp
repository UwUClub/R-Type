//
// Created by beafowl on 27/10/23.
//

#include "EwECS/ConfigReader/ConfigReader.hpp"
#include "EwECS/Physic/PhysicPlugin.hpp"
#include "EwECS/SFMLDisplayClass/RenderPlugin.hpp"
#include "SparseArray.hpp"
#include "System.hpp"
#include "Values.hpp"
#include "components/Speed.hpp"
#include "components/TypeEntity.hpp"

namespace ECS {
    void System::killBird()
    {
        ECS::Core::World &world = ECS::Core::World::getInstance();
        auto &hitbox = world.getComponent<Component::HitBox>();
        auto &type = world.getComponent<Component::TypeEntity>();
        size_t typeSize = type.size();

        for (size_t birdId = 0; birdId < typeSize; birdId++) {
            if (!type[birdId].has_value() || type[birdId].value().type != EntityType::BIRD
                || !hitbox[birdId].has_value() || !hitbox[birdId].value().isColliding) {
                continue;
            }
            auto &colliders = hitbox[birdId].value().collidingId;
            for (auto &collider : colliders) {
                if (!type[collider].has_value()) {
                    continue;
                }
                auto &colliderType = type[collider].value().type;
                if (colliderType != EntityType::GROUND && colliderType != EntityType::PIPE) {
                    continue;
                }
                world.killEntity(birdId);
            }
        }
    }
} // namespace ECS
