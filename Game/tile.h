#pragma once;
#include <Windows.h>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Rect.hpp>
#include "settings.h"
#include <iostream>
#include <vector>

using namespace std;
using namespace sf;

class Tile {
private:
    Sprite SpriteTile;
    Texture texture;
    Image image;
    IntRect rect;
    pair<int, int> pos;
public:
    Tile(pair<int, int> pos = {0, 0}) {
        pos = pos;
        SpriteTile.setPosition((float)pos.first, (float)pos.second);
    }
    Sprite get_sprite() {
        cout << texture.getSize().x << " " << texture.getSize().y << "\n";
        return SpriteTile;
    }
};
