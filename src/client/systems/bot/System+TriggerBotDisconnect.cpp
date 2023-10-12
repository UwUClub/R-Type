#include "ClientGameEvent.hpp"
#include "System.hpp"
#include "TypeUtils.hpp"

namespace ECS {
    void System::triggerBotDisconnect(RType::ClientGameEvent *aEvent)
    {
        auto &world = Core::World::getInstance();
        auto &typeComp = world.getComponent<Component::TypeEntity>();

        if (aEvent->getType() == RType::ClientEventType::PLAYER_DISCONNECTION) {
            const auto payload = aEvent->getPayload();
            if (payload.size() != 1) {
                return;
            }
            auto onlineBotId = static_cast<size_t>(payload[0]);
            std::size_t localBotId = RType::TypeUtils::getInstance().getEntityIdByOnlineId(typeComp, onlineBotId);

            world.killEntity(localBotId);
        }
    }
} // namespace ECS
