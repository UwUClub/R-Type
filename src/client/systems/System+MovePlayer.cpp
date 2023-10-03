#include <functional>
#include "EventManager.hpp"
#include "KeyboardEvent.hpp"
#include "SDLDisplayClass.hpp"
#include "System.hpp"
#include "World.hpp"
#include <unordered_map>

namespace ECS {
    void System::movePlayer(Core::SparseArray<Utils::Vector2f> &aPos, Core::SparseArray<Component::Speed> &aSpeed,
                            Core::SparseArray<Component::TypeEntity> &aType)
    {
        Event::EventManager *eventManager = Event::EventManager::getInstance();
        auto keyboardEvent = eventManager->getEventsByType(Event::EventType::KEYBOARD);
        static const std::unordered_map<Event::KeyIdentifier, std::function<void(float &, Utils::Vector2f &, Core::World &)>> keyMap =
            {
                {Event::KeyIdentifier::UP,
                 [](float &spd, Utils::Vector2f &xy, Core::World &world) {
                     xy.y = xy.y <= 0 ? 0 : xy.y -= spd * world.getDeltaTime();
                 }},
                {Event::KeyIdentifier::DOWN,
                 [](float &spd, Utils::Vector2f &xy, Core::World &world) {
                     xy.y = xy.y >= SCREEN_HEIGHT ? SCREEN_HEIGHT : xy.y += spd * world.getDeltaTime();
                 }},
                {Event::KeyIdentifier::LEFT,
                 [](float &spd, Utils::Vector2f &xy, Core::World &world) {
                     xy.x = xy.x <= 0 ? 0 : xy.x -= spd * world.getDeltaTime();
                 }},
                {Event::KeyIdentifier::RIGHT,
                 [](float &spd, Utils::Vector2f &xy, Core::World &world) {
                     xy.x = xy.x >= SCREEN_WIDTH ? SCREEN_WIDTH : xy.x += spd *  world.getDeltaTime();
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
                keyMap.at(keyEvent->_keyId)(aSpeed[i].value().speed, aPos[i].value(), Core::World::getInstance());
            }
        }
    }
} // namespace ECS