#include <vector>
#include "ClientGameEvent.hpp"
#include "EwECS/Event/EventManager.hpp"
#include "EwECS/SFMLDisplayClass/SFMLDisplayClass.hpp"
#include "ServerPackets.hpp"
#include "System.hpp"
#include "TypeUtils.hpp"

namespace ECS {
    void System::updateBotPosition(Core::SparseArray<Utils::Vector2f> &aPos,
                                   Core::SparseArray<Component::TypeEntity> &aType)
    {
        Event::EventManager *eventManager = Event::EventManager::getInstance();
        auto &events = eventManager->getEventsByType<RType::ClientGameEvent>();
        std::vector<size_t> toRemove;
        const auto size = events.size();

        for (size_t i = 0; i < size; i++) {
            auto &gameEvent = events[i];

            if (gameEvent.getType() != RType::ClientEventType::PLAYER_POSITION) {
                continue;
            }

            const auto &payload = gameEvent.getPayload<RType::Server::PlayerPositionPayload>();

            const auto localBotId = RType::TypeUtils::getInstance().getEntityIdByOnlineId(aType, payload.playerId);

            if (!aPos[localBotId].has_value()) {
                toRemove.push_back(i);
                continue;
            }

            auto &posLocal = aPos[localBotId].value();

            posLocal.x = payload.posX;
            posLocal.y = payload.posY;
            toRemove.push_back(i);
        }
        eventManager->removeEvent<RType::ClientGameEvent>(toRemove);
    }

} // namespace ECS