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
            TypeEntity()
                : isPlayer(false),
                  isBot(false),
                  isEnemy(false),
                  isBullet(false),
                  isWall(false),
                  isBonus(false),
                  isBackground(false)
            {}
            TypeEntity(bool aIsPlayer, bool aIsBot, bool aIsEnemy, bool aIsBullet, bool aIsWall, bool aIsBonus,
                       bool aIsBackground)
                : isPlayer(aIsPlayer),
                  isBot(aIsBot),
                  isEnemy(aIsEnemy),
                  isBullet(aIsBullet),
                  isWall(aIsWall),
                  isBonus(aIsBonus),
                  isBackground(aIsBackground)
            {}
            TypeEntity(bool aIsPlayer, bool aIsBot, bool aIsEnemy, bool aIsBullet, bool aIsWall, bool aIsBonus,
                       bool aIsBackground, size_t aOnlineId)
                : isPlayer(aIsPlayer),
                  isBot(aIsBot),
                  isEnemy(aIsEnemy),
                  isBullet(aIsBullet),
                  isWall(aIsWall),
                  isBonus(aIsBonus),
                  isBackground(aIsBackground),
                  onlineId(aOnlineId)
            {}

            bool isPlayer;
            bool isBot;
            bool isEnemy;
            bool isBullet;
            bool isWall;
            bool isBonus;
            bool isBackground;
            std::optional<size_t> onlineId;
    };
} // namespace Component

#endif // !
