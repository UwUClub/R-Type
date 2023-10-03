#include <functional>
#include "EventManager.hpp"
#include "KeyboardEvent.hpp"
#include "SDLDisplayClass.hpp"
#include "System.hpp"
#include "Values.hpp"
#include <unordered_map>

namespace ECS {
    void System::shootMissiles(Core::SparseArray<Utils::Vector2f> &aPos,
                               Core::SparseArray<Component::TypeEntity> &aType)
    {
        Event::EventManager *eventManager = Event::EventManager::getInstance();
        auto keyboardEvent = eventManager->getEventsByType(Event::EventType::KEYBOARD);
        static const std::unordered_map<Event::KeyIdentifier, std::function<void(Utils::Vector2f &, SDLDisplayClass &)>>
            keyMap = {
                {Event::KeyIdentifier::SPACE,
                 [](Utils::Vector2f &xy, SDLDisplayClass &display) {
                     display.addEntity(
                         ECS::Utils::Vector2f {xy.x + 30, xy.y}, Component::Speed {BULLET_SPEED},
                         Component::TypeEntity {false, false, true, false, false, false},
                         Component::LoadedSprite {BULLET_ASSET, nullptr,
                                                  new SDL_Rect {207, 10, BULLET_TEX_WIDTH, BULLET_TEX_HEIGHT},
                                                  new SDL_Rect {0, 0, BULLET_TEX_WIDTH, BULLET_TEX_HEIGHT}});
                 }},
            };

        for (size_t i = 0; i < aPos.size(); i++) {
            if (!aType[i].has_value() || !aType[i].value().isPlayer) {
                continue;
            }
            for (auto &event : keyboardEvent) {
                auto *keyEvent = static_cast<Event::KeyboardEvent *>(event);
                if (keyMap.find(keyEvent->_keyId) == keyMap.end()) {
                    std::cerr << "Key not found" << std::endl;
                    continue;
                }
                keyMap.at(keyEvent->_keyId)(aPos[i].value(), SDLDisplayClass::getInstance());
            }
        }
    }
} // namespace ECS