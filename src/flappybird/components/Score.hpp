#include <string>

#ifndef SCORE_HPP
    #define SCORE_HPP

namespace Component {
    struct Score
    {
            /**
             * @brief Construct a new Speed object
             *
             */
            Score()
                : score(0)
            {}
            /**
             * @brief Construct a new Speed object
             *
             * @param aScore The score value
             */
            explicit Score(float aScore)
                : score(aScore)
            {}
            unsigned short score;
    };
} // namespace Component
#endif // DEBUG
