#include <iostream>
#include <vector>
#include "EwECS/Event/EventManager.hpp"
#include "EwECS/SparseArray.hpp"
#include "ServerGameEvent.hpp"
#include "ServerHandler.hpp"
#include "System.hpp"
#include "Values.hpp"
#include <unordered_map>

namespace ECS {
    void System::movePlayer(Core::SparseArray<Utils::Vector2f> &aPos, Core::SparseArray<Component::Speed> &aSpeed,
                            Core::SparseArray<Component::Connection> &aConnection)
    {
        ECS::Event::EventManager *eventManager = ECS::Event::EventManager::getInstance();
        Network::NetworkHandler &network = Network::NetworkHandler::getInstance();
        Network::ServerHandler &server = Network::ServerHandler::getInstance();
        auto &events = eventManager->getEventsByType<RType::ServerGameEvent>();
        const auto size = events.size();
        std::vector<size_t> toRemove;

        for (size_t i = 0; i < size; i++) {
            auto &gameEvent = events[i];

            if (gameEvent.getType() != RType::ServerEventType::MOVE) {
                continue;
            }

            const auto &payloadReceived = gameEvent.getPayload();
            // Check payload size
            if (payloadReceived.size() != 2) {
                toRemove.push_back(i);
                network.send(RType::Packet(ERROR_PACKET_TYPE), gameEvent.getClientEndpoint());
                continue;
            }

            // Get and check entity ID
            auto entityId = gameEvent.getEntityId();

            if (entityId < 0 || entityId >= aPos.size() || !aPos[entityId].has_value()
                || !aSpeed[entityId].has_value()) {
                toRemove.push_back(i);
                network.send(RType::Packet(ERROR_PACKET_TYPE), gameEvent.getClientEndpoint());
                continue;
            }

            // Get and check move values
            float moveX = payloadReceived[0];
            float moveY = payloadReceived[1];

            if (moveX < -1 || moveX > 1 || moveY < -1 || moveY > 1) {
                toRemove.push_back(i);
                network.send(RType::Packet(ERROR_PACKET_TYPE), gameEvent.getClientEndpoint());
                continue;
            }

            // Move player
            if (!aSpeed[entityId].has_value() || !aPos[entityId].has_value()) {
                toRemove.push_back(i);
                network.send(RType::Packet(ERROR_PACKET_TYPE), gameEvent.getClientEndpoint());
                continue;
            }

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

            std::vector<float> payload = {static_cast<float>(entityId), pos.x, pos.y};

            server.broadcast(static_cast<int>(RType::ClientEventType::PLAYER_POSITION), payload, aConnection);
            toRemove.push_back(i);
        }
        eventManager->removeEvent<RType::ServerGameEvent>(toRemove);
    }
} // namespace ECS
