#pragma once;
#include <Windows.h>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Rect.hpp>
#include "settings.h"
#include "player.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;
using namespace sf;

vector<string> split(string sep, string str) {
    vector<string>sep_str(1, "");
    int i = 0;
    while(i<=str.size() - sep.size()) {
        int cnt = 0;
        for (int j=i; j<i + sep.size(); j++) {
            if (sep[j - i] == str[j]) {
                cnt++;
            }
        }
        if (cnt == sep.size()) {
            sep_str.push_back("");
            i += sep.size();
        }
        else {
            sep_str.back() += str[i];
            i++;
        }
    }
    if (sep_str.back().empty()) {
        sep_str.pop_back();
    }
    return sep_str;
}

class Weapon : public GameObject {
private:
    Texture texture;
    WeaponData data;
    FloatRect weapon_rect;
    // vector<string>direction;
public:
    Weapon(Player &player) {
        FloatRect player_rect = player.getGlobalBounds();
        string direction = split("_", player.get_status())[0];
        Texture* a = player.get_weapon_texture(direction);
        this->setTexture(*a);
        weapon_rect = this->getGlobalBounds();
        string weapon_name = player.get_weapon_name();
        if (direction == "right") {
            if (weapon_name == "sword") {
                weapon_rect.left = player_rect.left + player_rect.width;
                weapon_rect.top = player_rect.top + 35;
            }
            if (weapon_name == "axe") {
                weapon_rect.left = player_rect.left + player_rect.width;
                weapon_rect.top = player_rect.top + 26;
            }
            if (weapon_name == "lance") {
                weapon_rect.left = player_rect.left + player_rect.width;
                weapon_rect.top = player_rect.top + 35;
            }
            if (weapon_name == "rapier") {
                weapon_rect.left = player_rect.left + player_rect.width;
                weapon_rect.top = player_rect.top + 25;
            }
            if (weapon_name == "sai") {
                weapon_rect.left = player_rect.left + player_rect.width;
                weapon_rect.top = player_rect.top + 35;
            }
        }
        else if (direction == "left") {
            if (weapon_name == "sword") {
                weapon_rect.left = player_rect.left - weapon_rect.width;
                weapon_rect.top = player_rect.top + 35;
            }
            if (weapon_name == "axe") {
                weapon_rect.left = player_rect.left - weapon_rect.width;
                weapon_rect.top = player_rect.top + 26;
            }
            if (weapon_name == "lance") {
                weapon_rect.left = player_rect.left - weapon_rect.width;
                weapon_rect.top = player_rect.top + 35;
            }
            if (weapon_name == "rapier") {
                weapon_rect.left = player_rect.left - weapon_rect.width;
                weapon_rect.top = player_rect.top + 25;
            }
            if (weapon_name == "sai") {
                weapon_rect.left = player_rect.left - weapon_rect.width;
                weapon_rect.top = player_rect.top + 35;
            }
        }
        else if (direction == "up") {
            if (weapon_name == "sword") {
                weapon_rect.left = player_rect.left + 7;
                weapon_rect.top = player_rect.top - weapon_rect.height;
            }
            if (weapon_name == "axe") {
                weapon_rect.left = player_rect.left - 2;
                weapon_rect.top = player_rect.top - weapon_rect.height;;
            }
            if (weapon_name == "lance") {
                weapon_rect.left = player_rect.left + 10;
                weapon_rect.top = player_rect.top - weapon_rect.height;;
            }
            if (weapon_name == "rapier") {
                weapon_rect.left = player_rect.left - 3;
                weapon_rect.top = player_rect.top - weapon_rect.height;;
            }
            if (weapon_name == "sai") {
                weapon_rect.left = player_rect.left + 6;
                weapon_rect.top = player_rect.top - weapon_rect.height;;
            }
        }
        else {
            if (weapon_name == "sword") {
                weapon_rect.left = player_rect.left + 13;
                weapon_rect.top = player_rect.top + player_rect.height;
            }
            if (weapon_name == "axe") {
                weapon_rect.left = player_rect.left + 3;
                weapon_rect.top = player_rect.top + player_rect.height;;
            }
            if (weapon_name == "lance") {
                weapon_rect.left = player_rect.left + 15;
                weapon_rect.top = player_rect.top + player_rect.height;;
            }
            if (weapon_name == "rapier") {
                weapon_rect.left = player_rect.left + 2;
                weapon_rect.top = player_rect.top + player_rect.height;;
            }
            if (weapon_name == "sai") {
                weapon_rect.left = player_rect.left + 11;
                weapon_rect.top = player_rect.top + player_rect.height;;
            }
        }
        this->setPosition(Vector2f(weapon_rect.left, weapon_rect.top));
        // cout << direction << "\n";
    }
    void set_data(WeaponData value) {
        data = value;
    }
    void draw_shape(RenderWindow &screen) {
        RectangleShape shape;
        shape.setSize(Vector2f(weapon_rect.width, weapon_rect.height));
        shape.setPosition(Vector2f(weapon_rect.left, weapon_rect.top));
        shape.setFillColor(Color::Black);
        screen.draw(shape);
        // cout << weapon_rect.left << " " << weapon_rect.top << "\n";
    }
};
