#ifndef WEIGHT_HPP_
#define WEIGHT_HPP_

namespace ECS::Utils {
    struct Weight
    {
            Weight()
                : weight(1)
            {}
            Weight(int aWeight)
                : weight(aWeight)
            {}
            int weight;
    };
} // namespace ECS::Utils

#endif // !
