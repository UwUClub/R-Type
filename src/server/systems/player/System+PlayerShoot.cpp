#include <cstddef>
#include <iostream>
#include <vector>
#include "ClientGameEvent.hpp"
#include "EwECS/Event/EventManager.hpp"
#include "EwECS/SparseArray.hpp"
#include "EwECS/World.hpp"
#include "ServerGameEvent.hpp"
#include "ServerHandler.hpp"
#include "ServerPackets.hpp"
#include "System.hpp"
#include "Values.hpp"

namespace ECS {
    void System::playerShoot(Core::SparseArray<Utils::Vector2f> &aPos, Core::SparseArray<Component::Speed> &aSpeed,
                             Core::SparseArray<Component::TypeEntity> &aType,
                             Core::SparseArray<Component::HitBox> &aHitBox,
                             Core::SparseArray<Component::Connection> &aConnection)
    {
        auto &world = Core::World::getInstance();
        ECS::Event::EventManager *eventManager = ECS::Event::EventManager::getInstance();
        Network::ServerHandler &server = Network::ServerHandler::getInstance();
        auto &events = eventManager->getEventsByType<RType::ServerGameEvent>();
        const auto size = events.size();
        std::vector<size_t> toRemove;

        for (size_t i = 0; i < size; i++) {
            auto &gameEvent = events[i];

            if (gameEvent.getType() != RType::ServerEventType::SHOOT) {
                continue;
            }

            const auto playerId = gameEvent.getEntityId();
            auto &pos = aPos[playerId].value();

            // Create entity
            auto bulletId = world.createEntity();
            float posX = pos.x + BULLET_TEX_WIDTH + PLAYER_TEX_WIDTH;
            float posY = pos.y;

            aPos.insertAt(bulletId, ECS::Utils::Vector2f {posX, posY});
            aSpeed.insertAt(bulletId, Component::Speed {BULLET_SPEED});
            aType.insertAt(bulletId, Component::TypeEntity {false, false, false, true, false, false, false});
            aHitBox.insertAt(bulletId, Component::HitBox {BULLET_TEX_WIDTH, BULLET_TEX_HEIGHT});

            // Send packet
            RType::Server::PlayerShotPayload payloadToSend(bulletId, posX, posY);
            server.broadcast(RType::ClientEventType::PLAYER_SHOOT, payloadToSend, aConnection);

            toRemove.push_back(i);
        }
        eventManager->removeEvent<RType::ServerGameEvent>(toRemove);
    }
} // namespace ECS
