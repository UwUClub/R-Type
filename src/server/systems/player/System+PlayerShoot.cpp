#include <iostream>
#include "ServerGameEvent.hpp"
#include "ServerHandler.hpp"
#include "SparseArray.hpp"
#include "System.hpp"
#include "Values.hpp"
#include "World.hpp"

namespace ECS {
    void System::playerShoot(RType::ServerGameEvent *aEvent)
    {
        auto &world = Core::World::getInstance();
        Network::ServerHandler &server = Network::ServerHandler::getInstance();
        auto &posComp = world.getComponent<ECS::Utils::Vector2f>();
        auto &speedComp = world.getComponent<Component::Speed>();
        auto &typeComp = world.getComponent<Component::TypeEntity>();
        auto &hitBoxComp = world.getComponent<Component::HitBox>();
        auto &connectionComp = world.getComponent<Component::Connection>();

        if (aEvent->getType() == RType::ServerEventType::SHOOT) {
            const auto payload = aEvent->getPayload();
            if (payload.size() != 1) {
                return;
            }

            int playerId = static_cast<int>(payload[0]);

            if (playerId < 0 || playerId >= posComp.size()) {
                return;
            }
            if (!posComp[playerId].has_value()) {
                return;
            }

            auto pos = posComp[playerId].value();

            // Create entity
            size_t bulletId = world.createEntity();
            float posX = pos.x + BULLET_TEX_WIDTH + PLAYER_TEX_WIDTH;
            float posY = pos.y;
            posComp.insertAt(bulletId, ECS::Utils::Vector2f {posX, posY});
            speedComp.insertAt(bulletId, Component::Speed {BULLET_SPEED});
            typeComp.insertAt(bulletId, Component::TypeEntity {false, false, false, true, false, false, false});
            hitBoxComp.insertAt(bulletId, Component::HitBox {BULLET_TEX_WIDTH, BULLET_TEX_HEIGHT});

            // Send packet
            server.broadcast(static_cast<int>(RType::ClientEventType::PLAYER_SHOOT),
                             {static_cast<float>(bulletId), posX, posY}, connectionComp);
        }
    }
} // namespace ECS