#ifndef SYSTEM_HPP_
#define SYSTEM_HPP_

#include "Components.hpp"
#include "KeyboardEvent.hpp"
#include "MouseEvent.hpp"
#include "Utils.hpp"
#include "WindowEvent.hpp"
#include "World.hpp"

namespace ECS {
    class System
    {
        public:
            /**
             * @brief Welcome the players
             *
             * @param aPos SparseArray of all entities position
             * @param aSpeed Sparsearray of all entities speed
             * @param aType SparseArray of all entities type
             */
            static void welcomePlayers(Core::SparseArray<ECS::Utils::Vector2f> &aPos,
                                       Core::SparseArray<Component::Speed> &aSpeed,
                                       Core::SparseArray<Component::TypeEntity> &aType);

            /**
             * @brief Move the player
             *
             * @param aPos SparseArray of all entities position
             * @param aSpeed Sparsearray of all entities speed
             */
            static void movePlayer(Core::SparseArray<ECS::Utils::Vector2f> &aPos,
                                   Core::SparseArray<Component::Speed> &aSpeed);

            /**
             * @brief Spawn enemies
             *
             * @param aPos SparseArray of all entities position
             * @param aSpeed Sparsearray of all entities speed
             * @param aType SparseArray of all entities type
             * @param aHitBox SparseArray of all entities hitbox
             * @param aIsAlive SparseArray of all entities isAlive
             */
            static void spawnEnemy(Core::SparseArray<Utils::Vector2f> &aPos,
                                   Core::SparseArray<Component::Speed> &aSpeed,
                                   Core::SparseArray<Component::TypeEntity> &aType,
                                   Core::SparseArray<Component::HitBox> &aHitBox,
                                   Core::SparseArray<Component::IsAlive> &aIsAlive);

            /**
             * @brief Move enemies
             *
             * @param aPos SparseArray of all entities position
             * @param aSpeed Sparsearray of all entities speed
             * @param aType SparseArray of all entities type
             */
            static void moveEnemy(Core::SparseArray<Utils::Vector2f> &aPos, Core::SparseArray<Component::Speed> &aSpeed,
                                  Core::SparseArray<Component::TypeEntity> &aType);

            /**
             * @brief Make enemies shoot
             *
             * @param aPos SparseArray of all entities position
             * @param aSpeed Sparsearray of all entities speed
             * @param aType SparseArray of all entities type
             * @param aHitBox SparseArray of all entities hitbox
             * @param aIsAlive SparseArray of all entities isAlive
             */
            static void enemyShoot(Core::SparseArray<Utils::Vector2f> &aPos,
                                   Core::SparseArray<Component::Speed> &aSpeed,
                                   Core::SparseArray<Component::TypeEntity> &aType,
                                   Core::SparseArray<Component::HitBox> &aHitBox,
                                   Core::SparseArray<Component::IsAlive> &aIsAlive);

            /**
             * @brief Make players shoot
             *
             * @param aPos SparseArray of all entities position
             * @param aSpeed Sparsearray of all entities speed
             * @param aType SparseArray of all entities type
             * @param aHitBox SparseArray of all entities hitbox
             * @param aIsAlive SparseArray of all entities isAlive
             */
            static void playerShoot(Core::SparseArray<Utils::Vector2f> &aPos,
                                    Core::SparseArray<Component::Speed> &aSpeed,
                                    Core::SparseArray<Component::TypeEntity> &aType,
                                    Core::SparseArray<Component::HitBox> &aHitBox);
    };
} // namespace ECS
#endif /* !SYSTEM_HPP_ */
