#include <functional>
#include "ClientHandler.hpp"
#include "EventManager.hpp"
#include "KeyboardEvent.hpp"
#include "RayDisplayClass.hpp"
#include "System.hpp"
#include "Values.hpp"
#include "World.hpp"
#include "components/IsAlive.hpp"
#include <unordered_map>

namespace ECS {
    void System::movePlayer(Core::SparseArray<Utils::Vector2f> &aPos, Core::SparseArray<Component::Speed> &aSpeed,
                            Core::SparseArray<Component::TypeEntity> &aType,
                            Core::SparseArray<Component::IsAlive> &aIsAlive)
    {
        Network::ClientHandler &network = Network::ClientHandler::getInstance();

        Event::EventManager *eventManager = Event::EventManager::getInstance();
        auto keyboardEvent = eventManager->getEventsByType(Event::EventType::KEYBOARD);
        static const std::unordered_map<Event::KeyIdentifier, std::function<void(float &, Utils::Vector2f &, float)>>
            keyMap = {
                {Event::KeyIdentifier::UP,
                 [&network](float &spd, Utils::Vector2f &xy, float onlineId) {
                     xy.y -= spd;
                     RType::Packet packet(static_cast<int>(RType::ServerEventType::MOVE), {onlineId, 0, 1});
                     network.send(packet);
                 }},
                {Event::KeyIdentifier::DOWN,
                 [&network](float &spd, Utils::Vector2f &xy, float onlineId) {
                     xy.y += spd;
                     RType::Packet packet(static_cast<int>(RType::ServerEventType::MOVE), {onlineId, 0, -1});
                     network.send(packet);
                 }},
                {Event::KeyIdentifier::LEFT,
                 [&network](float &spd, Utils::Vector2f &xy, float onlineId) {
                     xy.x -= spd;
                     RType::Packet packet(static_cast<int>(RType::ServerEventType::MOVE), {onlineId, -1, 0});
                     network.send(packet);
                 }},
                {Event::KeyIdentifier::RIGHT,
                 [&network](float &spd, Utils::Vector2f &xy, float onlineId) {
                     xy.x += spd;
                     RType::Packet packet(static_cast<int>(RType::ServerEventType::MOVE), {onlineId, 1, 0});
                     network.send(packet);
                 }},
            };

        for (size_t i = 0; i < aPos.size(); i++) {
            if (!aType[i].has_value() || !aType[i].value().isPlayer) {
                continue;
            }
            for (auto &event : keyboardEvent) {
                auto *keyEvent = static_cast<Event::KeyboardEvent *>(event.get());
                if (keyMap.find(keyEvent->_keyId) == keyMap.end() || !aIsAlive[i].value().isAlive) {
                    continue;
                }
                auto &pos = aPos[i].value();
                float onlinePlayerId = static_cast<float>(aType[i].value().onlineId.value_or(-1));
                if (onlinePlayerId == -1) {
                    continue;
                }
                keyMap.at(keyEvent->_keyId)(aSpeed[i].value().speed, pos, onlinePlayerId);

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
    }
} // namespace ECS
