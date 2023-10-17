#ifndef WEIGHT_HPP_
#define WEIGHT_HPP_

namespace Component {
    struct Weight
    {
            Weight()
                : weight(1)
            {}
            Weight(float aWeight)
                : weight(aWeight)
            {}
            float weight;
    };
} // namespace Component

#endif // !
