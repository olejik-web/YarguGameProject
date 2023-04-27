#pragma once;
#pragma once;
#include <Windows.h>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Rect.hpp>
#include "settings.h"
#include "player.h"
#include "tile.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;
using namespace sf;

string toString(int num) {
    string str = "";
    while (num > 0) {
        str += char(num % 10 + '0');
        num /= 10;
    }
    if (str.empty()) str += "0";
    reverse(str.begin(), str.end());
    return str;
}

class UI : public GameObject {
private:
    Font font;
    RectangleShape health_bar_shape;
    RectangleShape energy_bar_shape;
    /* text.setFont(DebugFont);
    text.setCharacterSize(30);
    text.setString(info);
    text.setPosition((float)x, (float)y);*/
public:
    UI() {
        font.loadFromFile(UI_FONT);
        health_bar_shape = RectangleShape(Vector2f(HEALTH_BAR_WIDTH, BAR_HEIGHT));
        energy_bar_shape = RectangleShape(Vector2f(ENERGY_BAR_WIDTH, BAR_HEIGHT));

    };
    void show_bar(RenderWindow &screen, float current, float max_amount,
                  RectangleShape &bar_shape, Color color) {
        float shape_ratio = current / max_amount;
        float current_width = bar_shape.getSize().x * shape_ratio;
        RectangleShape current_shape;
        current_shape.setPosition(bar_shape.getPosition());
        current_shape.setSize(bar_shape.getSize());
        bar_shape.setFillColor(UI_BG_COLOR);
        bar_shape.setOutlineThickness(3);
        bar_shape.setOutlineColor(UI_BORDER_COLOR);
        screen.draw(bar_shape);
        current_shape.setSize(Vector2f(current_width, current_shape.getSize().y));
        current_shape.setFillColor(color);
        screen.draw(current_shape);
    }
    void show_exp(int exp, RenderWindow &screen, Player &player) {
        Text text;
        text.setFont(font);
        text.setCharacterSize(UI_FONT_SIZE);
        text.setOutlineColor(TEXT_COLOR);
        float x = player.getPosition().x + 550;
        float y = player.getPosition().y + 320;
        text.setPosition(x, y);
        text.setString(toString(exp));
        FloatRect bg_rect = text.getGlobalBounds();
        inflate_rect(bg_rect, 20, 20);
        RectangleShape bg_shape(Vector2f(bg_rect.width, bg_rect.height));
        bg_shape.setPosition(bg_rect.left, bg_rect.top);
        bg_shape.setFillColor(UI_BG_COLOR);
        bg_shape.setOutlineColor(UI_BORDER_COLOR);
        bg_shape.setOutlineThickness(3);
        // cout << text.getGlobalBounds().width << " " << text.getGlobalBounds().height << "\n";
        screen.draw(bg_shape);
        screen.draw(text);
    }
    FloatRect selection_box(RenderWindow &screen, Player &player,
                            float delta_x = 0, float delta_y = 0, bool has_switched = false) {
        RectangleShape shape(Vector2f(ITEM_BOX_SIZE, ITEM_BOX_SIZE));
        float x = player.getPosition().x + delta_x;
        float y = player.getPosition().y + delta_y;
        shape.setPosition(x, y);
        shape.setFillColor(UI_BG_COLOR);
        if (has_switched) {
            shape.setOutlineColor(UI_BORDER_COLOR);
        }
        else {
            shape.setOutlineColor(UI_BORDER_COLOR_ACTIVE);
        }
        shape.setOutlineThickness(3);
        screen.draw(shape);
        FloatRect shape_rect(shape.getPosition(), shape.getSize());
        return shape_rect;
    }
    void weapon_overlay(RenderWindow &screen, Player &player,
                        float delta_x = 0, float delta_y = 0) {
        FloatRect weapon_rect = selection_box(screen, player, delta_x,
                                              delta_y, player.get_can_switch_weapon());
        Sprite weapon_sprite;
        Texture* weapon_texture = player.get_weapon_texture("up");
        weapon_sprite.setTexture(*weapon_texture);
        if (player.get_weapon_name() == "sword") {
            weapon_sprite.setScale(1.5, 1.5);
            weapon_sprite.setPosition(weapon_rect.left + 20, weapon_rect.top + 5);
        }
        else if (player.get_weapon_name() == "axe") {
            weapon_sprite.setScale(1.6, 1.6);
            weapon_sprite.setPosition(weapon_rect.left + 5, weapon_rect.top + 15);
        }
        else if (player.get_weapon_name() == "lance") {
            weapon_sprite.setScale(1.1, 1.1);
            weapon_sprite.setPosition(weapon_rect.left + 28, weapon_rect.top + 3);
        }
        else if (player.get_weapon_name() == "rapier") {
            weapon_sprite.setScale(1.5, 1.5);
            weapon_sprite.setPosition(weapon_rect.left + 10, weapon_rect.top + 5);
        }
        else if (player.get_weapon_name() == "sai") {
            weapon_sprite.setScale(1.5, 1.5);
            weapon_sprite.setPosition(weapon_rect.left + 19, weapon_rect.top + 15);
        }
        screen.draw(weapon_sprite);
    }
    void magic_overlay(RenderWindow &screen, Player &player,
                        float delta_x = 0, float delta_y = 0) {
        FloatRect magic_rect = selection_box(screen, player, delta_x,
                                             delta_y, player.get_can_switch_magic());
        Sprite magic_sprite;
        Texture* magic_texture = player.get_magic_texture();
        if (player.get_magic_name() == "flame") {
            magic_sprite.setScale(1.2, 1.2);
            magic_sprite.setPosition(magic_rect.left, magic_rect.top);
        }
        else if (player.get_magic_name() == "heal") {
            magic_sprite.setScale(1.2, 1.2);
            magic_sprite.setPosition(magic_rect.left, magic_rect.top);
        }
        magic_sprite.setTexture(*magic_texture);
        screen.draw(magic_sprite);
    }
    void display(Player &player, RenderWindow &screen) {
        health_bar_shape.setPosition(Vector2f(player.getPosition().x - 570,
                                             player.getPosition().y - 300));
        energy_bar_shape.setPosition(Vector2f(player.getPosition().x - 570,
                                             player.getPosition().y - 266));
        this->show_bar(screen, player.get_health(), player.get_max_health(),
                       health_bar_shape, HEALTH_COLOR);
        this->show_bar(screen, player.get_energy(), player.get_max_energy(),
                       energy_bar_shape, ENERGY_COLOR);
        this->show_exp(player.get_exp(), screen, player);
        this->weapon_overlay(screen, player, -520, 280);
        this->magic_overlay(screen, player, -400, 280);
    }
};
