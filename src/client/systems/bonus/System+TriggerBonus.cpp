#include <iostream>
#include <string>
#include <vector>
#include "ClientHandler.hpp"
#include "Packets.hpp"
#include "SDLDisplayClass.hpp"
#include "System.hpp"

namespace ECS {
    void System::triggerBonus(Core::SparseArray<Utils::Vector2f> &aPos, Core::SparseArray<Component::TypeEntity> &aType,
                              Core::SparseArray<Component::IsAlive> &aIsAlive,
                              Core::SparseArray<Component::HitBox> &aHitBox)
    {
        auto &world = Core::World::getInstance();
        auto &display = SDLDisplayClass::getInstance();
        auto &client = Network::ClientHandler::getInstance();

        for (size_t bonus = 0; bonus < aType.size(); bonus++) {
            if (!aType[bonus].has_value() || !aType[bonus].value().isBonus) {
                continue;
            }
            for (size_t player = 0; player < aPos.size(); player++) {
                if (!aType[player].has_value() || !aType[player].value().isPlayer) {
                    continue;
                }
                if ((aPos[bonus].value().x > aPos[player].value().x
                     && aPos[bonus].value().x < aPos[player].value().x + aHitBox[player].value().width
                     && aPos[bonus].value().y > aPos[player].value().y
                     && aPos[bonus].value().y < aPos[player].value().y + aHitBox[player].value().height)
                    || (aPos[bonus].value().x + aHitBox[bonus].value().width > aPos[player].value().x
                        && aPos[bonus].value().x + aHitBox[bonus].value().width
                               < aPos[player].value().x + aHitBox[player].value().width
                        && aPos[bonus].value().y > aPos[player].value().y
                        && aPos[bonus].value().y < aPos[player].value().y + aHitBox[player].value().height)) {
                    aIsAlive[bonus].value().isAlive = false;
                    display.freeRects(bonus);
                    RType::Packet packet(static_cast<int>(RType::ServerEventType::BONUS), {1});
                    client.send(packet);
                    world.killEntity(bonus);
                    break;
                }
            }
        }
    }
} // namespace ECS
