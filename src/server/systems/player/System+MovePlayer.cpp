#include <iostream>
#include "EventManager.hpp"
#include "ServerGameEvent.hpp"
#include "ServerHandler.hpp"
#include "SparseArray.hpp"
#include "System.hpp"
#include "Values.hpp"
#include <unordered_map>

namespace ECS {
    void System::movePlayer(Core::SparseArray<Utils::Vector2f> &aPos, Core::SparseArray<Component::Speed> &aSpeed,
                            Core::SparseArray<Component::Connection> &aConnection)
    {
        ECS::Event::EventManager *eventManager = ECS::Event::EventManager::getInstance();
        Network::ServerHandler &network = Network::ServerHandler::getInstance();

        auto &events = eventManager->getEventsByType<RType::ServerGameEvent>();

        for (size_t i = 0; i < events.size(); i++) {
            auto &gameEvent = events[i];

            if (gameEvent.getType() == RType::ServerEventType::MOVE) {
                // Check payload size
                if (gameEvent.getPayload().size() != 3) {
                    eventManager->removeEvent<RType::ServerGameEvent>(i);
                    continue;
                }

                // Get and check entity ID
                int entityId = static_cast<int>(gameEvent.getPayload()[0]);
                if (entityId < 0 || entityId >= aPos.size() || !aPos[entityId].has_value()
                    || !aSpeed[entityId].has_value()) {
                    eventManager->removeEvent<RType::ServerGameEvent>(i);
                    continue;
                }

                // Get and check move values
                float moveX = gameEvent.getPayload()[1];
                float moveY = gameEvent.getPayload()[2];
                if (moveX < -1 || moveX > 1 || moveY < -1 || moveY > 1) {
                    eventManager->removeEvent<RType::ServerGameEvent>(i);
                    continue;
                }

                // Move player
                float speed = aSpeed[entityId].value().speed;
                auto &pos = aPos[entityId].value();

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
                                  {static_cast<float>(entityId), pos.x, pos.y}, aConnection);

                eventManager->removeEvent<RType::ServerGameEvent>(i);
            }
        }
    }
} // namespace ECS
