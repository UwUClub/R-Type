#ifndef SYSTEM_HPP_
#define SYSTEM_HPP_

#include "Utils.hpp"
#include "World.hpp"

namespace ECS {
    class System
    {
        public:
            static void movePlayer(Core::World &world, Core::SparseArray<ECS::Utils::Vector2f> &pos,
                                   Core::SparseArray<ECS::Utils::Speed> &speed,
                                   Core::SparseArray<ECS::Utils::TypeEntity> &type);
    };
} // namespace ECS
#endif /* !SYSTEM_HPP_ */
