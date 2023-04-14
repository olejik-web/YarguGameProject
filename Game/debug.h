#pragma once;
#include <Windows.h>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Font.hpp>
#include <iostream>

using namespace std;
using namespace sf;

Font DebugFont;

Text debug(string info, int y = 10, int x = 10) {
    Text text;
    text.setFont(DebugFont);
    text.setCharacterSize(30);
    text.setString(info);
    text.setPosition((float)x, (float)y);
    // cout << info << "\n";
    return text;
}
