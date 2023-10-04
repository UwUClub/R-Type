#include <functional>
#include "ClientHandler.hpp"
#include "EventManager.hpp"
#include "KeyboardEvent.hpp"
#include "SDLDisplayClass.hpp"
#include "System.hpp"
#include "Values.hpp"
#include "World.hpp"
#include <unordered_map>

namespace ECS {
    void System::movePlayer(Core::SparseArray<Utils::Vector2f> &aPos, Core::SparseArray<Component::Speed> &aSpeed,
                            Core::SparseArray<Component::TypeEntity> &aType)
    {
        Network::ClientHandler &network = Network::ClientHandler::getInstance();

        Event::EventManager *eventManager = Event::EventManager::getInstance();
        auto keyboardEvent = eventManager->getEventsByType(Event::EventType::KEYBOARD);
        static const std::unordered_map<Event::KeyIdentifier,
                                        std::function<void(float &, Utils::Vector2f &, float, Core::World &)>>
            keyMap = {
                {Event::KeyIdentifier::UP,
                 [&network](float &spd, Utils::Vector2f &xy, float onlineId, Core::World &world) {
                     xy.y = xy.y <= 0 ? 0 : xy.y -= spd * world.getDeltaTime();
                     RType::Packet packet(static_cast<int>(RType::ServerEventType::MOVE), {onlineId, 0, 1});
                     network.send(packet);
                 }},
                {Event::KeyIdentifier::DOWN,
                 [&network](float &spd, Utils::Vector2f &xy, float onlineId, Core::World &world) {
                     xy.y = xy.y >= SCREEN_HEIGHT ? SCREEN_HEIGHT : xy.y += spd * world.getDeltaTime();
                     RType::Packet packet(static_cast<int>(RType::ServerEventType::MOVE), {onlineId, 0, -1});
                     network.send(packet);
                 }},
                {Event::KeyIdentifier::LEFT,
                 [&network](float &spd, Utils::Vector2f &xy, float onlineId, Core::World &world) {
                     xy.x = xy.x <= 0 ? 0 : xy.x -= spd * world.getDeltaTime();
                     RType::Packet packet(static_cast<int>(RType::ServerEventType::MOVE), {onlineId, -1, 0});
                     network.send(packet);
                 }},
                {Event::KeyIdentifier::RIGHT,
                 [&network](float &spd, Utils::Vector2f &xy, float onlineId, Core::World &world) {
                     xy.x = xy.x >= SCREEN_WIDTH ? SCREEN_WIDTH : xy.x += spd * world.getDeltaTime();
                     RType::Packet packet(static_cast<int>(RType::ServerEventType::MOVE), {onlineId, 1, 0});
                     network.send(packet);
                 }},
            };

        for (size_t i = 0; i < aPos.size(); i++) {
            if (!aType[i].has_value() || !aType[i].value().isPlayer) {
                continue;
            }
            for (auto &event : keyboardEvent) {
                auto *keyEvent = static_cast<Event::KeyboardEvent *>(event);
                if (keyMap.find(keyEvent->_keyId) == keyMap.end()) {
                    continue;
                }
                float onlinePlayerId = static_cast<float>(aType[i].value().onlineId.value_or(0));
                keyMap.at(keyEvent->_keyId)(aSpeed[i].value().speed, aPos[i].value(), onlinePlayerId,
                                            Core::World::getInstance());
            }
        }
    }
} // namespace ECS
