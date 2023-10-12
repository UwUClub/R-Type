#include "Components.hpp"
#include "Event.hpp"
#include "EventManager.hpp"
#include "Packets.hpp"
#include "ServerGameEvent.hpp"
#include "ServerHandler.hpp"
#include "System.hpp"
#include "World.hpp"

namespace ECS {
    void System::moveSpeedUp(Core::SparseArray<Component::Speed> &aSpeed,
                             Core::SparseArray<Component::Connection> &aConnection)
    {
        ECS::Core::World const &world = ECS::Core::World::getInstance();
        ECS::Event::EventManager *eventManager = ECS::Event::EventManager::getInstance();
        Network::ServerHandler &network = Network::ServerHandler::getInstance();
        auto events = eventManager->getEventsByType(Event::EventType::GAME);

        for (auto &event : events) {
            auto &gameEvent = static_cast<RType::ServerGameEvent &>(*event);
            if (gameEvent.getType() == RType::ServerEventType::BONUS) {
                auto playerId = static_cast<size_t>(gameEvent.getEntityId());
                float const bonusType = gameEvent.getPayload()[0];

                if (bonusType == 1) {
                    aSpeed[playerId].value().speed += 10;
                    network.broadcast(static_cast<int>(RType::ClientEventType::PLAYER_BONUS),
                                      {static_cast<float>(playerId), 1}, aConnection);
                }
                eventManager->removeEvent(event);
            }
        }
    }
} // namespace ECS