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
const constexpr int SCREEN_WIDTH = 1920;
const constexpr int SCREEN_HEIGHT = 1080;

//------------------ ENEMY ------------------//
const constexpr float ENEMY_SPEED = 200;
const constexpr int ENEMY_TEX_WIDTH = 33;
const constexpr int ENEMY_TEX_HEIGHT = 33;
static const std::string ENEMY_ASSET = "assets/sprites/r-typesheet5.png";
const constexpr int PROBABILTY_SHOOT_ENEMY = 100;
const constexpr int ENEMY_SPAWN_INTERVAL = 5; // in seconds

//------------------ BACKGROUND ------------------//
const constexpr float BACKGROUND_SPEED = 300;
const constexpr int BACKGROUND_X_RES = 0;
const constexpr int BACKGROUND_Y_RES = 0;
static const std::string BACKGROUND_ASSET = "assets/sprites/background.png";

//------------------ PLAYER ------------------//
static const std::string PLAYER_ASSET = "assets/sprites/r-typesheet42.png";
const constexpr float PLAYER_SPEED = 10;
const constexpr int PLAYER_TEX_WIDTH = 33;
const constexpr int PLAYER_TEX_HEIGHT = 17;
const constexpr int MAX_NUMBER_PLAYER = 4;

//------------------ BULLET (for players) ------------------//
static const std::string BULLET_ASSET = "assets/sprites/r-typesheet2.png";
const constexpr float BULLET_SPEED = 800;
const constexpr int BULLET_TEX_WIDTH = 25;
const constexpr int BULLET_TEX_HEIGHT = 13;

//------------------ MISSILES (for enemies) ------------------//
static const std::string MISSILES_ASSET = "assets/sprites/r-typesheet2.png";
const constexpr float MISSILES_SPEED = 500;
const constexpr int MISSILES_TEX_WIDTH = 25;
const constexpr int MISSILES_TEX_HEIGHT = 13;

//------------------ EXPLOSION ------------------//
static const std::string EXPLOSION_ASSET = "assets/sprites/r-typesheet16.png";
const constexpr float EXPLOSION_SPEED = 0;
const constexpr int EXPLOSION_TEX_WIDTH = 23;
const constexpr int EXPLOSION_TEX_HEIGHT = 23;

// ------------------ RETURN STATUS ------------------ //
const constexpr int SUCCESS = 0;
const constexpr int FAILURE = 84;

//------------------ BONUS ------------------//
static const std::string BONUS_ASSET = "assets/sprites/powerup.png";
const constexpr float BONUS_SPEED = 200;
const constexpr int BONUS_TEX_WIDTH = 250;
const constexpr int BONUS_TEX_HEIGHT = 280;
const constexpr float BONUS_SCALE = 0.1;
const constexpr float BONUS_GAIN_FACTOR = 1.5;

// ------------------ LOADING MESSAGE ------------------ //
static const std::string LOADING_MESSAGE_ASSET = "assets/sprites/loading-message.png";
const constexpr int LOADING_MESSAGE_TEX_WIDTH = 700;
const constexpr int LOADING_MESSAGE_TEX_HEIGHT = 400;

// ------------------ SERVER FULL MESSAGE ------------------ //
static const std::string SERVER_FULL_MESSAGE = "assets/sprites/server-full-message.png";
const constexpr int SERVER_FULL_MESSAGE_TEX_WIDTH = 556;
const constexpr int SERVER_FULL_MESSAGE_TEX_HEIGHT = 95;

// ------------------ CRASH DETECTION ------------------ //
const constexpr float PACKET_TIMEOUT = 5;

#endif /* !VALUES_HPP_ */
