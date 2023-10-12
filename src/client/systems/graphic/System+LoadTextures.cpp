#include "RayDisplayClass.hpp"
#include "System.hpp"

namespace ECS {
    void System::loadTextures(Core::SparseArray<Component::LoadedSprite> &aSprites)
    {
        RayDisplayClass &display = RayDisplayClass::getInstance();

        for (auto &aSprite : aSprites) {
            if (!aSprite.has_value() || aSprite.value().texture != nullptr) {
                continue;
            }
            aSprite.value().texture = display.getTexture(aSprite.value().path);
            if (aSprite.value().texture == nullptr) {
                std::cerr << "Failed to load texture: " << aSprite.value().path << std::endl;
            }
        }
    }
} // namespace ECS
