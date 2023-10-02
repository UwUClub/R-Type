#include "System.hpp"
#include <functional>
#include "EventManager.hpp"
#include "KeyboardEvent.hpp"
#include "SDLDisplayClass.hpp"
#include <unordered_map>

namespace ECS {
    void System::movePlayer(Core::World &world, Core::SparseArray<Utils::Vector2f> &aPos,
                            Core::SparseArray<Utils::Speed> &aSpeed, Core::SparseArray<Utils::TypeEntity> &aType)
    {
        Event::EventManager *eventManager = Event::EventManager::getInstance();
        auto keyboardEvent = eventManager->getEventsByType(Event::EventType::KEYBOARD);
        static const std::unordered_map<const Event::KeyIdentifier, std::function<void(float &, Utils::Vector2f &)>> keyMap = {
            {Event::KeyIdentifier::UP, [](float &spd, Utils::Vector2f &xy) { xy.y = xy.y <= 0 ? 0 : xy.y -= spd; }},
            {Event::KeyIdentifier::DOWN, [](float &spd, Utils::Vector2f &xy) { xy.y = xy.y >= SCREEN_HEIGHT ? SCREEN_HEIGHT : xy.y += spd; }},
            {Event::KeyIdentifier::LEFT, [](float &spd, Utils::Vector2f &xy) { xy.x = xy.x <= 0 ? 0 : xy.x -= spd; }},
            {Event::KeyIdentifier::RIGHT, [](float &spd, Utils::Vector2f &xy) { xy.x = xy.x >= SCREEN_WIDTH ? SCREEN_WIDTH : xy.x += spd; }},
        };

        for (size_t i = 0; i < aPos.size(); i++) {
            if (!aType[i].has_value() || !aType[i].value().isPlayer) {
                continue;
            }
            for (auto event : keyboardEvent) {
                auto keyEvent = static_cast<Event::KeyboardEvent *>(event);
                keyMap.at(keyEvent->_keyId)(aSpeed[i].value().speed, aPos[i].value());
            }
        }
    }
}