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

//------------------ BACKGROUND ------------------//
const constexpr float BACKGROUND_SPEED = 300;
const constexpr int BACKGROUND_X_RES = 0;
const constexpr int BACKGROUND_Y_RES = 0;
static const std::string BACKGROUND_ASSET = "assets/sprites/background.png";

//------------------ PLAYER ------------------//
static const std::string PLAYER_ASSET = "assets/sprites/bluebird-upflap.png";
const constexpr float PLAYER_SPEED = 10;
const constexpr float PLAYER_WEIGHT = 1;
const constexpr float PLAYER_JUMP_HEIGHT = 260;
const constexpr float PLAYER_JUMP_STRENGTH = 4;
const constexpr float PLAYER_JUMP_FLOATING = 10;
const constexpr int PLAYER_TEX_WIDTH = 34;
const constexpr int PLAYER_TEX_HEIGHT = 24;

// ------------------ RETURN STATUS ------------------ //
const constexpr int SUCCESS = 0;
const constexpr int FAILURE = 84;

#endif /* !VALUES_HPP_ */
