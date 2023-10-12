#include "Components.hpp"
#include "Event.hpp"
#include "Packets.hpp"
#include "ServerGameEvent.hpp"
#include "ServerHandler.hpp"
#include "SparseArray.hpp"
#include "System.hpp"
#include "World.hpp"

namespace ECS {
    void System::moveSpeedUp(RType::ServerGameEvent *aEvent)
    {
        ECS::Core::World &world = ECS::Core::World::getInstance();
        Network::ServerHandler &network = Network::ServerHandler::getInstance();
        auto &speedComp = world.getComponent<Component::Speed>();
        auto &connectionComp = world.getComponent<Component::Connection>();

        if (aEvent->getType() == RType::ServerEventType::BONUS) {
            auto playerId = static_cast<size_t>(aEvent->getEntityId());
            float const bonusType = aEvent->getPayload()[0];
            if (!speedComp[playerId].has_value()) {
                return;
            }

            if (bonusType == 1) {
                speedComp[playerId].value().speed += 10;
                network.broadcast(static_cast<int>(RType::ClientEventType::PLAYER_BONUS),
                                  {static_cast<float>(playerId), 1}, connectionComp);
            }
        }
    }
} // namespace ECS
