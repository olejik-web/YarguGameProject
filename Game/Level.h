#pragma once;
#include <Windows.h>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <iostream>
#include <vector>
#include <iostream>
#include "settings.h"
#include "tile.h"
#include "player.h"

using namespace std;
using namespace sf;

class Level {
private:
    vector<Sprite>visible_sprites;
    vector<Sprite>obstacle_sprites;
    Texture Rock_Texture;
public:
    Level() {
        visible_sprites = vector<Sprite>(0);
        obstacle_sprites = vector<Sprite>(0);
        Image image;
        image.loadFromFile("rock.png");
        Rock_Texture.loadFromImage(image);
        this->create_map();
    }
    void create_map() {
        int x, y;
        for (int i=0; i<WORLD_MAP.size(); i++) {
            for (int j=0; j<WORLD_MAP[i].size(); j++) {
                x = j * TILESIZE;
                y = i * TILESIZE;
                if (WORLD_MAP[i][j] == 'x') {
                    Tile tile({x, y});
                    visible_sprites.push_back(tile.get_sprite());
                }
            }
        }
    }
    void run(RenderWindow &screen) {
        for (auto sprite : visible_sprites) {
            sprite.setTexture(Rock_Texture);
            screen.draw(sprite);
        }
    }
};
