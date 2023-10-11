#include <functional>
#include "ClientHandler.hpp"
#include "EventManager.hpp"
#include "KeyboardEvent.hpp"
#include "SDLDisplayClass.hpp"
#include "System.hpp"
#include "Values.hpp"
#include "World.hpp"
#include "components/IsAlive.hpp"
#include <unordered_map>

namespace ECS {
    void System::movePlayer(Event::KeyboardEvent *aEvent)
    {
        Network::ClientHandler &network = Network::ClientHandler::getInstance();
        auto &world = ECS::Core::World::getInstance();
        auto &posComp = world.getComponent<Utils::Vector2f>();
        auto &speedComp = world.getComponent<Component::Speed>();
        auto &typeComp = world.getComponent<Component::TypeEntity>();
        auto &isAliveComp = world.getComponent<Component::IsAlive>();
        const auto size = posComp.size();

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

        for (size_t i = 0; i < size; i++) {
            if (!typeComp[i].has_value() || !speedComp[i].has_value() || !isAliveComp[i].has_value()
                || posComp[i].has_value() || !typeComp[i].value().isPlayer) {
                continue;
            }
            if (keyMap.find(aEvent->_keyId) == keyMap.end() || !isAliveComp[i].value().isAlive) {
                continue;
            }
            auto &pos = posComp[i].value();
            float onlinePlayerId = static_cast<float>(typeComp[i].value().onlineId.value_or(-1));
            if (onlinePlayerId == -1) {
                continue;
            }
            keyMap.at(aEvent->_keyId)(speedComp[i].value().speed, pos, onlinePlayerId);

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
