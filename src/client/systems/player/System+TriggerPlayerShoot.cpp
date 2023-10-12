#include <functional>
#include "ClientHandler.hpp"
#include "KeyboardEvent.hpp"
#include "SDLDisplayClass.hpp"
#include "System.hpp"
#include "Values.hpp"
#include <unordered_map>

namespace ECS {
    void System::triggerPlayerShoot(Event::KeyboardEvent *aEvent)
    {
        Network::ClientHandler &client = Network::ClientHandler::getInstance();
        auto &world = ECS::Core::World::getInstance();
        auto &posComp = world.getComponent<Utils::Vector2f>();
        auto &typeComp = world.getComponent<Component::TypeEntity>();
        auto &isAliveComp = world.getComponent<Component::IsAlive>();
        const auto size = posComp.size();

        for (size_t i = 0; i < size; i++) {
            if (!typeComp[i].has_value() || !isAliveComp[i].has_value() || !posComp[i].has_value()
                || !typeComp[i].value().isPlayer || !isAliveComp[i].value().isAlive) {
                continue;
            }

            if (aEvent->_keyId == Event::KeyIdentifier::SPACE) {
                int playerOnlineId = static_cast<int>(typeComp[i].value().onlineId.value_or(-1));
                if (playerOnlineId == -1) {
                    continue;
                }
                RType::Packet packet(static_cast<int>(RType::ServerEventType::SHOOT),
                                     {static_cast<float>(playerOnlineId)});
                client.send(packet);
            }
        }
    }
} // namespace ECS
