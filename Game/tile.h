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
#include <string>

using namespace std;
using namespace sf;

void inflate_rect(FloatRect &rect, int x=0, int y=0) {
    rect.height += y;
    rect.top -= y / 2;
    rect.width += x;
    rect.left -= x / 2;
}

class GameObject : public Sprite {
private:
    string ObjectName;
    bool ObjectVisibility;
    pair<int, int> pos;
    pair<int, int> started_pos;
    FloatRect hitbox;
public:
    GameObject(string obj_name = "None", pair<int, int> pos = {0, 0}):
        ObjectName(obj_name),
        pos(pos),
        started_pos(pos),
        ObjectVisibility(false) {};
    string get_name() {
        return ObjectName;
    }
    bool isVisible() {
        return ObjectVisibility;
    }
    void set_visibility(bool value) {
        ObjectVisibility = value;
    }
    void set_pos(pair<int, int> pos) {
        pos = pos;
        started_pos = pos;
        this->setPosition((float)pos.first, (float)pos.second);
    }
    pair<int, int> get_started_pos() {
        return started_pos;
    }
    void set_name(string value) {
        ObjectName = value;
    }
};

class Tile : public GameObject {
private:
    FloatRect hitbox;
public:
    Tile(string obj_name = "None", pair<int, int> pos = {0, 0}):
        GameObject(obj_name, pos) {
        this->setPosition((float)pos.first, (float)pos.second);
    }
    void update() {
        cout << "tile-update\n";
    }
    void set_hitbox(FloatRect value) {
        hitbox = value;
        if (this->get_name() == "object") {
            hitbox.top += TILESIZE;
            hitbox.height -= TILESIZE;
        }
        hitbox.height -= 10;
    }
    FloatRect get_hitbox() {
        return hitbox;
    }
    void cout_hitbox() {
        cout << "hitbox: " << hitbox.width << " " << hitbox.height << "\n";
    }
    void cout_rect() {
        FloatRect rect = this->getGlobalBounds();
        cout << "rect: " << rect.width << " " << rect.height << "\n";
    }
};
