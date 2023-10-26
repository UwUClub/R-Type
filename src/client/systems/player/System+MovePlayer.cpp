#include <functional>
#include "ClientHandler.hpp"
#include "ClientPackets.hpp"
#include "EwECS/Event/EventManager.hpp"
#include "EwECS/Event/KeyboardEvent.hpp"
#include "EwECS/SFMLDisplayClass/SFMLDisplayClass.hpp"
#include "EwECS/World.hpp"
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
        Network::ClientHandler &network = Network::ClientHandler::getInstance();
        Event::EventManager *eventManager = Event::EventManager::getInstance();
        auto &keyboardEvent = eventManager->getEventsByType<Event::KeyboardEvent>();
        static const std::unordered_map<Event::KeyIdentifier,
                                        std::function<RType::Client::MovePayload(float &, Utils::Vector2f &)>>
            keyMap = {
                {Event::KeyIdentifier::UP,
                 [&network](float &spd, Utils::Vector2f &xy) {
                     xy.y -= spd;
                     return RType::Client::MovePayload {0, 1};
                 }},
                {Event::KeyIdentifier::DOWN,
                 [&network](float &spd, Utils::Vector2f &xy) {
                     xy.y += spd;
                     return RType::Client::MovePayload {0, -1};
                 }},
                {Event::KeyIdentifier::LEFT,
                 [&network](float &spd, Utils::Vector2f &xy) {
                     xy.x -= spd;
                     return RType::Client::MovePayload {-1, 0};
                 }},
                {Event::KeyIdentifier::RIGHT,
                 [&network](float &spd, Utils::Vector2f &xy) {
                     xy.x += spd;
                     return RType::Client::MovePayload {1, 0};
                 }},
            };
        const auto size = aPos.size();

        for (size_t i = 0; i < size; i++) {
            if (!aType[i].has_value() || !aType[i].value().isPlayer) {
                continue;
            }
            for (auto &event : keyboardEvent) {
                if (keyMap.find(event._keyId) == keyMap.end() || !aIsAlive[i].has_value() || !aPos[i].has_value()
                    || !aSpeed[i].has_value() || !aIsAlive[i].value().isAlive) {
                    continue;
                }

                auto &pos = aPos[i].value();
                auto &speed = aSpeed[i].value().speed;

                auto payload = keyMap.at(event._keyId)(speed, pos);

                network.send(RType::ServerEventType::MOVE, payload);

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
