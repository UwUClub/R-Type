#include <iostream>
#include <string>
#include <vector>
#include "ClientHandler.hpp"
#include "EwECS/SFMLDisplayClass/SFMLDisplayClass.hpp"
#include "Packets.hpp"
#include "System.hpp"

namespace ECS {
    void System::triggerBonus(Core::SparseArray<Utils::Vector2f> &aPos, Core::SparseArray<Component::TypeEntity> &aType,
                              Core::SparseArray<Component::IsAlive> &aIsAlive,
                              Core::SparseArray<Component::HitBox> &aHitBox)
    {
        auto &world = Core::World::getInstance();
        auto &display = SFMLDisplayClass::getInstance();
        auto &client = Network::ClientHandler::getInstance();
        const auto size = aType.size();

        for (size_t bonus = 0; bonus < size; bonus++) {
            if (!aType[bonus].has_value() || !aType[bonus].value().isBonus || !aPos[bonus].has_value()
                || !aIsAlive[bonus].has_value() || !aHitBox[bonus].has_value()) {
                continue;
            }

            auto &posBonus = aPos[bonus].value();
            auto &isAliveBonus = aIsAlive[bonus].value();
            auto &hitBoxBonus = aHitBox[bonus].value();
            const auto posSize = aPos.size();

            if (!isAliveBonus.isAlive) {
                continue;
            }

            for (size_t player = 0; player < posSize; player++) {
                if (!aType[player].has_value() || !aType[player].value().isPlayer) {
                    continue;
                }

                auto &posPlayer = aPos[player].value();
                auto &hitBoxPlayer = aHitBox[player].value();

                if ((posBonus.x > posPlayer.x && posBonus.x < posPlayer.x + hitBoxPlayer.width
                     && posBonus.y > posPlayer.y && posBonus.y < posPlayer.y + hitBoxPlayer.height)) {
                    isAliveBonus.isAlive = false;
                    RType::Packet packet(static_cast<int>(RType::ServerEventType::BONUS), {1});
                    client.send(packet);
                    world.killEntity(bonus);
                    break;
                }
            }
        }
    }
} // namespace ECS
