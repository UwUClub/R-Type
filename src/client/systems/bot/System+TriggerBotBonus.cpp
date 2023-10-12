#include "ClientGameEvent.hpp"
#include "System.hpp"
#include "TypeUtils.hpp"

namespace ECS {
    void System::triggerBotBonus(RType::ClientGameEvent *aEvent)
    {
        auto &typeUtils = RType::TypeUtils::getInstance();
        auto &world = ECS::Core::World::getInstance();
        auto &speedComp = world.getComponent<Component::Speed>();
        auto &typeComp = world.getComponent<Component::TypeEntity>();

        if (aEvent->getType() == RType::ClientEventType::PLAYER_BONUS) {
            const auto payload = aEvent->getPayload();
            if (payload.size() != 2) {
                return;
            }
            auto const onlineBotId = static_cast<const size_t>(payload[0]);
            std::size_t const localBotId = typeUtils.getEntityIdByOnlineId(typeComp, onlineBotId);
            float const type = payload[1];

            if (type == 1) {
                if (!speedComp[localBotId].has_value()) {
                    return;
                }
                speedComp[localBotId].value().speed += static_cast<float>(10);
            }
        }
    }
} // namespace ECS