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

        for (size_t birdId = 0; birdId < type.size(); birdId++) {
            if (!type[birdId].has_value() || type[birdId].value().type != EntityType::BIRD
                || !hitbox[birdId].has_value() || !hitbox[birdId].value().isColliding) {
                continue;
            }
            auto &colliderId = hitbox[birdId].value().collidingId;
            if (!type[colliderId].has_value()) {
                continue;
            }
            auto &colliderType = type[colliderId].value().type;
            if (colliderType != EntityType::GROUND && colliderType != EntityType::PIPE) {
                continue;
            }
            world.killEntity(birdId);
            // if (!aPos[i].has_value() || !aType[i].has_value() || aType[i].value().type != EntityType::BIRD) {
            //     continue;
            // }
            // auto &pos = aPos[i].value();

            // if (pos.y >= (ground1Conf["position"]["y"]) || pos.y >= ground2Conf["position"]["y"] || pos.y <= 0) {
            //     aType[i].value().type = EntityType::DEAD;
            // }

            // if (aType[i].value().type == EntityType::DEAD) {
            //     auto &speed = Core::World::getInstance().getComponent<Component::Speed>();
            //     auto &world = Core::World::getInstance();
            //     speed[i]->speed = 0;
            //     world.killEntity(i);
            // }
        }
    }
} // namespace ECS
