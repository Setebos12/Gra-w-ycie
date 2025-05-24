#pragma once

#include "ParserKeyboard.h"


constexpr int KEY_S = 18; // 'S' for Start
constexpr int KEY_P = 15; // 'P' for Stop
constexpr int KEY_E = 4; // 'E' for End
constexpr int KEY_D = 3; // 'D' for ToggleDraw
constexpr int arrow_down = 88;
constexpr int arrow_up = 89;

InputToken ParseKeyBoard::parseKey(const int key) const {
    switch (key) {
    case KEY_S:
        return InputToken::Start;
    case KEY_P:
        return InputToken::Stop;
    case KEY_E:
        return InputToken::End;
    case KEY_D:
        return InputToken::ToggleDraw;
    case arrow_down:
        return InputToken::SpeedDown;
    case arrow_up:
        return InputToken::SpeedUp;
    default:
        return InputToken::Unknown;
    }
}