#include <functional>
#include "ClientHandler.hpp"
#include "EwECS/Event/EventManager.hpp"
#include "EwECS/Event/KeyboardEvent.hpp"
#include "EwECS/World.hpp"
#include "EwECS/SFMLDisplayClass/SFMLDisplayClass.hpp"
#include "System.hpp"
#include "Values.hpp"
#include "components/IsAlive.hpp"
#include <unordered_map>

namespace ECS {
    void System::movePlayer(Core::SparseArray<Utils::Vector2f> &aPos, Core::SparseArray<Component::Speed> &aSpeed,
                            Core::SparseArray<Component::TypeEntity> &aType,
                            Core::SparseArray<Component::IsAlive> &aIsAlive)
    {
        Network::ClientHandler &network = Network::ClientHandler::getInstance();
        Event::EventManager *eventManager = Event::EventManager::getInstance();
        auto &keyboardEvent = eventManager->getEventsByType<Event::KeyboardEvent>();
        static const std::unordered_map<Event::KeyIdentifier, std::function<void(float &, Utils::Vector2f &)>> keyMap =
            {
                {Event::KeyIdentifier::UP,
                 [&network](float &spd, Utils::Vector2f &xy) {
                     xy.y -= spd;
                     RType::Packet packet(RType::ServerEventType::MOVE, {0, 1});
                     network.send(packet);
                 }},
                {Event::KeyIdentifier::DOWN,
                 [&network](float &spd, Utils::Vector2f &xy) {
                     xy.y += spd;
                     RType::Packet packet(RType::ServerEventType::MOVE, {0, -1});
                     network.send(packet);
                 }},
                {Event::KeyIdentifier::LEFT,
                 [&network](float &spd, Utils::Vector2f &xy) {
                     xy.x -= spd;
                     RType::Packet packet(RType::ServerEventType::MOVE, {-1, 0});
                     network.send(packet);
                 }},
                {Event::KeyIdentifier::RIGHT,
                 [&network](float &spd, Utils::Vector2f &xy) {
                     xy.x += spd;
                     RType::Packet packet(RType::ServerEventType::MOVE, {1, 0});
                     network.send(packet);
                 }},
            };
        const auto size = aPos.size();

        for (size_t i = 0; i < size; i++) {
            if (!aType[i].has_value() || !aType[i].value().isPlayer) {
                continue;
            }
            for (auto &event : keyboardEvent) {
                if (keyMap.find(event._keyId) == keyMap.end() || !aIsAlive[i].value().isAlive) {
                    continue;
                }

                auto &pos = aPos[i].value();
                auto &speed = aSpeed[i].value().speed;

                keyMap.at(event._keyId)(speed, pos);

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
