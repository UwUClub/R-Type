/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Values
*/

#ifndef VALUES_HPP_
#define VALUES_HPP_
#include <string>

//------------------ VALUES ------------------//

const constexpr unsigned short READ_BUFFER_SIZE = 128;
const constexpr int SCREEN_WIDTH = 1920;
const constexpr int SCREEN_HEIGHT = 1080;

//------------------ ENEMY ------------------//

const constexpr float ENEMY_SPEED = 200;
const constexpr int ENEMY_TEX_WIDTH = 33;
const constexpr int ENEMY_TEX_HEIGHT = 33;
static const std::string ENEMY_ASSET = "assets/sprites/r-typesheet5.png";

//------------------ BACKGROUND ------------------//

const constexpr float BACKGROUND_SPEED = 300;
const constexpr int BACKGROUND_X_RES = 0;
const constexpr int BACKGROUND_Y_RES = 0;
static const std::string BACKGROUND_ASSET = "assets/sprites/background.png";

//------------------ PLAYER ------------------//

static const std::string PLAYER_ASSET = "assets/sprites/r-typesheet42.png";
const constexpr float PLAYER_SPEED = 3000;
const constexpr int PLAYER_TEX_WIDTH = 33;
const constexpr int PLAYER_TEX_HEIGHT = 17;

#endif /* !VALUES_HPP_ */