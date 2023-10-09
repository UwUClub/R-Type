#include <iostream>
#include "Components.hpp"
#include "Event.hpp"
#include "EventManager.hpp"
#include "HitBox.hpp"
#include "Packets.hpp"
#include "ServerGameEvent.hpp"
#include "ServerHandler.hpp"
#include "SparseArray.hpp"
#include "System.hpp"
#include "Values.hpp"
#include "World.hpp"

namespace ECS {
    void System::welcomePlayer(Core::SparseArray<Utils::Vector2f> &aPos, Core::SparseArray<Component::Speed> &aSpeed,
                               Core::SparseArray<Component::TypeEntity> &aType, Core::SparseArray<Component::HitBox> &aHitBox)
    {
        ECS::Core::World &world = ECS::Core::World::getInstance();
        ECS::Event::EventManager *eventManager = ECS::Event::EventManager::getInstance();
        Network::ServerHandler &network = Network::ServerHandler::getInstance();
        auto events = eventManager->getEventsByType(Event::EventType::GAME);

        for (auto &event : events) {
            auto &gameEvent = static_cast<RType::ServerGameEvent &>(*event);
            if (gameEvent.getType() == RType::ServerEventType::CONNECT) {
                size_t playerId = world.createEntity();
                float playerColor = static_cast<float>(network.getNumberClients());

                aPos.insertAt(playerId, ECS::Utils::Vector2f {10, 10});
                aSpeed.insertAt(playerId, Component::Speed {PLAYER_SPEED});
                aType.insertAt(playerId, Component::TypeEntity {true, false, false, false, false, false, false});
                aHitBox.insertAt(playerId, Component::HitBox{PLAYER_TEX_WIDTH, PLAYER_TEX_HEIGHT});
                
                network.broadcast(static_cast<int>(RType::ClientEventType::PLAYER_SPAWN),
                                  {static_cast<float>(playerId), 0, playerColor, 10, 10});
                network.addClient(playerId, gameEvent.getClientEndpoint());
                network.send(RType::Packet(static_cast<int>(RType::ClientEventType::PLAYER_SPAWN),
                                           {static_cast<float>(playerId), 1, playerColor, 10, 10}),
                             playerId);

                int aPosSize = aPos.size();
                for (std::size_t i = 0; i < aPosSize; i++) {
                    if (!aType[i].has_value() || !aPos[i].has_value()) {
                        continue;
                    }
                    if (i != playerId && aType[i]->isPlayer) {
                        network.send(RType::Packet(static_cast<int>(RType::ClientEventType::PLAYER_SPAWN),
                                                   {static_cast<float>(i), 0, playerColor, aPos[i]->x, aPos[i]->y}),
                                     playerId);
                    }
                    if (aType[i]->isEnemy) {
                        network.send(RType::Packet(static_cast<int>(RType::ClientEventType::ENEMY_SPAWN),
                                                   {static_cast<float>(i), aPos[i]->x, aPos[i]->y}),
                                     playerId);
                    }
                }

                eventManager->removeEvent(event);
            }
        }
    }
} // namespace ECS
