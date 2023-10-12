#include <iostream>
#include "ServerGameEvent.hpp"
#include "ServerHandler.hpp"
#include "SparseArray.hpp"
#include "System.hpp"
#include "Values.hpp"
#include <unordered_map>

namespace ECS {
    void System::movePlayer(RType::ServerGameEvent *aEvent)
    {
        Network::ServerHandler &network = Network::ServerHandler::getInstance();
        auto &world = ECS::Core::World::getInstance();
        auto &posComp = world.getComponent<ECS::Utils::Vector2f>();
        auto &speedComp = world.getComponent<Component::Speed>();
        auto &connectionComp = world.getComponent<Component::Connection>();

        if (aEvent->getType() == RType::ServerEventType::MOVE) {
            // Check payload size
            const auto payload = aEvent->getPayload();
            if (payload.size() != 3) {
                return;
            }

            // Get and check entity ID
            int entityId = static_cast<int>(payload[0]);
            if (entityId < 0 || entityId >= posComp.size() || !posComp[entityId].has_value()
                || !speedComp[entityId].has_value()) {
                return;
            }

            // Get and check move values
            float moveX = payload[1];
            float moveY = payload[2];
            if (moveX < -1 || moveX > 1 || moveY < -1 || moveY > 1) {
                return;
            }

            // Move player
            float speed = speedComp[entityId].value().speed;
            auto &pos = posComp[entityId].value();

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
                              {static_cast<float>(entityId), pos.x, pos.y}, connectionComp);
        }
    }
} // namespace ECS
