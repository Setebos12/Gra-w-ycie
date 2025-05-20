#pragma once

#include "ParserKeyboard.h"


constexpr int KEY_S = 18; // 'S' for Start
constexpr int KEY_P = 15; // 'P' for Stop
constexpr int KEY_E = 3; // 'E' for End
constexpr int KEY_D = 4; // 'D' for ToggleDraw

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
    default:
        return InputToken::Unknown;
    }
}