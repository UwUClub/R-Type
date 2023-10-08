#include <iostream>
#include "EventManager.hpp"
#include "ServerGameEvent.hpp"
#include "ServerHandler.hpp"
#include "SparseArray.hpp"
#include "System.hpp"
#include "Values.hpp"
#include "World.hpp"

namespace ECS {
    void System::playerShoot(Core::SparseArray<Utils::Vector2f> &aPos, Core::SparseArray<Component::Speed> &aSpeed,
                             Core::SparseArray<Component::TypeEntity> &aType,
                             Core::SparseArray<Component::HitBox> &aHitBox)
    {
        auto &world = Core::World::getInstance();
        ECS::Event::EventManager *eventManager = ECS::Event::EventManager::getInstance();
        Network::ServerHandler &server = Network::ServerHandler::getInstance();

        auto events = eventManager->getEventsByType(Event::EventType::GAME);

        for (auto &event : events) {
            auto &gameEvent = static_cast<RType::ServerGameEvent &>(*event);

            if (gameEvent.getType() == RType::ServerEventType::SHOOT) {
                size_t playerId = static_cast<size_t>(gameEvent.getPayload()[0]);
                auto &pos = aPos[playerId].value();

                // Create entity
                size_t bulletId = world.createEntity();
                auto posX = pos.x + BULLET_TEX_WIDTH; // + PLAYER_TEX_WIDTH;
                auto posY = pos.y;
                ECS::Utils::Vector2f entityPos(posX, posY);
                aPos.insertAt(bulletId, entityPos);
                aSpeed.insertAt(bulletId, Component::Speed {BULLET_SPEED});
                aType.insertAt(bulletId, Component::TypeEntity {false, false, false, true, false, false, false});
                aHitBox.insertAt(bulletId, Component::HitBox {BULLET_TEX_WIDTH, BULLET_TEX_HEIGHT});

                // Send packet
                server.broadcast(static_cast<int>(RType::ClientEventType::PLAYER_SHOOT),
                                 {static_cast<float>(bulletId), posX, posY});

                // Delete event
                eventManager->removeEvent(event);
            }
        }
    }
} // namespace ECS