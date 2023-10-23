#include <cstddef>
#include "Components.hpp"
#include "EwECS/SparseArray.hpp"

#ifndef RTYPE_UTILS_HPP_
    #define RTYPE_UTILS_HPP_

namespace RType {

    class TypeUtils
    {
        public:
            TypeUtils() = default;
            ~TypeUtils() = default;

            static TypeUtils &getInstance()
            {
                static TypeUtils instance;

                return instance;
            }

            static std::size_t getEntityIdByOnlineId(ECS::Core::SparseArray<Component::TypeEntity> &aType,
                                                     const std::size_t &aOnlineId);
    };

} // namespace RType

#endif // !RTYPE_UTILS_HPP_
