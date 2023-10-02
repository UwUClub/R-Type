#ifndef SYSTEM_HPP_
#define SYSTEM_HPP_

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
             * @param world A reference to the world
             * @param aPos SparseArray of all entities position
             * @param aSpeed Sparsearray of all entities speed
             * @param aType SparseArray of all entities type
             */
            static void welcomePlayers(Core::World &world, Core::SparseArray<ECS::Utils::Vector2f> &aPos,
                                       Core::SparseArray<ECS::Utils::Speed> &aSpeed,
                                       Core::SparseArray<ECS::Utils::TypeEntity> &aType);

            /**
             * @brief Move the player
             *
             * @param aWorld A reference to the world
             * @param aPos SparseArray of all entities position
             * @param aSpeed Sparsearray of all entities speed
             * @param aType SparseArray of all entities type
             */
            static void movePlayer(Core::World &aWorld, Core::SparseArray<ECS::Utils::Vector2f> &aPos,
                                   Core::SparseArray<ECS::Utils::Speed> &aSpeed,
                                   Core::SparseArray<ECS::Utils::TypeEntity> &aType);
    };
} // namespace ECS
#endif /* !SYSTEM_HPP_ */
