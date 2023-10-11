#include "ClientGameEvent.hpp"
#include "EventManager.hpp"
#include "SDLDisplayClass.hpp"
#include "System.hpp"
#include "TypeUtils.hpp"

namespace ECS {
    void System::updateBotPosition(RType::ClientGameEvent *aEvent)
    {
        auto &world = ECS::Core::World::getInstance();
        auto &posComp = world.getComponent<Utils::Vector2f>();
        auto &typeComp = world.getComponent<Component::TypeEntity>();

        auto &gameEvent = static_cast<RType::ClientGameEvent &>(*aEvent);

        if (gameEvent.getType() == RType::ClientEventType::PLAYER_POSITION) {
            const auto payload = gameEvent.getPayload();
            auto onlineBotId = static_cast<std::size_t>(payload[0]);
            size_t localBotId = RType::TypeUtils::getInstance().getEntityIdByOnlineId(typeComp, onlineBotId);
            float posX = payload[1];
            float posY = payload[2];

            if (!posComp[localBotId].has_value()) {
                return;
            }
            posComp[localBotId].value().x = posX;
            posComp[localBotId].value().y = posY;
        }
    }

} // namespace ECS
