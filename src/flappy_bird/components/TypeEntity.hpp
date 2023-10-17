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
namespace Component {
    struct TypeEntity
    {
            /**
             * @brief Construct a new Type Entity object
             *
             */
            TypeEntity()
                : isPlayer(false),
                  isBackground(false)
            {}
            /**
             * @brief Construct a new Type Entity object
             *
             * @param aIsPlayer a boolean to know if the entity is a player
             * @param aIsBackground a boolean to know if the entity is a background
             */
            TypeEntity(bool aIsPlayer, bool aIsBackground)
                : isPlayer(aIsPlayer),
                  isBackground(aIsBackground)
            {}

            bool isPlayer;
            bool isBackground;
            std::optional<size_t> onlineId;
    };
} // namespace Component

#endif // !
