#include "EwECS/Event/KeyboardEvent.hpp"
#include "SFMLDisplayClass.hpp"
#include "System.hpp"

namespace ECS {
    void System::displayEntities(Core::SparseArray<Component::LoadedSprite> &aSprites,
                                 Core::SparseArray<Utils::Vector2f> &aPos)
    {
        SFMLDisplayClass &display = SFMLDisplayClass::getInstance();
        const auto size = aSprites.size();

        display._window.clear(sf::Color::Black);
        for (size_t i = 0; i < size; i++) {
            if (!aSprites[i].has_value() || aSprites[i]->texture == nullptr) {
                continue;
            }
            if (!aPos[i].has_value()) {
                continue;
            }

            auto &spriteData = aSprites[i].value();
            auto &pos = aPos[i].value();

            if (spriteData.srcRect != nullptr) {
                sf::Sprite sprite;

                sprite.setTexture(*spriteData.texture);
                sprite.setTextureRect(*spriteData.rect);
                sprite.setPosition(pos.x, pos.y);
                sprite.scale(spriteData.scale, spriteData.scale);
                display._window.draw(sprite);
            }
        }
        display._window.display();
    }
} // namespace ECS
