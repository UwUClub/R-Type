/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Inputs
*/

#pragma once
extern "C"
{
#include "raylib.h"
}

namespace Raylib {

    enum class KeyboardKey : int
    {
        KB_NULL = KEY_NULL,
        KB_APOSTROPHE = KEY_APOSTROPHE,
        KB_COMMA = KEY_COMMA,
        KB_MINUS = KEY_MINUS,
        KB_PERIOD = KEY_PERIOD,
        KB_SLASH = KEY_SLASH,
        KB_ZERO = KEY_ZERO,
        KB_ONE = KEY_ONE,
        KB_TWO = KEY_TWO,
        KB_THREE = KEY_THREE,
        KB_FOUR = KEY_FOUR,
        KB_FIVE = KEY_FIVE,
        KB_SIX = KEY_SIX,
        KB_SEVEN = KEY_SEVEN,
        KB_EIGHT = KEY_EIGHT,
        KB_NINE = KEY_NINE,
        KB_SEMICOLON = KEY_SEMICOLON,
        KB_EQUAL = KEY_EQUAL,
        KB_A = KEY_A,
        KB_B = KEY_B,
        KB_C = KEY_C,
        KB_D = KEY_D,
        KB_E = KEY_E,
        KB_F = KEY_F,
        KB_G = KEY_G,
        KB_H = KEY_H,
        KB_I = KEY_I,
        KB_J = KEY_J,
        KB_K = KEY_K,
        KB_L = KEY_L,
        KB_M = KEY_M,
        KB_N = KEY_N,
        KB_O = KEY_O,
        KB_P = KEY_P,
        KB_Q = KEY_Q,
        KB_R = KEY_R,
        KB_S = KEY_S,
        KB_T = KEY_T,
        KB_U = KEY_U,
        KB_V = KEY_V,
        KB_W = KEY_W,
        KB_X = KEY_X,
        KB_Y = KEY_Y,
        KB_Z = KEY_Z,
        KB_LEFT_BRACKET = KEY_LEFT_BRACKET,
        KB_BACKSLASH = KEY_BACKSLASH,
        KB_RIGHT_BRACKET = KEY_RIGHT_BRACKET,
        KB_GRAVE = KEY_GRAVE,
        KB_SPACE = KEY_SPACE,
        KB_ESCAPE = KEY_ESCAPE,
        KB_ENTER = KEY_ENTER,
        KB_TAB = KEY_TAB,
        KB_BACKSPACE = KEY_BACKSPACE,
        KB_INSERT = KEY_INSERT,
        KB_DELETE = KEY_DELETE,
        KB_RIGHT = KEY_RIGHT,
        KB_LEFT = KEY_LEFT,
        KB_DOWN = KEY_DOWN,
        KB_UP = KEY_UP,
        KB_PAGE_UP = KEY_PAGE_UP,
        KB_PAGE_DOWN = KEY_PAGE_DOWN,
        KB_HOME = KEY_HOME,
        KB_END = KEY_END,
        KB_CAPS_LOCK = KEY_CAPS_LOCK,
        KB_SCROLL_LOCK = KEY_SCROLL_LOCK,
        KB_NUM_LOCK = KEY_NUM_LOCK,
        KB_PRINT_SCREEN = KEY_PRINT_SCREEN,
        KB_PAUSE = KEY_PAUSE,
        KB_F1 = KEY_F1,
        KB_F2 = KEY_F2,
        KB_F3 = KEY_F3,
        KB_F4 = KEY_F4,
        KB_F5 = KEY_F5,
        KB_F6 = KEY_F6,
        KB_F7 = KEY_F7,
        KB_F8 = KEY_F8,
        KB_F9 = KEY_F9,
        KB_F10 = KEY_F10,
        KB_F11 = KEY_F11,
        KB_F12 = KEY_F12,
        KB_LEFT_SHIFT = KEY_LEFT_SHIFT,
        KB_LEFT_CONTROL = KEY_LEFT_CONTROL,
        KB_LEFT_ALT = KEY_LEFT_ALT,
        KB_LEFT_SUPER = KEY_LEFT_SUPER,
        KB_RIGHT_SHIFT = KEY_RIGHT_SHIFT,
        KB_RIGHT_CONTROL = KEY_RIGHT_CONTROL,
        KB_RIGHT_ALT = KEY_RIGHT_ALT,
        KB_RIGHT_SUPER = KEY_RIGHT_SUPER,
        KB_MENU = KEY_MENU,
    };

    enum class MouseButton : int
    {
        MOUSE_BTN_LEFT = MOUSE_BUTTON_LEFT,
        MOUSE_BTN_RIGHT = MOUSE_BUTTON_RIGHT,
        MOUSE_BTN_MIDDLE = MOUSE_BUTTON_LEFT,
        MOUSE_BTN_SIDE = MOUSE_BUTTON_SIDE,
        MOUSE_BTN_EXTRA = MOUSE_BUTTON_EXTRA,
        MOUSE_BTN_FORWARD = MOUSE_BUTTON_FORWARD,
        MOUSE_BTN_BACK = MOUSE_BUTTON_BACK,
    };
} // namespace Raylib
