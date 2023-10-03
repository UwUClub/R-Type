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
            /**
             * @brief Construct a new Type Entity object
             *
             * @param aIsPlayer a boolean to know if the entity is a player
             * @param aIsEnemy a boolean to know if the entity is an enemy
             * @param aIsBullet a boolean to know if the entity is a bullet
             * @param aIsWall a boolean to know if the entity is a wall
             * @param aIsBonus a boolean to know if the entity is a bonus
             * @param aIsBackground a boolean to know if the entity is a background
             */
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
