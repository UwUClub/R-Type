#include "SDLDisplayClass.hpp"
#include "SparseArray.hpp"
#include "System.hpp"
#include <SDL_image.h>

namespace ECS {
    void System::moveBase(Core::SparseArray<Utils::Vector2f> &aPos, Core::SparseArray<Component::Speed> &aSpeed,
                          Core::SparseArray<Component::TypeEntity> &aType)
    {
        SDLDisplayClass &display = SDLDisplayClass::getInstance();
        auto &graphicsConf = ConfigReader::getInstance().get()["graphics"];
        float screenWidth = graphicsConf["width"];

        for (size_t i = 0; i < aPos.size(); i++) {
            if (!aPos[i].has_value() || !aType[i].has_value() || !aSpeed[i].has_value()
                || aType[i].value().type != EntityType::BASE) {
                continue;
            }
            aPos[i].value().x -= aSpeed[i].value().speed * Core::World::getInstance().getDeltaTime();
            if (aPos[i].value().x <= -screenWidth) {
                aPos[i].value().x = screenWidth;
            }
        }
    }
} // namespace ECS
