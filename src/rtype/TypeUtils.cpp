#include "TypeUtils.hpp"

namespace RType {

    std::size_t TypeUtils::getEntityIdByOnlineId(ECS::Core::SparseArray<Component::TypeEntity> &aType,
                                                 const std::size_t &aOnlineId)
    {
        for (std::size_t i = 0; i < aType.size(); i++) {
            if (!aType[i].has_value()) {
                continue;
            }
            if (aType[i].value().onlineId == aOnlineId) {
                return i;
            }
        }
        return 0;
    }

} // namespace RType
