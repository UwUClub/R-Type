/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** TypeEntity
*/

#ifndef TYPEENTITY_HPP
#define TYPEENTITY_HPP
namespace Component {
    struct TypeEntity
    {
            TypeEntity()
                : isPlayer(false),
                  isEnemy(false),
                  isBullet(false),
                  isWall(false),
                  isBonus(false),
                  isBackground(false)
            {}
            TypeEntity(bool aIsPlayer, bool aIsEnemy, bool aIsBullet, bool aIsWall, bool aIsBonus, bool aIsBackground)
                : isPlayer(aIsPlayer),
                  isEnemy(aIsEnemy),
                  isBullet(aIsBullet),
                  isWall(aIsWall),
                  isBonus(aIsBonus),
                  isBackground(aIsBackground)
            {}

            bool isPlayer;
            bool isEnemy;
            bool isBullet;
            bool isWall;
            bool isBonus;
            bool isBackground;
    };
} // namespace Component

#endif // !
