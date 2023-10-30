#include "EwECS/SFMLDisplayClass/RenderPlugin.hpp"
#include "SparseArray.hpp"
#include "System.hpp"

namespace ECS {
    void System::moveGround()
    {
        auto screenWidth = static_cast<float>(Render::RenderPluginConfig::getInstance()._windowWidth);
        auto &world = Core::World::getInstance();
        auto &pos = world.getComponent<Utils::Vector2f>();
        auto &type = world.getComponent<Component::TypeEntity>();
        auto &speed = world.getComponent<Component::Speed>();

        for (size_t i = 0; i < pos.size(); i++) {
            if (!pos[i].has_value() || !type[i].has_value() || !speed[i].has_value()) {
                continue;
            }
            auto &typeVal = type[i].value().type;
            if (typeVal != EntityType::GROUND && typeVal != EntityType::PIPE) {
                continue;
            }
            auto &posVal = pos[i].value();
            auto &speedVal = speed[i].value().speed;

            posVal.x -= speedVal * Core::World::getInstance().getDeltaTime();
            if (posVal.x <= -screenWidth) {
                posVal.x = screenWidth;
            }
        }
    }
} // namespace ECS
