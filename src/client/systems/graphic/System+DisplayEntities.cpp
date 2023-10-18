#include "KeyboardEvent.hpp"
#include "SFMLDisplayClass.hpp"
#include "System.hpp"

namespace ECS {
    void System::displayEntities(Core::SparseArray<Component::LoadedSprite> &aSprites,
                                 Core::SparseArray<Utils::Vector2f> &aPos)
    {
        SFMLDisplayClass &display = SFMLDisplayClass::getInstance();

        display._window.clear(sf::Color::Black);
        for (size_t i = 0; i < aSprites.size(); i++) {
            if (!aSprites[i].has_value() || aSprites[i]->texture == nullptr) {
                continue;
            }
            if (!aPos[i].has_value()) {
                continue;
            }
            if (aSprites[i]->srcRect != nullptr) {
                sf::Sprite sprite;
                sprite.setTexture(*aSprites[i]->texture);
                sprite.setTextureRect(*aSprites[i]->rect);
                sprite.setPosition(aPos[i].value().x, aPos[i].value().y);
                sprite.scale(aSprites[i]->scale, aSprites[i]->scale);
                display._window.draw(sprite);
            }
        }
        display._window.display();
    }
} // namespace ECS
