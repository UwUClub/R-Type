#include <functional>
#include "ClientHandler.hpp"
#include "EwECS/Event/EventManager.hpp"
#include "EwECS/Event/KeyboardEvent.hpp"
#include "EwECS/SFMLDisplayClass/SFMLDisplayClass.hpp"
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
        auto &keyboardEvent = eventManager->getEventsByType<Event::KeyboardEvent>();
        const auto size = aPos.size();

        for (size_t i = 0; i < size; i++) {
            if (!aType[i].has_value() || !aType[i].value().isPlayer || !aIsAlive[i].has_value()
                || !aIsAlive[i].value().isAlive) {
                continue;
            }
            for (auto &event : keyboardEvent) {
                if (event._keyId == Event::KeyIdentifier::SPACE) {
                    int playerOnlineId = aType[i].value().onlineId.value_or(-1);

                    if (playerOnlineId == -1) {
                        continue;
                    }
                    RType::Packet packet(static_cast<int>(RType::ServerEventType::SHOOT),
                                         {static_cast<float>(playerOnlineId)});
                    client.send(packet);
                }
            }
        }
    }
} // namespace ECS
