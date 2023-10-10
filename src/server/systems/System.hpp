#ifndef SYSTEM_HPP_
#define SYSTEM_HPP_

#include "Components.hpp"
#include "HitBox.hpp"
#include "KeyboardEvent.hpp"
#include "MouseEvent.hpp"
#include "SparseArray.hpp"
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
             * @param aHitBox SparseArray of all entities hitbox
             */
            static void welcomePlayer(Core::SparseArray<ECS::Utils::Vector2f> &aPos,
                                      Core::SparseArray<Component::Speed> &aSpeed,
                                      Core::SparseArray<Component::TypeEntity> &aType,
                                      Core::SparseArray<Component::HitBox> &aHitBox);

            /**
             * @brief Move the player
             *
             * @param aPos SparseArray of all entities position
             * @param aSpeed Sparsearray of all entities speed
             */
            static void movePlayer(Core::SparseArray<ECS::Utils::Vector2f> &aPos,
                                   Core::SparseArray<Component::Speed> &aSpeed);

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

            /**
             * @brief Handle players who get hit
             *
             * @param aPos SparseArray of all entities position
             * @param aType SparseArray of all entities type
             * @param aIsAlive SparseArray of all entities isAlive
             * @param aHitBox SparseArray of all entities hitbox
             */
            static void playerHit(Core::SparseArray<Utils::Vector2f> &aPos,
                                  Core::SparseArray<Component::TypeEntity> &aType,
                                  Core::SparseArray<Component::IsAlive> &aIsAlive,
                                  Core::SparseArray<Component::HitBox> &aHitBox);

            /**
             * @brief Handle players who get hit
             *
             * @param aType SparseArray of all entities type
             * @param aIsAlive SparseArray of all entities isAlive
             */
            static void killPlayer(Core::SparseArray<Component::TypeEntity> &aType,
                                   Core::SparseArray<Component::IsAlive> &aIsAlive);

            /**
             * @brief Disconnect the player from the server
             */
            static void disconnectPlayer();

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
             * @brief Handle enemies who get hit
             *
             * @param aPos SparseArray of all entities position
             * @param aType SparseArray of all entities type
             * @param aHitBox SparseArray of all entities hitbox
             * @param aIsAlive SparseArray of all entities isAlive
             */
            static void enemyHit(Core::SparseArray<Utils::Vector2f> &aPos,
                                 Core::SparseArray<Component::TypeEntity> &aType,
                                 Core::SparseArray<Component::HitBox> &aHitBox,
                                 Core::SparseArray<Component::IsAlive> &aIsAlive);

            /**
             * @brief Kill enemies when they shouldn't live anymore
             *
             * @param aPos SparseArray of all entities position
             * @param aIsAlive SparseArray of all entities isAlive
             */
            static void killEnemy(Core::SparseArray<Component::TypeEntity> &aType,
                                  Core::SparseArray<Component::IsAlive> &aIsAlive);

            /**
             * @brief Move missiles
             *
             * @param aPos SparseArray of all entities position
             * @param aSpeed Sparsearray of all entities speed
             * @param aType SparseArray of all entities type
             */
            static void moveMissiles(Core::SparseArray<Utils::Vector2f> &aPos,
                                     Core::SparseArray<Component::Speed> &aSpeed,
                                     Core::SparseArray<Component::TypeEntity> &aType);
    };
} // namespace ECS
#endif /* !SYSTEM_HPP_ */
