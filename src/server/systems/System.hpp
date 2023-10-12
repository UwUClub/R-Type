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
            //---------PLAYER----------//
            /**
             * @brief Welcome the players
             *
             * @param aEvent Event to handle
             */
            static void welcomePlayer(RType::ServerGameEvent *aEvent);

            /**
             * @brief Move the player
             *
             * @param aEvent Event to handle
             */
            static void movePlayer(RType::ServerGameEvent *aEvent);

            /**
             * @brief Make players shoot
             *
             * @param aEvent Event to handle
             */
            static void playerShoot(RType::ServerGameEvent *aEvent);

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
             * @param aEvent Event to handle
             */
            static void disconnectPlayer(RType::ServerGameEvent *aEvent);

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

            //---------NETWORK----------//
            /**
             * @brief Receive client aknowledgment
             *
             * @param aEvent Event to handle
             */
            static void receiveAknowledgment(RType::ServerGameEvent *aEvent);

            //---------ENEMY----------//
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

            //---------MISSILE----------//
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

            //---------BONUS----------//
            /**
             * @brief Move the player speed up
             *
             * @param aEvent Event to handle
             */
            static void moveSpeedUp(RType::ServerGameEvent *aEvent);
    };
} // namespace ECS
#endif /* !SYSTEM_HPP_ */
