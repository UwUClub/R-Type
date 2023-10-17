/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Values
*/

#ifndef VALUES_HPP_
#define VALUES_HPP_
#include <string>

// ------------------ DISPLAY ------------------ //
const constexpr int SCREEN_WIDTH = 1000;
const constexpr int SCREEN_HEIGHT = 1000;

// //--------------- CONFIG ------------------ //
static const std::string CONFIG_PATH = "config/flappy_bird/";
static const std::string CONFIG_PLAYER = "player.json";
static const std::string CONFIG_PHYSICS = "physics.json";

//------------------ BACKGROUND ------------------//
const constexpr float BACKGROUND_SPEED = 300;
const constexpr int BACKGROUND_X_RES = 0;
const constexpr int BACKGROUND_Y_RES = 0;
static const std::string BACKGROUND_ASSET = "assets/sprites/background.png";

// ------------------ RETURN STATUS ------------------ //
const constexpr int SUCCESS = 0;
const constexpr int FAILURE = 84;

#endif /* !VALUES_HPP_ */
