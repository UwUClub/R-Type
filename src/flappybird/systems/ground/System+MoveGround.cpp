#include "EwECS/SFMLDisplayClass/RenderPlugin.hpp"
#include "SparseArray.hpp"
#include "System.hpp"

namespace ECS {
    void System::moveGround(Core::SparseArray<Utils::Vector2f> &aPos, Core::SparseArray<Component::Speed> &aSpeed,
                            Core::SparseArray<Component::TypeEntity> &aType)
    {
        auto screenWidth = static_cast<float>(Render::RenderPluginConfig::getInstance()._windowWidth);

        for (size_t i = 0; i < aPos.size(); i++) {
            if (!aPos[i].has_value() || !aType[i].has_value() || !aSpeed[i].has_value()
                || aType[i].value().type != EntityType::GROUND) {
                continue;
            }
            auto &pos = aPos[i].value();
            auto &speed = aSpeed[i].value().speed;

            pos.x -= speed * Core::World::getInstance().getDeltaTime();
            if (pos.x <= -screenWidth) {
                pos.x = screenWidth;
            }
        }
    }
} // namespace ECS
