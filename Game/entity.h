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

class Entity : public Sprite {
private:
    string ObjectName;
    bool ObjectVisibility;
    pair<int, int> pos;
    pair<int, int> started_pos;
    Vector2f direction;
    vector<Tile>obstacle_tiles;
    FloatRect hitbox;
    bool attacking = false;
    float attack_cooldown = 0.5;
    Time attack_time;
    float frame_index;
    float animation_speed;
    map<string, vector<Texture> > anim_textures;
    map<string, float> stats;
    float speed;
public:
    Entity(string obj_name = "None", pair<int, int> pos = {0, 0}):
        ObjectName(obj_name),
        pos(pos),
        started_pos(pos),
        ObjectVisibility(false) {
            speed = 1;
            frame_index = 0;
            animation_speed = 0.15;
            direction.x = 1;
            direction.y = 0;
        };
    string get_name() {
        return ObjectName;
    }
    int get_frame_index() {
        return frame_index;
    }
    float get_animation_speed() {
        return animation_speed;
    }
    void set_frame_index(int value) {
        frame_index = value;
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
        // cout << "before: " << this->getPosition().x << " " << this->getPosition().y << "\n";
        this->setPosition(new_pos);
        // cout << new_pos.x << " " << new_pos.y << "\n";
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
    float get_speed() {
        return speed;
    }
    int get_direct_x() {
        return direction.x;
    }
    int get_direct_y() {
        return direction.y;
    }
    void set_direction(Vector2f value) {
        direction = value;
    }
    Vector2f get_direction() {
        return direction;
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
