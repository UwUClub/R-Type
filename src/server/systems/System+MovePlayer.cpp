#include <iostream>
#include "EventManager.hpp"
#include "ServerGameEvent.hpp"
#include "ServerHandler.hpp"
#include "System.hpp"
#include "Values.hpp"
#include <unordered_map>

namespace ECS {
    void System::movePlayer(Core::SparseArray<Utils::Vector2f> &aPos, Core::SparseArray<Component::Speed> &aSpeed,
                            Core::SparseArray<Component::TypeEntity> &aType)
    {
        ECS::Event::EventManager *eventManager = ECS::Event::EventManager::getInstance();
        Network::ServerHandler &network = Network::ServerHandler::getInstance();

        auto events = eventManager->getEventsByType(Event::EventType::GAME);

        for (auto &event : events) {
            auto &gameEvent = static_cast<RType::ServerGameEvent &>(*event);

            if (gameEvent.getType() == RType::ServerEventType::MOVE) {
                std::size_t entityId = static_cast<size_t>(gameEvent.getPayload()[0]);
                float moveX = gameEvent.getPayload()[1];
                float moveY = gameEvent.getPayload()[2];
                float speed = aSpeed[entityId].value().speed;

                auto &pos = aPos[entityId].value();

                if (moveX < -1 || moveX > 1 || moveY < -1 || moveY > 1) {
                    continue;
                }

                pos.x += moveX * speed;
                pos.y -= moveY * speed;

                if (pos.x < 0) {
                    pos.x = 0;
                }
                if (pos.x > SCREEN_WIDTH) {
                    pos.x = SCREEN_WIDTH;
                }
                if (pos.y < 0) {
                    pos.y = 0;
                }
                if (pos.y > SCREEN_HEIGHT) {
                    pos.y = SCREEN_HEIGHT;
                }

                network.broadcast(static_cast<int>(RType::ClientEventType::PLAYER_POSITION),
                                  {static_cast<float>(entityId), pos.x, pos.y});

                eventManager->removeEvent(event);
            }
        }
    }
} // namespace ECS
