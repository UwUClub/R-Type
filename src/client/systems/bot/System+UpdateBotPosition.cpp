#include <vector>
#include "ClientGameEvent.hpp"
#include "EwECS/Event/EventManager.hpp"
#include "EwECS/SFMLDisplayClass/SFMLDisplayClass.hpp"
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

            const auto &payload = gameEvent.getPayload();

            if (payload.size() != 3) {
                toRemove.push_back(i);
                continue;
            }

            std::size_t onlineBotId = static_cast<int>(payload[0]);
            float posX = payload[1];
            float posY = payload[2];
            size_t localBotId = RType::TypeUtils::getInstance().getEntityIdByOnlineId(aType, onlineBotId);

            if (!aPos[localBotId].has_value()) {
                toRemove.push_back(i);
                continue;
            }

            auto &posLocal = aPos[localBotId].value();

            posLocal.x = posX;
            posLocal.y = posY;
            toRemove.push_back(i);
        }
        eventManager->removeEvent<RType::ClientGameEvent>(toRemove);
    }

} // namespace ECS