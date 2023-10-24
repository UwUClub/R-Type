#include <iostream>
#include <vector>
#include "ClientGameEvent.hpp"
#include "ClientPackets.hpp"
#include "EwECS/Event/EventManager.hpp"
#include "EwECS/SparseArray.hpp"
#include "ServerGameEvent.hpp"
#include "ServerHandler.hpp"
#include "ServerPackets.hpp"
#include "System.hpp"
#include "Values.hpp"
#include <unordered_map>

namespace ECS {
    void System::movePlayer(Core::SparseArray<Utils::Vector2f> &aPos, Core::SparseArray<Component::Speed> &aSpeed,
                            Core::SparseArray<Component::Connection> &aConnection)
    {
        ECS::Event::EventManager *eventManager = ECS::Event::EventManager::getInstance();
        Network::ServerHandler &server = Network::ServerHandler::getInstance();
        auto &events = eventManager->getEventsByType<RType::ServerGameEvent>();
        const auto size = events.size();
        std::vector<size_t> toRemove;

        for (size_t i = 0; i < size; i++) {
            auto &gameEvent = events[i];

            if (gameEvent.getType() != RType::ServerEventType::MOVE) {
                continue;
            }

            const auto &payload = gameEvent.getPayload<RType::Client::MovePayload>();

            // Get and check entity ID
            auto entityId = gameEvent.getEntityId();

            if (entityId < 0 || entityId >= aPos.size() || !aPos[entityId].has_value()
                || !aSpeed[entityId].has_value()) {
                toRemove.push_back(i);
                server.sendError(entityId);
                continue;
            }

            // Get and check move values
            if (payload.moveX < -1 || payload.moveX > 1 || payload.moveY < -1 || payload.moveY > 1) {
                toRemove.push_back(i);
                server.sendError(entityId);
                continue;
            }

            // Move player
            if (!aSpeed[entityId].has_value() || !aPos[entityId].has_value()) {
                toRemove.push_back(i);
                server.sendError(entityId);
                continue;
            }

            float speed = aSpeed[entityId].value().speed;
            auto &pos = aPos[entityId].value();

            pos.x += payload.moveX * speed;
            pos.y -= payload.moveY * speed;

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

            RType::Server::PlayerPositionPayload payloadToSend(entityId, pos.x, pos.y);
            server.broadcast(RType::ClientEventType::PLAYER_POSITION, payloadToSend, aConnection);

            toRemove.push_back(i);
        }
        eventManager->removeEvent<RType::ServerGameEvent>(toRemove);
    }
} // namespace ECS
