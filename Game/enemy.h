#pragma once;
#include <math.h>
#include <Windows.h>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Rect.hpp>
#include "settings.h"
#include "entity.h"
#include "player.h"
#include <iostream>
#include <vector>
#include <string>

struct MonsterData {
    string name;
    float health;
    int exp;
    float damage;
    string attack_type;
    string attack_sound_path;
    float speed;
    float resistance;
    float attack_radius;
    float notice_radius;
};

class Enemy : public Entity {
private:
    string sprite_type = "enemy";
    string status = "idle";
    map<string, MonsterData>monsters;
    MonsterData data;
    float time_K = 1;
public:
    Enemy() {
        monsters["squid"].name = "squid";
        monsters["squid"].health = 100;
        monsters["squid"].exp = 100;
        monsters["squid"].damage = 20;
        monsters["squid"].attack_type = "slash";
        monsters["squid"].attack_sound_path = "audio/attack/slash.wav";
        monsters["squid"].speed = 3;
        monsters["squid"].resistance = 3;
        monsters["squid"].attack_radius = 80;
        monsters["squid"].notice_radius = 360;
        monsters["raccoon"].name = "raccoon";
        monsters["raccoon"].health = 300;
        monsters["raccoon"].exp = 250;
        monsters["raccoon"].damage = 40;
        monsters["raccoon"].attack_type = "claw";
        monsters["raccoon"].attack_sound_path = "audio/attack/claw.wav";
        monsters["raccoon"].speed = 2;
        monsters["raccoon"].resistance = 3;
        monsters["raccoon"].attack_radius = 120;
        monsters["raccoon"].notice_radius = 400;
        monsters["spirit"].name = "spirit";
        monsters["spirit"].health = 100;
        monsters["spirit"].exp = 110;
        monsters["spirit"].damage = 8;
        monsters["spirit"].attack_type = "thunder";
        monsters["spirit"].attack_sound_path = "audio/attack/fireball.wav";
        monsters["spirit"].speed = 4;
        monsters["spirit"].resistance = 3;
        monsters["spirit"].attack_radius = 60;
        monsters["spirit"].notice_radius = 350;
        monsters["bamboo"].name = "bamboo";
        monsters["bamboo"].health = 70;
        monsters["bamboo"].exp = 120;
        monsters["bamboo"].damage = 6;
        monsters["bamboo"].attack_type = "leaf_attack";
        monsters["bamboo"].attack_sound_path = "audio/attack/slash.wav";
        monsters["bamboo"].speed = 3;
        monsters["bamboo"].resistance = 3;
        monsters["bamboo"].attack_radius = 50;
        monsters["bamboo"].notice_radius = 300;
    }
    string get_sprite_type() {
        return sprite_type;
    }
    void set_sprite_type(string value) {
        sprite_type = value;
        data = monsters[sprite_type];
    }
    /* void set_draw_order(int value) {
        draw_order = value;
    }
    int get_draw_order() {
        return draw_order;
    }*/

    pair<float, Vector2f> get_player_distance_direction(Player &player) {
        // cout << data.name << "\n";
        float enemy_vec_x = this->getPosition().x + this->getGlobalBounds().width / 2;
        float enemy_vec_y = this->getPosition().y + this->getGlobalBounds().height / 2;
        Vector2f enemy_vec(enemy_vec_x, enemy_vec_y);
        float player_vec_x = player.getPosition().x + player.getGlobalBounds().width / 2;
        float player_vec_y = player.getPosition().y + player.getGlobalBounds().height / 2;
        Vector2f player_vec(player_vec_x, player_vec_y);
        Vector2f distance_vec = (player_vec - enemy_vec);
        float distance = sqrt(distance_vec.x * distance_vec.x + distance_vec.y * distance_vec.y);
        Vector2f direction = distance_vec;
        if (distance > 1) {
            direction.x /= distance;
            direction.y /= distance;
            this->set_direction(direction);
        }
        else {
            this->set_direction(Vector2f(0, 0));
        }
        return {distance, direction};
    }
    string get_status(Player &player) {
        float distance = this->get_player_distance_direction(player).first;
        if (distance <= data.attack_radius) {
            status = "attack";
        }
        else if (distance <= data.notice_radius) {
            status = "move";
        }
        else {
            status = "idle";
        }
    }
    void actions(Player &player) {
        if (status == "attack") {
            // cout << "attack\n";
        }
        else if (status == "move") {
            // cout << "ok\n";
            this->set_direction(get_player_distance_direction(player).second);
        }
        else {
            this->set_direction(Vector2f(0, 0));
        }
    }
    void update(Player &player) {
        this->get_status(player);
        this->actions(player);
        this->move(data.speed);
    }
};
