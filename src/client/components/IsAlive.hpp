#ifndef ISALIVE_HPP_
    #define ISALIVE_HPP_

namespace Component {
    struct IsAlive {
        /**
         * @brief Construct a new Is Alive object
         * 
         */
        IsAlive()
            : isAlive(true),
              timeToDie(0)
        {}
        /**
         * @brief Construct a new Is Alive object
         * 
         * @param aIsAlive a boolean to know if the entity is alive
         * @param aTimeToDie the time of dying animation
         */
        IsAlive(bool aIsAlive, float aTimeToDie)
            : isAlive(aIsAlive),
              timeToDie(aTimeToDie)
        {}
        bool isAlive;
        float timeToDie;
    };
} // namespace Component

#endif /* !ISALIVE_HPP_ */
