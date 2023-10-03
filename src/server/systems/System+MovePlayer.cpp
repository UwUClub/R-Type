#include <iostream>
#include "EventManager.hpp"
#include "ServerGameEvent.hpp"
#include "ServerNetworkHandler.hpp"
#include "System.hpp"
#include <unordered_map>

constexpr int SCREEN_WIDTH = 1920;
constexpr int SCREEN_HEIGHT = 1080;

namespace ECS {
    void System::movePlayer(Core::SparseArray<Utils::Vector2f> &aPos, Core::SparseArray<Component::Speed> &aSpeed,
                            Core::SparseArray<Component::TypeEntity> &aType)
    {
        ECS::Event::EventManager *eventManager = ECS::Event::EventManager::getInstance();
        Network::ServerNetworkHandler &network = Network::ServerNetworkHandler::getInstance();

        static const std::unordered_map<RTypeProtocol::ServerEventType, std::function<void(float &, Utils::Vector2f &)>>
            moveMap = {
                {RTypeProtocol::ServerEventType::MOVE_UP,
                 [](float &spd, Utils::Vector2f &xy) {
                     xy.y = xy.y <= 0 ? 0 : xy.y -= spd;
                 }},
                {
                    RTypeProtocol::ServerEventType::MOVE_DOWN,
                    [](float &spd, Utils::Vector2f &xy) {
                        xy.y = xy.y >= SCREEN_HEIGHT ? SCREEN_HEIGHT : xy.y += spd;
                    },
                },
                {
                    RTypeProtocol::ServerEventType::MOVE_LEFT,
                    [](float &spd, Utils::Vector2f &xy) {
                        xy.x = xy.x <= 0 ? 0 : xy.x -= spd;
                    },
                },
                {
                    RTypeProtocol::ServerEventType::MOVE_RIGHT,
                    [](float &spd, Utils::Vector2f &xy) {
                        xy.x = xy.x >= SCREEN_WIDTH ? SCREEN_WIDTH : xy.x += spd;
                    },
                },
            };

        for (auto &event : eventManager->getEventsByType(Event::EventType::GAME)) {
            auto &gameEvent = static_cast<RTypeProtocol::ServerGameEvent &>(*event);

            if (moveMap.find(gameEvent.getType()) != moveMap.end()) {
                std::size_t entityId = gameEvent.getEntityId();
                moveMap.at(gameEvent.getType())(aSpeed[entityId].value().speed, aPos[entityId].value());

                // std::cout << entityId << " pos: " << aPos[gameEvent.getEntityId()].value().x << " "
                //           << aPos[gameEvent.getEntityId()].value().y << std::endl;

                network.broadcast({RTypeProtocol::ClientEventType::PLAYER_POSITION,
                                   entityId,
                                   {aPos[entityId].value().x, aPos[entityId].value().y}});
            }
        }
    }
} // namespace ECS
