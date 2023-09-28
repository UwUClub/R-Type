#ifndef UTILS_HPP
#define UTILS_HPP

#include <SDL.h>

namespace ECS::Utils {
    struct Vector2i
    {
            Vector2i()
                : x(0),
                  y(0)
            {}
            Vector2i(int aX, int aY)
                : x(aX),
                  y(aY)
            {}
            int x;
            int y;
    };

    struct Vector2f
    {
            Vector2f()
                : x(0),
                  y(0)
            {}
            Vector2f(float aX, float aY)
                : x(aX),
                  y(aY)
            {}
            float x;
            float y;
    };

    struct Speed
    {
            Speed()
                : speed(0)
            {}
            Speed(float aSpeed)
                : speed(aSpeed)
            {}
            float speed;
    };

    struct TypeEntity
    {
            TypeEntity()
                : isPlayer(false),
                  isEnemy(false),
                  isBullet(false),
                  isWall(false),
                  isBonus(false)
            {}
            TypeEntity(bool aIsPlayer, bool aIsEnemy, bool aIsBullet, bool aIsWall, bool aIsBonus)
                : isPlayer(aIsPlayer),
                  isEnemy(aIsEnemy),
                  isBullet(aIsBullet),
                  isWall(aIsWall),
                  isBonus(aIsBonus)
            {}
            bool isPlayer;
            bool isEnemy;
            bool isBullet;
            bool isWall;
            bool isBonus;
    };

    struct LoadedSprite
    {
            LoadedSprite()
                : path(""),
                  texture(nullptr),
                  rect({0, 0, 0, 0}),
                  srcRect({0, 0, 0, 0})
            {}
            LoadedSprite(std::string aPath, SDL_Texture *aTexture, SDL_Rect aRect, SDL_Rect aSrcRect)
                : path(aPath),
                  texture(aTexture),
                  rect(aRect),
                  srcRect(aSrcRect)
            {}
            std::string path;
            SDL_Texture *texture;
            SDL_Rect rect;
            SDL_Rect srcRect;
    };

} // namespace ECS::Utils

#endif // !
