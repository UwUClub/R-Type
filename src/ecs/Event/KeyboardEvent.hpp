#ifndef KEYBOARDEVENT_HPP
#define KEYBOARDEVENT_HPP

namespace ECS::Event {
    enum class KeyIdentifier
    {
        A = 0,
        B = 1,
        C = 2,
        D = 3,
        E = 4,
        F = 5,
        G = 6,
        H = 7,
        I = 8,
        J = 9,
        K = 10,
        L = 11,
        M = 12,
        N = 13,
        O = 14,
        P = 15,
        Q = 16,
        R = 17,
        S = 18,
        T = 19,
        U = 20,
        V = 21,
        W = 22,
        X = 23,
        Y = 24,
        Z = 25,
        NUM_0 = 26,
        NUM_1 = 27,
        NUM_2 = 28,
        NUM_3 = 29,
        NUM_4 = 30,
        NUM_5 = 31,
        NUM_6 = 32,
        NUM_7 = 33,
        NUM_8 = 34,
        NUM_9 = 35,
        ESCAPE = 36,
        LCONTROL = 37,
        LSHIFT = 38,
        LALT = 39,
        LSYSTEM = 40,
        RCONTROL = 41,
        RSHIFT = 42,
        RALT = 43,
        RSYSTEM = 44,
        MENU = 45,
        LBRACKET = 46,
        RBRACKET = 47,
        SEMICOLON = 48,
        COMMA = 49,
        PERIOD = 50,
        QUOTE = 51,
        SLASH = 52,
        BACKSLASH = 53,
        TILDE = 54,
        EQUAL = 55,
        DASH = 56,
        SPACE = 57,
        RETURN = 58,
        BACKSPACE = 59,
        TAB = 60,
        PAGEUP = 61,
        PAGEDOWN = 62,
        END = 63,
        HOME = 64,
        INSERT = 65,
        DEL = 66,
        ADD = 67,
        SUBTRACT = 68,
        MULTIPLY = 69,
        DIVIDE = 70,
        LEFT = 71,
        RIGHT = 72,
        UP = 73,
        DOWN = 74,
        NUMPAD_0 = 75,
        NUMPAD_1 = 76,
        NUMPAD_2 = 77,
        NUMPAD_3 = 78,
        NUMPAD_4 = 79,
        NUMPAD_5 = 80,
        NUMPAD_6 = 81,
        NUMPAD_7 = 82,
        NUMPAD_8 = 83,
        NUMPAD_9 = 84,
        F1 = 85,
        F2 = 86,
        F3 = 87,
        F4 = 88,
        F5 = 89,
        F6 = 90,
        F7 = 91,
        F8 = 92,
        F9 = 93,
        F10 = 94,
        F11 = 95,
        F12 = 96
    };

    enum class KeyState
    {
        PRESSED = 0,
        RELEASED = 1
    };

    class KeyboardEvent
    {
        public:
            // -------------------CONSTRUCTORS / DESTRUCTOR-------------------//
            /**
             * @brief Construct a new Keyboard Event object
             *
             * @param aKey The key pressed.
             * @param aState The state of the key.
             * @param aIsShiftPressed Is the shift key pressed.
             * @param aIsCtrlPressed Is the ctrl key pressed.
             * @param aIsAltPressed Is the alt key pressed.
             * @param aIsSystemPressed Is the system key pressed.
             */
            KeyboardEvent(const KeyIdentifier &aKeyId, const KeyState &aKeyState, const bool &aIsShiftPressed = false,
                          const bool &aIsCtrlPressed = false, const bool &aIsAltPressed = false,
                          const bool &aIsSystemPressed = false);

            KeyboardEvent(const KeyboardEvent &keyboardEvent) = default;
            KeyboardEvent(KeyboardEvent &&keyboardEvent) = default;
            KeyboardEvent &operator=(const KeyboardEvent &keyboardEvent) = default;

            KeyboardEvent &operator=(KeyboardEvent &&keyboardEvent) noexcept = default;

            ~KeyboardEvent() = default;

            // -------------------ATTRIBUTES-------------------//
            KeyIdentifier _keyId;
            KeyState _state;
            bool _isShiftPressed;
            bool _isCtrlPressed;
            bool _isAltPressed;
            bool _isSystemPressed;
    };
} // namespace ECS::Event

#endif // !
