#include "ClientGameEvent.hpp"
#include "SDLDisplayClass.hpp"
#include "System.hpp"
#include "Values.hpp"

namespace ECS {
    void System::createBot(RType::ClientGameEvent *aEvent)
    {
        SDLDisplayClass &display = SDLDisplayClass::getInstance();

        if (aEvent->getType() == RType::ClientEventType::PLAYER_SPAWN) {
            std::cout << "Player spawn" << std::endl;
            const auto payload = aEvent->getPayload();
            if (payload.size() != 5) {
                return;
            }
            auto onlineEntityId = static_cast<std::size_t>(payload[0]);
            std::cout << "Online entity id: " << onlineEntityId << std::endl;
            bool isLocalPlayer = payload[1] == 1;

            Component::TypeEntity entityType {false, true, false, false, false, false, false, onlineEntityId};
            if (isLocalPlayer) {
                std::cout << "Local player" << std::endl;
                entityType.isPlayer = true;
                entityType.isBot = false;
            }

            int color = static_cast<int>(payload[2]);
            float posX = payload[3];
            float posY = payload[4];

            display.addEntity(ECS::Utils::Vector2f {posX, posY}, Component::Speed {PLAYER_SPEED}, entityType,
                              Component::LoadedSprite {
                                  PLAYER_ASSET, nullptr,
                                  new SDL_Rect {0, color * PLAYER_TEX_HEIGHT, PLAYER_TEX_WIDTH, PLAYER_TEX_HEIGHT},
                                  new SDL_Rect {0, 0, PLAYER_TEX_WIDTH, PLAYER_TEX_HEIGHT}},
                              Component::HitBox {PLAYER_TEX_WIDTH, PLAYER_TEX_HEIGHT}, Component::IsAlive {true, 0});
        }
    }

} // namespace ECS