#include <functional>
#include "ClientHandler.hpp"
#include "EventManager.hpp"
#include "KeyboardEvent.hpp"
#include "SDLDisplayClass.hpp"
#include "System.hpp"
#include "Values.hpp"
#include <unordered_map>

namespace ECS {
    void System::triggerPlayerShoot(Core::SparseArray<Utils::Vector2f> &aPos,
                                    Core::SparseArray<Component::TypeEntity> &aType,
                                    Core::SparseArray<Component::IsAlive> &aIsAlive)
    {
        Network::ClientHandler &client = Network::ClientHandler::getInstance();
        Event::EventManager *eventManager = Event::EventManager::getInstance();
        auto keyboardEvent = eventManager->getEventsByType(Event::EventType::KEYBOARD);

        for (size_t i = 0; i < aPos.size(); i++) {
            if (!aType[i].has_value() || !aType[i].value().isPlayer || !aIsAlive[i].value().isAlive) {
                continue;
            }
            for (auto &event : keyboardEvent) {
                auto *keyEvent = static_cast<Event::KeyboardEvent *>(event);

                if (keyEvent->_keyId == Event::KeyIdentifier::SPACE) {
                    RType::Packet packet(static_cast<int>(RType::ClientEventType::PLAYER_SHOOT),
                                         {static_cast<float>(aType[i].value().onlineId.value_or(0))});
                    client.send(packet);
                }
            }
        }
    }
} // namespace ECS