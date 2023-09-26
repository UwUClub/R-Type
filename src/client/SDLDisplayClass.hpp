/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** SDLDisplayClass
*/

#ifndef SDLDISPLAYClass_HPP_
#define SDLDISPLAYClass_HPP_

#define SCREEN_WIDTH  1920
#define SCREEN_HEIGHT 1080

#include <SDL2/SDL.h>
#include <string>
#include "KeyboardEvent.hpp"
#include "MouseEvent.hpp"
#include "WindowEvent.hpp"
#include <SDL2/SDL_image.h>
#include <unordered_map>

class SDLDisplayClass
{
    public:
        /**
         * @brief Destroy the SDLDisplayClass object
         * 
         */
        ~SDLDisplayClass();

        /**
         * @brief Get an Instance of the SDLDisplayClass (singleton)
         * 
         * @return SDLDisplayClass& 
         */
        static SDLDisplayClass &getInstance()
        {
            static SDLDisplayClass instance;

            return instance;
        }

        /**
         * @brief Construct a new SDLDisplayClass object
         * 
         */
        SDLDisplayClass();
        SDL_Renderer *_renderer;
        SDL_Window *_window;

    private:
};

#endif /* !SDLDISPLAYClass_HPP_ */
