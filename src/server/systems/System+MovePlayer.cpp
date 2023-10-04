#include <iostream>
#include "EventManager.hpp"
#include "ServerGameEvent.hpp"
#include "ServerNetworkHandler.hpp"
#include "System.hpp"
#include "Values.hpp"
#include <unordered_map>

namespace ECS {
    void System::movePlayer(Core::SparseArray<Utils::Vector2f> &aPos, Core::SparseArray<Component::Speed> &aSpeed,
                            Core::SparseArray<Component::TypeEntity> &aType)
    {
        ECS::Event::EventManager *eventManager = ECS::Event::EventManager::getInstance();
        Network::ServerNetworkHandler &network = Network::ServerNetworkHandler::getInstance();

        auto events = eventManager->getEventsByType(Event::EventType::GAME);

        for (auto &event : events) {
            auto &gameEvent = static_cast<RType::ServerGameEvent &>(*event);

            if (gameEvent.getType() == RType::ServerEventType::MOVE) {
                std::size_t entityId = static_cast<size_t>(gameEvent.getPayload()[0]);
                float moveX = gameEvent.getPayload()[1];
                float moveY = gameEvent.getPayload()[2];
                float speed = aSpeed[entityId].value().speed;

                if (moveX < -1 || moveY > 1 || moveY < -1 || moveY > 1) {
                    continue;
                }

                aPos[entityId].value().x += moveX * speed;
                aPos[entityId].value().y -= moveY * speed;

                // std::cout << entityId << " pos: " << aPos[gameEvent.getEntityId()].value().x << " "
                //           << aPos[gameEvent.getEntityId()].value().y << std::endl;

                network.broadcast(static_cast<int>(RType::ClientEventType::PLAYER_POSITION),
                                  {static_cast<float>(entityId), aPos[entityId].value().x, aPos[entityId].value().y});

                eventManager->removeEvent(event);
            }
        }
    }
} // namespace ECS
