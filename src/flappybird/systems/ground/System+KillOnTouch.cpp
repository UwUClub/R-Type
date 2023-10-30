//
// Created by beafowl on 27/10/23.
//

#include "EwECS/ConfigReader/ConfigReader.hpp"
#include "EwECS/SFMLDisplayClass/RenderPlugin.hpp"
#include "SparseArray.hpp"
#include "System.hpp"
#include "Values.hpp"
#include "components/Speed.hpp"
#include "components/TypeEntity.hpp"

namespace ECS {
    void System::killOnTouch(Core::SparseArray<Utils::Vector2f> &aPos, Core::SparseArray<Component::TypeEntity> &aType)
    {
        ConfigReader &configReader = ConfigReader::getInstance();
        auto &conf = configReader.loadConfig(CONFIG_PATH);
        auto &ground1Conf = conf["entities"]["ground_1"];
        auto &ground2Conf = conf["entities"]["ground_2"];

        for (size_t i = 0; i < aPos.size(); i++) {
            if (!aPos[i].has_value() || !aType[i].has_value() || aType[i].value().type != EntityType::BIRD) {
                continue;
            }
            auto &pos = aPos[i].value();

            if (pos.y >= (ground1Conf["position"]["y"]) || pos.y >= ground2Conf["position"]["y"] || pos.y <= 0) {
                aType[i].value().type = EntityType::DEAD;
            }

            if (aType[i].value().type == EntityType::DEAD) {
                auto &speed = Core::World::getInstance().getComponent<Component::Speed>();
                auto &world = Core::World::getInstance();
                speed[i]->speed = 0;
                world.killEntity(i);
            }
        }
    }
} // namespace ECS
