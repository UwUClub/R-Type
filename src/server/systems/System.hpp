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
             * @param aIsAlive SparseArray of all entities isAlive
             * @param aConnection SparseArray of all entities connection
             */
            static void welcomePlayer(Core::SparseArray<ECS::Utils::Vector2f> &aPos,
                                      Core::SparseArray<Component::Speed> &aSpeed,
                                      Core::SparseArray<Component::TypeEntity> &aType,
                                      Core::SparseArray<Component::HitBox> &aHitBox,
                                      Core::SparseArray<Component::IsAlive> &aIsAlive,
                                      Core::SparseArray<Component::Connection> &aConnection);

            /**
             * @brief Move the player
             *
             * @param aPos SparseArray of all entities position
             * @param aSpeed Sparsearray of all entities speed
             * @param aConnection SparseArray of all entities connection
             */
            static void movePlayer(Core::SparseArray<ECS::Utils::Vector2f> &aPos,
                                   Core::SparseArray<Component::Speed> &aSpeed,
                                   Core::SparseArray<Component::Connection> &aConnection);

            /**
             * @brief Make players shoot
             *
             * @param aPos SparseArray of all entities position
             * @param aSpeed Sparsearray of all entities speed
             * @param aType SparseArray of all entities type
             * @param aHitBox SparseArray of all entities hitbox
             * @param aIsAlive SparseArray of all entities isAlive
             * @param aConnection SparseArray of all entities connection
             */
            static void playerShoot(Core::SparseArray<Utils::Vector2f> &aPos,
                                    Core::SparseArray<Component::Speed> &aSpeed,
                                    Core::SparseArray<Component::TypeEntity> &aType,
                                    Core::SparseArray<Component::HitBox> &aHitBox,
                                    Core::SparseArray<Component::Connection> &aConnection);

            /**
             * @brief Move the player speed up
             *
             * @param aSpeed Sparsearray of all entities speed
             * @param aConnection SparseArray of all entities connection
             */
            static void moveSpeedUp(Core::SparseArray<Component::Speed> &aSpeed,
                                    Core::SparseArray<Component::Connection> &aConnection);

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
             * @param aConnection SparseArray of all entities connection
             */
            static void killPlayer(Core::SparseArray<Component::TypeEntity> &aType,
                                   Core::SparseArray<Component::IsAlive> &aIsAlive,
                                   Core::SparseArray<Component::Connection> &aConnection);

            /**
             * @brief Disconnect the player from the server
             *
             * @param aConnection SparseArray of all entities connection
             */
            static void disconnectPlayer(Core::SparseArray<Component::Connection> &aConnection);

            /**
             * @brief Handle player crash
             *
             * @param aIsAlive SparseArray of all entities isAlive
             * @param aType SparseArray of all entities type
             * @param aConnection SparseArray of all entities connection
             */
            static void handlePlayerCrash(Core::SparseArray<Component::IsAlive> &aIsAlive,
                                          Core::SparseArray<Component::TypeEntity> &aType,
                                          Core::SparseArray<Component::Connection> &aConnection);

            /**
             * @brief Receive client aknowledgment
             *
             * @param aConnection SparseArray of all entities connection status
             */
            static void receiveAknowledgment(Core::SparseArray<Component::Connection> &aConnection);

            /**
             * @brief Spawn enemies
             *
             * @param aPos SparseArray of all entities position
             * @param aSpeed Sparsearray of all entities speed
             * @param aType SparseArray of all entities type
             * @param aHitBox SparseArray of all entities hitbox
             * @param aIsAlive SparseArray of all entities isAlive
             * @param aConnection SparseArray of all entities connection
             */
            static void spawnEnemy(Core::SparseArray<Utils::Vector2f> &aPos,
                                   Core::SparseArray<Component::Speed> &aSpeed,
                                   Core::SparseArray<Component::TypeEntity> &aType,
                                   Core::SparseArray<Component::HitBox> &aHitBox,
                                   Core::SparseArray<Component::IsAlive> &aIsAlive,
                                   Core::SparseArray<Component::Connection> &aConnection);

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
             * @param aConnection SparseArray of all entities connection
             */
            static void enemyShoot(Core::SparseArray<Utils::Vector2f> &aPos,
                                   Core::SparseArray<Component::Speed> &aSpeed,
                                   Core::SparseArray<Component::TypeEntity> &aType,
                                   Core::SparseArray<Component::HitBox> &aHitBox,
                                   Core::SparseArray<Component::IsAlive> &aIsAlive,
                                   Core::SparseArray<Component::Connection> &aConnection);

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
             * @param aConnection SparseArray of all entities connection
             */
            static void killEnemy(Core::SparseArray<Component::TypeEntity> &aType,
                                  Core::SparseArray<Component::IsAlive> &aIsAlive,
                                  Core::SparseArray<Component::Connection> &aConnection);

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
