#ifndef SYSTEM_HPP_
#define SYSTEM_HPP_

#include "Components.hpp"
#include "EwECS/Event/KeyboardEvent.hpp"
#include "EwECS/Event/MouseEvent.hpp"
#include "EwECS/Event/WindowEvent.hpp"
#include "EwECS/Utils.hpp"
#include "EwECS/World.hpp"
#include <unordered_map>

namespace ECS {
    class System
    {
        public:
            /**
             * @brief Make an entity jump
             *
             * @param aPos SparseArray of all entities position
             * @param aJump Sparsearray of all entities who can jump
             * @param aWeight Sparsearray of all entities weight
             */
            static void jump(Core::SparseArray<ECS::Utils::Vector2f> &aPos, Core::SparseArray<Component::Jump> &aJump,
                             Core::SparseArray<Component::Weight> &aWeight);

            /**
             * @brief Move the ground
             *
             */
            static void moveGround();

            /**
             * @brief Kill the bird if it touches the ground or a pipe
             *
             */
            static void killBird();

            /**
             * @brief Display the pipes
             *
             * @param aPos SparseArray of all the entities position
             * @param aType SparseArray of all the entities type
             */
            static void displayPipes(Core::SparseArray<Utils::Vector2f> &aPos,
                                     Core::SparseArray<Component::TypeEntity> &aType);

            /**
             * @brief Kill the bird if it touch a pipe
             *
             * @param aPos SparseArray of all the entities position
             * @param aType SparseArray of all the entities type
             */
            static void killOnPipe(Core::SparseArray<Utils::Vector2f> &aPos,
                                   Core::SparseArray<Component::TypeEntity> &aType);

            /**
             * @brief Display the score
             *
             * @param aPos SparseArray of all the entities position
             * @param aType SparseArray of all the entities type
             */
            static void displayScore(Core::SparseArray<Utils::Vector2f> &aPos,
                                     Core::SparseArray<Component::TypeEntity> &aType);
    };
} // namespace ECS
#endif /* !SYSTEM_HPP_ */
