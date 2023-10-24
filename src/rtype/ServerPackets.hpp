#include "Packet.hpp"

#ifndef SERVERPACKETS_HPP
    #define SERVERPACKETS_HPP

namespace RType::Server {

    struct PlayerJoinedPayload : Network::IPayload
    {
            unsigned short playerId;
            bool isReceiver;
            uint8_t playerColor;
            float posX;
            float posY;

            explicit PlayerJoinedPayload(unsigned short aPlayerId, bool aIsReceiver, uint8_t aPlayerColor, float aPosX,
                                         float aPosY)
                : playerId(aPlayerId),
                  isReceiver(aIsReceiver),
                  playerColor(aPlayerColor),
                  posX(aPosX),
                  posY(aPosY)
            {}
    };

    struct PlayerLeftPayload : Network::IPayload
    {
            unsigned short playerId;

            explicit PlayerLeftPayload(unsigned short aPlayerId)
                : playerId(aPlayerId)
            {}
    };

    struct PlayerPositionPayload : Network::IPayload
    {
            unsigned short playerId;
            float posX;
            float posY;

            explicit PlayerPositionPayload(unsigned short aPlayerId, float aPosX, float aPosY)
                : playerId(aPlayerId),
                  posX(aPosX),
                  posY(aPosY)
            {}
    };

    struct PlayerGotBonusPayload : Network::IPayload
    {
            unsigned short playerId;
            uint8_t bonusId;

            explicit PlayerGotBonusPayload(unsigned short aPlayerId, uint8_t aBonusId)
                : playerId(aPlayerId),
                  bonusId(aBonusId)
            {}
    };

    struct PlayerShotPayload : Network::IPayload
    {
            unsigned short bulletId;
            float posX;
            float posY;

            explicit PlayerShotPayload(unsigned short aBulletId, float aPosX, float aPosY)
                : bulletId(aBulletId),
                  posX(aPosX),
                  posY(aPosY)
            {}
    };

    struct PlayerDiedPayload : Network::IPayload
    {
            unsigned short playerId;

            explicit PlayerDiedPayload(unsigned short aPlayerId)
                : playerId(aPlayerId)
            {}
    };

    struct EnemySpawnedPayload : Network::IPayload
    {
            unsigned short enemyId;
            float posX;
            float posY;

            explicit EnemySpawnedPayload(unsigned short aEnemyId, float aPosX, float aPosY)
                : enemyId(aEnemyId),
                  posX(aPosX),
                  posY(aPosY)
            {}
    };

    struct EnemyPositionPayload : Network::IPayload
    {
            uint8_t enemyId;
            float posX;
            float posY;

            explicit EnemyPositionPayload(uint8_t aEnemyId, float aPosX, float aPosY)
                : enemyId(aEnemyId),
                  posX(aPosX),
                  posY(aPosY)
            {}
    };

    struct EnemyShotPayload : Network::IPayload
    {
            unsigned short bulletId;
            float posX;
            float posY;

            explicit EnemyShotPayload(unsigned short aBulletId, float aPosX, float aPosY)
                : bulletId(aBulletId),
                  posX(aPosX),
                  posY(aPosY)
            {}
    };

    struct EnemyDiedPayload : Network::IPayload
    {
            unsigned short enemyId;

            explicit EnemyDiedPayload(unsigned short aEnemyId)
                : enemyId(aEnemyId)
            {}
    };

    struct ServerFullPayload : Network::IPayload
    {};

} // namespace RType::Server

#endif
