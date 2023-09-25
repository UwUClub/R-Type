#include "System.hpp"
#include "EventManager.hpp"
#include "KeyboardEvent.hpp"

namespace ECS {
    void System::movePlayer(Core::World &world, Core::SparseArray<ECS::Utils::Vector2f> &pos,
    Core::SparseArray<ECS::Utils::Speed> &speed, Core::SparseArray<ECS::Utils::TypeEntity> &type)
    {
        Event::EventManager *eventManager = Event::EventManager::getInstance();
        auto keyboardEvent = eventManager->getEventsByType(Event::EventType::KEYBOARD);

        for (size_t i = 0; i < pos.size(); i++) {
            if (!type[i].has_value() || !type[i].value().isPlayer) {
                continue;
            }
            for (auto event : keyboardEvent) {
                auto keyEvent = static_cast<Event::KeyboardEvent &>(event);
                if (keyEvent._keyId == Event::KeyIdentifier::UP)
                    pos[i].value().y -= speed[i].value().speed;
                if (keyEvent._keyId == Event::KeyIdentifier::DOWN)
                    pos[i].value().y += speed[i].value().speed;
                if (keyEvent._keyId == Event::KeyIdentifier::LEFT)
                    pos[i].value().x -= speed[i].value().speed;
                if (keyEvent._keyId == Event::KeyIdentifier::RIGHT)
                    pos[i].value().x += speed[i].value().speed;
            }
        }
    }
}