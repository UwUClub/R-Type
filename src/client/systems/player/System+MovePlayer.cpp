#include <functional>
#include "ClientPackets.hpp"
#include "EwECS/Event/EventManager.hpp"
#include "EwECS/Event/KeyboardEvent.hpp"
#include "EwECS/Network/ClientHandler.hpp"
#include "EwECS/SFMLDisplayClass/SFMLDisplayClass.hpp"
#include "EwECS/World.hpp"
#include "PlayerMoveState.hpp"
#include "ServerGameEvent.hpp"
#include "System.hpp"
#include "Values.hpp"
#include "components/IsAlive.hpp"
#include <unordered_map>

namespace ECS {
    void System::movePlayer(Core::SparseArray<Utils::Vector2f> &aPos, Core::SparseArray<Component::Speed> &aSpeed,
                            Core::SparseArray<Component::TypeEntity> &aType,
                            Core::SparseArray<Component::IsAlive> &aIsAlive)
    {
        Core::World &world = Core::World::getInstance();
        ECS::Network::ClientHandler &client = ECS::Network::ClientHandler::getInstance();
        Event::EventManager *eventManager = Event::EventManager::getInstance();
        PlayerMoveState &playerMoveState = PlayerMoveState::getInstance();
        auto &keyboardEvent = eventManager->getEventsByType<Event::KeyboardEvent>();
        static const std::unordered_map<
            Event::KeyIdentifier, std::function<RType::Client::MovePayload(PlayerMoveState &, Event::KeyState, float)>>
            keyMap = {
                {Event::KeyIdentifier::UP,
                 [](PlayerMoveState &moveState, Event::KeyState state, float speed) {
                     moveState.runningY = (state == Event::KeyState::PRESSED) ? true : false;
                     moveState.speedY = -speed;
                     return RType::Client::MovePayload {0, 1};
                 }},
                {Event::KeyIdentifier::DOWN,
                 [](PlayerMoveState &moveState, Event::KeyState state, float speed) {
                     moveState.runningY = (state == Event::KeyState::PRESSED) ? true : false;
                     moveState.speedY = speed;
                     return RType::Client::MovePayload {0, -1};
                 }},
                {Event::KeyIdentifier::LEFT,
                 [](PlayerMoveState &moveState, Event::KeyState state, float speed) {
                     moveState.runningX = (state == Event::KeyState::PRESSED) ? true : false;
                     moveState.speedX = -speed;
                     return RType::Client::MovePayload {-1, 0};
                 }},
                {Event::KeyIdentifier::RIGHT,
                 [](PlayerMoveState &moveState, Event::KeyState state, float speed) {
                     moveState.runningX = (state == Event::KeyState::PRESSED) ? true : false;
                     moveState.speedX = speed;
                     return RType::Client::MovePayload {1, 0};
                 }},
            };
        const auto size = aPos.size();

        for (size_t i = 0; i < size; i++) {
            if (!aType[i].has_value() || !aType[i].value().isPlayer) {
                continue;
            }
            auto &pos = aPos[i].value();
            auto &speed = aSpeed[i].value().speed;
            RType::Client::MovePayload payload {0, 0};

            for (auto &event : keyboardEvent) {
                if (keyMap.find(event._keyId) == keyMap.end() || !aIsAlive[i].has_value() || !aPos[i].has_value()
                    || !aSpeed[i].has_value() || !aIsAlive[i].value().isAlive) {
                    continue;
                }

                payload = keyMap.at(event._keyId)(playerMoveState, event._state, speed);
            }
            if (playerMoveState.runningX) {
                pos.x += speed;
                if (playerMoveState.speedX < 0) {
                    payload.moveX = -1;
                } else {
                    payload.moveX = 1;
                }
            }
            if (playerMoveState.runningY) {
                pos.y += speed;

                if (playerMoveState.speedY < 0) {
                    payload.moveY = 1;
                } else {
                    payload.moveY = -1;
                }
            }

            client.send(RType::ServerEventType::MOVE, payload);

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
        }
    }
} // namespace ECS
