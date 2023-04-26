#pragma once;
#include <Windows.h>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Rect.hpp>
#include "settings.h"
#include "tile.h"
#include <iostream>
#include <vector>
#include "SFML/Window/Keyboard.hpp"

using namespace std;
using namespace sf;

class Player : public GameObject {
private:
    Vector2f direction;
    float speed;
    vector<Tile>obstacle_tiles;
    FloatRect hitbox;
public:
    Player(string obj_name = "None", pair<int, int> pos = {0, 0},
            vector<Tile> obstacle_tiles = {}):
        GameObject(obj_name, pos) {
        speed = 2.2;
        obstacle_tiles = obstacle_tiles;
        this->setPosition((float)pos.first, (float)pos.second);
    }
    void input() {
        if (Keyboard::isKeyPressed(Keyboard::Up)) {
            direction.y = -1;
        }
        else if(Keyboard::isKeyPressed(Keyboard::Down)) {
            direction.y = 1;
        }
        else {
            direction.y = 0;
        }
        if (Keyboard::isKeyPressed(Keyboard::Right)) {
            direction.x = 1;
        }
        else if(Keyboard::isKeyPressed(Keyboard::Left)) {
            direction.x = -1;
        }
        else {
            direction.x = 0;
        }
    }
    float get_speed() {
        return speed;
    }
    void move(float speed) {
        float direction_length = sqrt(direction.x * direction.x + direction.y * direction.y);
        if (direction_length != 0) {
            direction.x /= direction_length;
            direction.y /= direction_length;
        }
        Vector2f move_vector;
        move_vector.x = 0;
        move_vector.y = 0;
        move_vector.x = direction.x * speed;
        Vector2f hitbox_pos(hitbox.left, hitbox.top);
        hitbox_pos += move_vector;
        hitbox = FloatRect(hitbox_pos, Vector2f(hitbox.width, hitbox.height));
        collision("horizontal");
        hitbox_pos = Vector2f(hitbox.left, hitbox.top);
        move_vector.x = 0;
        move_vector.y = direction.y * speed;
        hitbox_pos += move_vector;
        hitbox = FloatRect(hitbox_pos, Vector2f(hitbox.width, hitbox.height));
        collision("vertical");
        Vector2f new_pos(hitbox.left, hitbox.top - 15);
        this->setPosition(new_pos);
    }
    void collision(string way) {
        if (way == "horizontal") {
            for (auto tile : obstacle_tiles) {
                FloatRect tile_hitbox = tile.get_hitbox();
                Vector2f tile_hitbox_pos = Vector2f(tile_hitbox.left, tile_hitbox.top);
                if (tile_hitbox.intersects(hitbox)) {
                    if (direction.x > 0) {
                        hitbox.left = tile_hitbox_pos.x - hitbox.width;
                    }
                    if (direction.x < 0) {
                        hitbox.left = tile_hitbox_pos.x + tile_hitbox.width;
                    }
                }
            }
        }
        if (way == "vertical") {
            for (auto tile : obstacle_tiles) {
                FloatRect tile_hitbox = tile.get_hitbox();
                Vector2f tile_hitbox_pos = Vector2f(tile_hitbox.left, tile_hitbox.top);
                if (tile_hitbox.intersects(hitbox)) {
                    if (direction.y > 0) {
                        hitbox.top = tile_hitbox_pos.y - hitbox.height;
                    }
                    if (direction.y < 0) {
                        hitbox.top = tile_hitbox_pos.y + tile_hitbox.height;
                    }
                }
            }
        }
    }
    void update(float time) {
        this->input();
        this->move(speed);
    }
    int get_direct_x() {
        return direction.x;
    }
    int get_direct_y() {
        return direction.y;
    }
    void set_obstacle_tiles(vector<Tile> &value) {
        obstacle_tiles = value;
    }
    vector<Tile> get_obstacle_tiles() {
        return obstacle_tiles;
    }
    void set_hitbox(FloatRect value) {
        hitbox = value;
    }
    void cout_hitbox() {
        cout << "hitbox: " << hitbox.top << " " << hitbox.height << "\n";
    }
    void cout_rect() {
        FloatRect rect = this->getGlobalBounds();
        cout << "rect: " << rect.top << " " << rect.height << "\n";
    }
    FloatRect get_hitbox() {
        return hitbox;
    }
};
