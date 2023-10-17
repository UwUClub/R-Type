/*
** EPITECH PROJECT, 2023
** Flappy Bird
** File description:
** TypeEntity
*/

#include <cstddef>
#include <optional>

#ifndef TYPEENTITY_HPP
    #define TYPEENTITY_HPP

enum EntityType
{
    PLAYER,
    BACKGROUND,
    BASE,
    PIPE,
    BIRD,
    GROUND,
    SCORE,
    GAMEOVER,
    RESTART,
    QUIT,
    NONE
};

namespace Component {
    struct TypeEntity
    {
            /**
             * @brief Construct a new Type Entity object
             *
             */
            TypeEntity()
            {}
            /**
             * @brief Construct a new Type Entity object
             *
             *
             */
            TypeEntity(EntityType aType)
                : type(aType)
            {}

            EntityType type = NONE;
    };
} // namespace Component

#endif // !
