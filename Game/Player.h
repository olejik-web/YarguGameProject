#pragma once;
#include <Windows.h>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Rect.hpp>
#include "settings.h"
#include "tile.h"
#include "Level.h"
#include <iostream>
#include <vector>
#include <map>
#include "SFML/Window/Keyboard.hpp"

using namespace std;
using namespace sf;

struct WeaponData {
    string name;
    float cooldown;
    float damage;
    string texture_path;
};

struct MagicData {
    string name;
    float strength;
    float cost;
    string texture_path;
};

bool get_contain (string t, string s) {
    if (t.size() > s.size()) return false;
    for (int i=0; i<=s.size() - t.size(); i++) {
        int cnt = 0;
        for (int j=i; j<i + t.size(); j++) {
            if (t[j - i] == s[j]) {
                cnt++;
            }
        }
        if (cnt == t.size()) {
            return true;
        }
    }
    return false;
}

string str_replace(string main_str, string old_str, string new_str) {
    for (int i=0; i<=main_str.size() - old_str.size(); i++) {
        int cnt = 0;
        for (int j=i; j<i + old_str.size(); j++) {
            if (old_str[j - i] == main_str[j]) {
                cnt++;
            }
        }
        if (cnt == old_str.size()) {
            string replaced = "";
            for (int k=0; k<i; k++) {
                replaced += main_str[k];
            }
            replaced += new_str;
            for (int k=i + old_str.size(); k<main_str.size(); k++) {
                replaced += main_str[k];
            }
            return replaced;
        }
    }
    return main_str;
}

class Player : public GameObject {
private:
    Vector2f direction;
    vector<Tile>obstacle_tiles;
    FloatRect hitbox;
    // weapon
    bool attacking = false;
    float attack_cooldown = 0.5;
    Time attack_time;
    bool can_switch_weapon = true;
    Time weapon_switch_time;
    float switch_duration_cooldown = 0.5;
    bool nead_create_attack;
    bool nead_destroy_attack;
    int weapon_index = 0;
    vector<string>weapon_names;
    map<string, map<string, Texture> > weapon_textures;
    //
    // magic
    int magic_index = 0;
    vector<MagicData>magic_datas;
    vector<Texture>magic_textures;
    bool can_switch_magic = true;
    Time magic_switch_time;
    //
    string status;
    float frame_index;
    float animation_speed;
    map<string, vector<Texture> > anim_textures;
    map<string, float> stats;
    float health;
    float energy;
    float exp;
    float speed;
public:
    float get_health() {
        return health;
    }
    float get_energy() {
        return energy;
    }
    float get_exp() {
        return exp;
    }
    float get_max_health() {
        return stats["health"];
    }
    float get_max_energy() {
        return stats["energy"];
    }
    bool get_can_switch_weapon() {
        return can_switch_weapon;
    }
    bool get_can_switch_magic() {
        return can_switch_magic;
    }
    Player(string obj_name = "None", pair<int, int> pos = {0, 0},
            vector<Tile> obstacle_tiles = {}):
        GameObject(obj_name, pos) {
        speed = 1.2;
        obstacle_tiles = obstacle_tiles;
        status = "down";
        frame_index = 0;
        animation_speed = 0.025;
        nead_create_attack = false;
        nead_destroy_attack = false;
        weapon_names = vector<string>(5);
        weapon_names[0] = "sword";
        weapon_names[1] = "axe";
        weapon_names[2] = "lance";
        weapon_names[3] = "rapier";
        weapon_names[4] = "sai";
        stats["health"] = 100;
        stats["energy"] = 60;
        stats["attack"] = 10;
        stats["magic"] = 4;
        stats["speed"] = 1.2;
        magic_datas = vector<MagicData>(2);
        magic_datas[0] = MagicData();
        magic_datas[0].name = "flame";
        magic_datas[0].strength = 5;
        magic_datas[0].cost = 20;
        magic_datas[0].texture_path = "graphics/particles/flame/fire.png";
        magic_datas[1] = MagicData();
        magic_datas[1].name = "heal";
        magic_datas[1].strength = 20;
        magic_datas[1].cost = 10;
        magic_datas[1].texture_path = "graphics/particles/heal/heal.png";
        health = stats["health"] * 0.4;
        energy = stats["energy"] * 0.6;
        exp = 123;
        speed = stats["speed"];
        this->setPosition((float)pos.first, (float)pos.second);
        anim_textures["up"] = vector<Texture>(4);
        anim_textures["up"][0].loadFromFile("graphics/player/up/up_0.png");
        anim_textures["up"][1].loadFromFile("graphics/player/up/up_1.png");
        anim_textures["up"][2].loadFromFile("graphics/player/up/up_2.png");
        anim_textures["up"][3].loadFromFile("graphics/player/up/up_3.png");
        anim_textures["down"] = vector<Texture>(4);
        anim_textures["down"][0].loadFromFile("graphics/player/down/down_0.png");
        anim_textures["down"][1].loadFromFile("graphics/player/down/down_1.png");
        anim_textures["down"][2].loadFromFile("graphics/player/down/down_2.png");
        anim_textures["down"][3].loadFromFile("graphics/player/down/down_3.png");
        anim_textures["left"] = vector<Texture>(4);
        anim_textures["left"][0].loadFromFile("graphics/player/left/left_0.png");
        anim_textures["left"][1].loadFromFile("graphics/player/left/left_1.png");
        anim_textures["left"][2].loadFromFile("graphics/player/left/left_2.png");
        anim_textures["left"][3].loadFromFile("graphics/player/left/left_3.png");
        anim_textures["right"] = vector<Texture>(4);
        anim_textures["right"][0].loadFromFile("graphics/player/right/right_0.png");
        anim_textures["right"][1].loadFromFile("graphics/player/right/right_1.png");
        anim_textures["right"][2].loadFromFile("graphics/player/right/right_2.png");
        anim_textures["right"][3].loadFromFile("graphics/player/right/right_3.png");
        anim_textures["right_idle"] = vector<Texture>(1);
        anim_textures["right_idle"][0].loadFromFile("graphics/player/right_idle/idle_right.png");
        anim_textures["left_idle"] = vector<Texture>(1);
        anim_textures["left_idle"][0].loadFromFile("graphics/player/left_idle/idle_left.png");
        anim_textures["up_idle"] = vector<Texture>(1);
        anim_textures["up_idle"][0].loadFromFile("graphics/player/up_idle/idle_up.png");
        anim_textures["down_idle"] = vector<Texture>(1);
        anim_textures["down_idle"][0].loadFromFile("graphics/player/down_idle/idle_down.png");
        anim_textures["right_attack"] = vector<Texture>(1);
        anim_textures["right_attack"][0].loadFromFile("graphics/player/right_attack/attack_right.png");
        anim_textures["left_attack"] = vector<Texture>(1);
        anim_textures["left_attack"][0].loadFromFile("graphics/player/left_attack/attack_left.png");
        anim_textures["up_attack"] = vector<Texture>(1);
        anim_textures["up_attack"][0].loadFromFile("graphics/player/up_attack/attack_up.png");
        anim_textures["down_attack"] = vector<Texture>(1);
        anim_textures["down_attack"][0].loadFromFile("graphics/player/down_attack/attack_down.png");
        weapon_textures["sword"]["up"].loadFromFile("graphics/weapons/sword/up.png");
        weapon_textures["sword"]["full"].loadFromFile("graphics/weapons/sword/full.png");
        weapon_textures["sword"]["left"].loadFromFile("graphics/weapons/sword/left.png");
        weapon_textures["sword"]["right"].loadFromFile("graphics/weapons/sword/right.png");
        weapon_textures["sword"]["down"].loadFromFile("graphics/weapons/sword/down.png");
        weapon_textures["axe"]["up"].loadFromFile("graphics/weapons/axe/up.png");
        weapon_textures["axe"]["full"].loadFromFile("graphics/weapons/axe/full.png");
        weapon_textures["axe"]["left"].loadFromFile("graphics/weapons/axe/left.png");
        weapon_textures["axe"]["right"].loadFromFile("graphics/weapons/axe/right.png");
        weapon_textures["axe"]["down"].loadFromFile("graphics/weapons/axe/down.png");
        weapon_textures["lance"]["up"].loadFromFile("graphics/weapons/lance/up.png");
        weapon_textures["lance"]["full"].loadFromFile("graphics/weapons/lance/full.png");
        weapon_textures["lance"]["left"].loadFromFile("graphics/weapons/lance/left.png");
        weapon_textures["lance"]["right"].loadFromFile("graphics/weapons/lance/right.png");
        weapon_textures["lance"]["down"].loadFromFile("graphics/weapons/lance/down.png");
        weapon_textures["rapier"]["up"].loadFromFile("graphics/weapons/rapier/up.png");
        weapon_textures["rapier"]["full"].loadFromFile("graphics/weapons/rapier/full.png");
        weapon_textures["rapier"]["left"].loadFromFile("graphics/weapons/rapier/left.png");
        weapon_textures["rapier"]["right"].loadFromFile("graphics/weapons/rapier/right.png");
        weapon_textures["rapier"]["down"].loadFromFile("graphics/weapons/rapier/down.png");
        weapon_textures["sai"]["up"].loadFromFile("graphics/weapons/sai/up.png");
        weapon_textures["sai"]["full"].loadFromFile("graphics/weapons/sai/full.png");
        weapon_textures["sai"]["left"].loadFromFile("graphics/weapons/sai/left.png");
        weapon_textures["sai"]["right"].loadFromFile("graphics/weapons/sai/right.png");
        weapon_textures["sai"]["down"].loadFromFile("graphics/weapons/sai/down.png");
        magic_textures = vector<Texture>(2);
        magic_textures[0].loadFromFile(magic_datas[0].texture_path);
        magic_textures[1].loadFromFile(magic_datas[1].texture_path);
    }
    void create_magic(string style, int strength, int cost) {
        cout << style << " " << strength << " " << cost << "\n";
    }
    string get_weapon_name() {
        return weapon_names[weapon_index];
    }
    string get_magic_name() {
        return magic_datas[magic_index].name;
    }
    void input(Clock &clock) {
        if (!attacking) {
            if (Keyboard::isKeyPressed(Keyboard::Up)) {
                direction.y = -1;
                status = "up";
            }
            else if(Keyboard::isKeyPressed(Keyboard::Down)) {
                direction.y = 1;
                status = "down";
            }
            else {
                direction.y = 0;
            }
            if (Keyboard::isKeyPressed(Keyboard::Right)) {
                direction.x = 1;
                status = "right";
            }
            else if(Keyboard::isKeyPressed(Keyboard::Left)) {
                direction.x = -1;
                status = "left";
            }
            else {
                direction.x = 0;
            }
            if (Keyboard::isKeyPressed(Keyboard::Space)) {
                attacking = true;
                attack_time = clock.getElapsedTime();
                this->set_nead_create_attack(true);
                // cout << "attack\n";
            }
            if (Keyboard::isKeyPressed(Keyboard::LControl)) {
                attacking = true;
                attack_time = clock.getElapsedTime();
                string style = magic_datas[magic_index].name;
                int strength = magic_datas[magic_index].strength + stats["magic"];
                int cost = magic_datas[magic_index].cost;
                create_magic(style, strength, cost);
            }
            if (Keyboard::isKeyPressed(Keyboard::Q) && can_switch_weapon) {
                can_switch_weapon = false;
                weapon_switch_time = clock.getElapsedTime();
                weapon_index++;
                weapon_index %= weapon_names.size();
                // cout << weapon_index;
            }
            if (Keyboard::isKeyPressed(Keyboard::E) && can_switch_magic) {
                can_switch_magic = false;
                magic_switch_time = clock.getElapsedTime();
                magic_index++;
                magic_index %= magic_datas.size();
                // cout << weapon_index;
            }
        }
    }
    Texture* get_weapon_texture(string direction) {
        return &weapon_textures[weapon_names[weapon_index]][direction];
    }
    Texture* get_magic_texture() {
        return &magic_textures[magic_index];
    }
    bool get_nead_create_attack() {
        return nead_create_attack;
    }
    void set_nead_create_attack(bool value) {
        nead_create_attack = value;
    }
    bool get_nead_destroy_attack() {
        return nead_destroy_attack;
    }
    void set_nead_destroy_attack(bool value) {
        nead_destroy_attack = value;
    }
    string get_status() {
        if (direction.x == 0 && direction.y == 0) {
            if (!get_contain("idle", status) && !get_contain("attack", status)) {
                status += "_idle";
            }
        }
        if (attacking) {
            direction.x = 0;
            direction.y = 0;
            if (!get_contain("attack", status)) {
                if (get_contain("idle", status)) {
                    status = str_replace(status, "_idle", "_attack");
                }
                else {
                    status += "_attack";
                }
            }
        }
        else {
            if (get_contain("attack", status)) {
                status = str_replace(status, "_attack", "");
            }
        }
        return status;
    }
    void animate() {
        frame_index += animation_speed;
        if (frame_index >= anim_textures[status].size()) {
            frame_index = 0;
        }
        this->setTexture(anim_textures[status][(int)frame_index]);
    }
    void cooldowns(Clock &clock) {
        Time current_time = clock.getElapsedTime();
        if (attacking) {
            if (current_time.asSeconds() - attack_time.asSeconds() >= attack_cooldown) {
                attacking = false;
                nead_destroy_attack = true;
            }
        }
        if (!can_switch_weapon) {
            if (current_time.asSeconds() - weapon_switch_time.asSeconds() >= switch_duration_cooldown) {
                can_switch_weapon = true;
            }
        }
        if (!can_switch_magic) {
            if (current_time.asSeconds() - magic_switch_time.asSeconds() >= switch_duration_cooldown) {
                can_switch_magic = true;
            }
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
    void update(float time, Clock &clock) {
        this->input(clock);
        this->cooldowns(clock);
        this->get_status();
        this->animate();
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
