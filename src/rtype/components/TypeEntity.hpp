/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** TypeEntity
*/

#include <cstddef>
#include <optional>

#ifndef TYPEENTITY_HPP
    #define TYPEENTITY_HPP
namespace Component {
    struct TypeEntity
    {
            /**
             * @brief Construct a new Type Entity object
             *
             */
            TypeEntity()
                : isPlayer(false),
                  isBot(false),
                  isEnemy(false),
                  isBullet(false),
                  isWall(false),
                  isBonus(false),
                  isBackground(false)
            {}
            /**
             * @brief Construct a new Type Entity object
             *
             * @param aIsPlayer a boolean to know if the entity is a player
             * @param aIsBot a boolean to know if the entity is a bot
             * @param aIsEnemy a boolean to know if the entity is an enemy
             * @param aIsBullet a boolean to know if the entity is a bullet
             * @param aIsWall a boolean to know if the entity is a wall
             * @param aIsBonus a boolean to know if the entity is a bonus
             * @param aIsBackground a boolean to know if the entity is a background
             */
            TypeEntity(bool aIsPlayer, bool aIsBot, bool aIsEnemy, bool aIsBullet, bool aIsWall, bool aIsBonus,
                       bool aIsBackground, bool aIsEnemyMissile = false)
                : isPlayer(aIsPlayer),
                  isBot(aIsBot),
                  isEnemy(aIsEnemy),
                  isBullet(aIsBullet),
                  isWall(aIsWall),
                  isBonus(aIsBonus),
                  isBackground(aIsBackground),
                  isEnemyMissile(aIsEnemyMissile)
            {}
            /**
             * @brief Construct a new Type Entity object
             *
             * @param aIsPlayer a boolean to know if the entity is a player
             * @param aIsBot a boolean to know if the entity is a bot
             * @param aIsEnemy a boolean to know if the entity is an enemy
             * @param aIsBullet a boolean to know if the entity is a bullet
             * @param aIsWall a boolean to know if the entity is a wall
             * @param aIsBonus a boolean to know if the entity is a bonus
             * @param aIsBackground a boolean to know if the entity is a background
             * @param aOnlineId an optional size_t to know the online id of the entity
             */
            TypeEntity(bool aIsPlayer, bool aIsBot, bool aIsEnemy, bool aIsBullet, bool aIsWall, bool aIsBonus,
                       bool aIsBackground, size_t aOnlineId, bool aIsEnemyMissile = false)
                : isPlayer(aIsPlayer),
                  isBot(aIsBot),
                  isEnemy(aIsEnemy),
                  isBullet(aIsBullet),
                  isWall(aIsWall),
                  isBonus(aIsBonus),
                  isBackground(aIsBackground),
                  onlineId(aOnlineId),
                  isEnemyMissile(aIsEnemyMissile)
            {}

            bool isPlayer;
            bool isBot;
            bool isEnemy;
            bool isBullet;
            bool isWall;
            bool isBonus;
            bool isBackground;
            std::optional<size_t> onlineId;
            bool isEnemyMissile;
    };
} // namespace Component

#endif // !
