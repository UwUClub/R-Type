#include <functional>
#include "EventManager.hpp"
#include "KeyboardEvent.hpp"
#include "SDLDisplayClass.hpp"
#include "System.hpp"
#include <unordered_map>

namespace ECS {
    void System::movePlayer(Core::SparseArray<Utils::Vector2f> &aPos, Core::SparseArray<Component::Speed> &aSpeed,
                            Core::SparseArray<Component::TypeEntity> &aType)
    {
        Event::EventManager *eventManager = Event::EventManager::getInstance();
        auto keyboardEvent = eventManager->getEventsByType(Event::EventType::KEYBOARD);
        static const std::unordered_map<Event::KeyIdentifier, std::function<void(float &, Utils::Vector2f &)>> keyMap =
            {
                {Event::KeyIdentifier::UP,
                 [](float &spd, Utils::Vector2f &xy) {
                     xy.y = xy.y <= 0 ? 0 : xy.y -= spd;
                 }},
                {Event::KeyIdentifier::DOWN,
                 [](float &spd, Utils::Vector2f &xy) {
                     xy.y = xy.y >= SCREEN_HEIGHT ? SCREEN_HEIGHT : xy.y += spd;
                 }},
                {Event::KeyIdentifier::LEFT,
                 [](float &spd, Utils::Vector2f &xy) {
                     xy.x = xy.x <= 0 ? 0 : xy.x -= spd;
                 }},
                {Event::KeyIdentifier::RIGHT,
                 [](float &spd, Utils::Vector2f &xy) {
                     xy.x = xy.x >= SCREEN_WIDTH ? SCREEN_WIDTH : xy.x += spd;
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
                keyMap.at(keyEvent->_keyId)(aSpeed[i].value().speed, aPos[i].value());
            }
        }
    }
} // namespace ECS