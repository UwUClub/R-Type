#include "EwECS/Network/Packet.hpp"

#ifndef SERVERPACKETS_HPP
    #define SERVERPACKETS_HPP

namespace RType::Server {

    PACK(struct PlayerJoinedPayload
         : ECS::Network::IPayload {
             unsigned short playerId;
             bool isReceiver;
             uint8_t playerColor;
             float posX;
             float posY;

             PlayerJoinedPayload() = default;

             PlayerJoinedPayload(unsigned short aPlayerId, bool aIsReceiver, uint8_t aPlayerColor, float aPosX,
                                 float aPosY)
             {
                 playerId = aPlayerId;
                 isReceiver = aIsReceiver;
                 playerColor = aPlayerColor;
                 posX = aPosX;
                 posY = aPosY;
             }
         });

    PACK(struct PlayerLeftPayload
         : ECS::Network::IPayload {
             unsigned short playerId;

             PlayerLeftPayload() = default;

             PlayerLeftPayload(unsigned short aPlayerId)
             {
                 playerId = aPlayerId;
             }
         });

    PACK(struct PlayerPositionPayload
         : ECS::Network::IPayload {
             unsigned short playerId;
             float posX;
             float posY;

             PlayerPositionPayload() = default;

             PlayerPositionPayload(unsigned short aPlayerId, float aPosX, float aPosY)
             {
                 playerId = aPlayerId;
                 posX = aPosX;
                 posY = aPosY;
             }
         });

    PACK(struct PlayerGotBonusPayload
         : ECS::Network::IPayload {
             unsigned short playerId;
             unsigned short bonusId;

             PlayerGotBonusPayload() = default;

             PlayerGotBonusPayload(unsigned short aPlayerId, unsigned short aBonusId)
             {
                 playerId = aPlayerId;
                 bonusId = aBonusId;
             }
         });

    PACK(struct PlayerShotPayload
         : ECS::Network::IPayload {
             unsigned short bulletId;
             float posX;
             float posY;

             PlayerShotPayload() = default;

             PlayerShotPayload(unsigned short aBulletId, float aPosX, float aPosY)
             {
                 bulletId = aBulletId;
                 posX = aPosX;
                 posY = aPosY;
             }
         });

    PACK(struct PlayerDiedPayload
         : ECS::Network::IPayload {
             unsigned short playerId;

             PlayerDiedPayload() = default;

             PlayerDiedPayload(unsigned short aPlayerId)
             {
                 playerId = aPlayerId;
             }
         });

    PACK(struct EnemySpawnedPayload
         : ECS::Network::IPayload {
             unsigned short enemyId;
             float posX;
             float posY;

             EnemySpawnedPayload() = default;

             EnemySpawnedPayload(unsigned short aEnemyId, float aPosX, float aPosY)
             {
                 enemyId = aEnemyId;
                 posX = aPosX;
                 posY = aPosY;
             }
         });

    PACK(struct EnemyPositionPayload
         : ECS::Network::IPayload {
             uint8_t enemyId;
             float posX;
             float posY;

             EnemyPositionPayload() = default;

             EnemyPositionPayload(uint8_t aEnemyId, float aPosX, float aPosY)
             {
                 enemyId = aEnemyId;
                 posX = aPosX;
                 posY = aPosY;
             }
         });

    PACK(struct EnemyShotPayload
         : ECS::Network::IPayload {
             unsigned short bulletId;
             float posX;
             float posY;

             EnemyShotPayload() = default;

             EnemyShotPayload(unsigned short aBulletId, float aPosX, float aPosY)
             {
                 bulletId = aBulletId;
                 posX = aPosX;
                 posY = aPosY;
             }
         });

    PACK(struct EnemyDiedPayload
         : ECS::Network::IPayload {
             unsigned short enemyId;
             unsigned short bonusId;

             EnemyDiedPayload() = default;

             EnemyDiedPayload(unsigned short aEnemyId, unsigned short aBonusId)
             {
                 enemyId = aEnemyId;
                 bonusId = aBonusId;
             }
         });
} // namespace RType::Server

#endif
