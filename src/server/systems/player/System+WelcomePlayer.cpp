#include <iostream>
#include "Components.hpp"
#include "Event.hpp"
#include "EventManager.hpp"
#include "Packets.hpp"
#include "PlayerColor.hpp"
#include "ServerGameEvent.hpp"
#include "ServerHandler.hpp"
#include "System.hpp"
#include "Values.hpp"
#include "World.hpp"

namespace ECS {
    void System::welcomePlayer(Core::SparseArray<Utils::Vector2f> &aPos, Core::SparseArray<Component::Speed> &aSpeed,
                               Core::SparseArray<Component::TypeEntity> &aType)
    {
        ECS::Core::World &world = ECS::Core::World::getInstance();
        ECS::Event::EventManager *eventManager = ECS::Event::EventManager::getInstance();
        Network::ServerHandler &server = Network::ServerHandler::getInstance();
        auto events = eventManager->getEventsByType(Event::EventType::GAME);

        for (auto &event : events) {
            auto &gameEvent = static_cast<RType::ServerGameEvent &>(*event);
            if (gameEvent.getType() == RType::ServerEventType::CONNECT) {
                size_t playerId = world.createEntity();
                RType::PLAYER_COLOR playerColor = server.addClientColor(playerId);

                if (playerColor == RType::PLAYER_COLOR::NONE) {
                    world.killEntity(playerId);
                    continue;
                }

                aPos.insertAt(playerId, ECS::Utils::Vector2f {10, 10});
                aSpeed.insertAt(playerId, Component::Speed {PLAYER_SPEED});
                aType.insertAt(playerId, Component::TypeEntity {true, false, false, false, false, false, false});

                server.broadcast(static_cast<int>(RType::ClientEventType::PLAYER_SPAWN),
                                 {static_cast<float>(playerId), 0, static_cast<float>(playerColor), 10, 10});
                server.addClient(playerId, gameEvent.getClientEndpoint());
                server.send(RType::Packet(static_cast<int>(RType::ClientEventType::PLAYER_SPAWN),
                                          {static_cast<float>(playerId), 1, static_cast<float>(playerColor), 10, 10}),
                            playerId);

                int aPosSize = aPos.size();
                for (std::size_t i = 0; i < aPosSize; i++) {
                    if (!aType[i].has_value() || !aPos[i].has_value()) {
                        continue;
                    }
                    if (i != playerId && aType[i]->isPlayer) {
                        float color = static_cast<float>(server.getClientColor(i));
                        server.send(RType::Packet(static_cast<int>(RType::ClientEventType::PLAYER_SPAWN),
                                                  {static_cast<float>(i), 0, color, aPos[i]->x, aPos[i]->y}),
                                    playerId);
                    }
                    if (aType[i]->isEnemy) {
                        server.send(RType::Packet(static_cast<int>(RType::ClientEventType::ENEMY_SPAWN),
                                                  {static_cast<float>(i), aPos[i]->x, aPos[i]->y}),
                                    playerId);
                    }
                }

                eventManager->removeEvent(event);
            }
        }
    }
} // namespace ECS
