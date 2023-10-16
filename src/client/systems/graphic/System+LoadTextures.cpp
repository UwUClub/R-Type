#include "RayDisplayClass.hpp"
#include "System.hpp"

namespace ECS {
    void System::loadTextures(Core::SparseArray<Raylib::Sprite> &aSprites)
    {
        RayDisplayClass &display = RayDisplayClass::getInstance();

        for (auto &aSprite : aSprites) {
            if (!aSprite.has_value() || aSprite.value()._texture != nullptr) {
                continue;
            }
            aSprite.value()._texture = display.getTexture(aSprite.value()._fileName);
            if (aSprite.value()._texture == nullptr) {
                std::cerr << "Failed to load texture: " << aSprite.value()._fileName << std::endl;
            }
        }
    }
} // namespace ECS
