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
#include "enemy.h"
#include "debug.h"
#include "weapon.h"
#include "ui.h"
#include <iomanip>
#include <memory>
#include <fstream>

using namespace std;
using namespace sf;

Texture ROCK_TEXTURE;
Texture PLAYER_TEXTURE;
Texture GROUND_TEXTURE;
vector<Texture> GRASS_TEXTURES(3);
vector<Texture> OBJECT_TEXTURES(21);
map<string, map<string, vector<Texture>> > ENEMY_ANIM_TEXTURES;

vector< vector<int> > load_map_from_file(string path) {
    vector< vector<int> >loaded_map(0, vector<int>(0));
    ifstream in(path);
    string line;
    while (getline(in, line)) {
        vector<int>v(0);
        string str_num="";
        for (auto c : line) {
            if (c == ',') {
                int num = 0;
                bool have_minus = false;
                for (auto t : str_num) {
                    if (t == '-') {
                        have_minus = true;
                    }
                    else {
                        num *= 10;
                        num += (t - '0');
                    }
                }
                if (have_minus) num *= -1;
                // cout << num << " " << str_num << "\n";
                v.push_back(num);
                str_num = "";
            }
            else {
                str_num += c;
            }
        }
        loaded_map.push_back(v);
    }
    return loaded_map;
}

/* class Camera {
private:
    Vector2f offset;
    bool stop;
    int half_width;
    int half_height;
public:
    Camera() {
        offset = Vector2f(0, 0);
        stop = false;
    }
    void custom_draw(Tile &tile, RenderWindow &display, Player &player) {
        FloatRect player_rect = player.getGlobalBounds();
        offset.x = player_rect.left + player_rect.width / 2;
        offset.y = player_rect.top + player_rect.height / 2;
        FloatRect tile_rect = tile.getGlobalBounds();
        float start_tile_x = tile.get_started_pos().first;
        float start_tile_y = tile.get_started_pos().second;
        tile.setPosition(Vector2f(start_tile_x + half_width, start_tile_y + half_height) - offset);
        display.draw(tile);
        // stop = true;
    }
    void set_stop(bool value) {
        stop = value;
    }
    bool get_stop() {
        return stop;
    }
    void set_screen_size(RenderWindow &screen) {
        Vector2u screen_size = screen.getSize();
        half_width = screen_size.x / 2;
        half_height = screen_size.y / 2;
    }
};*/

Texture main_texture;

class Level {
private:
    vector<Tile>level_tiles;
    vector<Tile>obstacle_tiles;
    Player player;
    Entity enemy;
    Sprite Ground;
    vector< vector<int> >BoundaryMap;
    vector< vector<int> >GrassMap;
    vector< vector<int> >ObjectsMap;
    vector< vector<int> >EntitiesMap;
    View camera;
    Clock clock;
    vector<Weapon>weapons;
    vector<Enemy>enemys;
    UI ui;
    bool a = false;
public:
    Level() {
        level_tiles = vector<Tile>(0);
        camera.zoom(2.5f);
        this->create_map();
        clock.restart();
    }
    void create_attack() {
        Weapon weapon(player);
        weapon.set_visibility(true);
        weapons.push_back(weapon);
    }
    void destroy_attack() {
        vector<Weapon>tmp_vector;
        for (int i=1; i<weapons.size(); i++) {
            tmp_vector.push_back(weapons[i]);
        }
        weapons = tmp_vector;
    }
    void load_textures() {
        ROCK_TEXTURE.loadFromFile("rock.png");
        PLAYER_TEXTURE.loadFromFile("player.png");
        GROUND_TEXTURE.loadFromFile("graphics/tilemap/ground.png");
        GRASS_TEXTURES[0].loadFromFile("graphics/grass/grass_1.png");
        GRASS_TEXTURES[1].loadFromFile("graphics/grass/grass_2.png");
        GRASS_TEXTURES[2].loadFromFile("graphics/grass/grass_3.png");
        OBJECT_TEXTURES[0].loadFromFile("graphics/objects/0.png");
        OBJECT_TEXTURES[1].loadFromFile("graphics/objects/01.png");
        OBJECT_TEXTURES[2].loadFromFile("graphics/objects/02.png");
        OBJECT_TEXTURES[3].loadFromFile("graphics/objects/03.png");
        OBJECT_TEXTURES[4].loadFromFile("graphics/objects/04.png");
        OBJECT_TEXTURES[5].loadFromFile("graphics/objects/05.png");
        OBJECT_TEXTURES[6].loadFromFile("graphics/objects/06.png");
        OBJECT_TEXTURES[7].loadFromFile("graphics/objects/07.png");
        OBJECT_TEXTURES[8].loadFromFile("graphics/objects/08.png");
        OBJECT_TEXTURES[9].loadFromFile("graphics/objects/09.png");
        OBJECT_TEXTURES[10].loadFromFile("graphics/objects/10.png");
        OBJECT_TEXTURES[11].loadFromFile("graphics/objects/11.png");
        OBJECT_TEXTURES[12].loadFromFile("graphics/objects/12.png");
        OBJECT_TEXTURES[13].loadFromFile("graphics/objects/13.png");
        OBJECT_TEXTURES[14].loadFromFile("graphics/objects/14.png");
        OBJECT_TEXTURES[15].loadFromFile("graphics/objects/15.png");
        OBJECT_TEXTURES[16].loadFromFile("graphics/objects/16.png");
        OBJECT_TEXTURES[17].loadFromFile("graphics/objects/17.png");
        OBJECT_TEXTURES[18].loadFromFile("graphics/objects/18.png");
        OBJECT_TEXTURES[19].loadFromFile("graphics/objects/19.png");
        OBJECT_TEXTURES[20].loadFromFile("graphics/objects/20.png");
        ENEMY_ANIM_TEXTURES["bamboo"]["idle"] = vector<Texture>(4);
        ENEMY_ANIM_TEXTURES["bamboo"]["idle"][0].loadFromFile("graphics/monsters/bamboo/idle/0.png");
        ENEMY_ANIM_TEXTURES["bamboo"]["idle"][1].loadFromFile("graphics/monsters/bamboo/idle/1.png");
        ENEMY_ANIM_TEXTURES["bamboo"]["idle"][2].loadFromFile("graphics/monsters/bamboo/idle/2.png");
        ENEMY_ANIM_TEXTURES["bamboo"]["idle"][3].loadFromFile("graphics/monsters/bamboo/idle/3.png");
        ENEMY_ANIM_TEXTURES["bamboo"]["move"] = vector<Texture>(4);
        ENEMY_ANIM_TEXTURES["bamboo"]["move"][0].loadFromFile("graphics/monsters/bamboo/move/0.png");
        ENEMY_ANIM_TEXTURES["bamboo"]["move"][1].loadFromFile("graphics/monsters/bamboo/move/1.png");
        ENEMY_ANIM_TEXTURES["bamboo"]["move"][2].loadFromFile("graphics/monsters/bamboo/move/2.png");
        ENEMY_ANIM_TEXTURES["bamboo"]["move"][3].loadFromFile("graphics/monsters/bamboo/move/3.png");
        ENEMY_ANIM_TEXTURES["bamboo"]["attack"] = vector<Texture>(1);
        ENEMY_ANIM_TEXTURES["bamboo"]["attack"][0].loadFromFile("graphics/monsters/bamboo/attack/0.png");
        ENEMY_ANIM_TEXTURES["raccoon"]["idle"] = vector<Texture>(6);
        ENEMY_ANIM_TEXTURES["raccoon"]["idle"][0].loadFromFile("graphics/monsters/raccoon/idle/0.png");
        ENEMY_ANIM_TEXTURES["raccoon"]["idle"][1].loadFromFile("graphics/monsters/raccoon/idle/1.png");
        ENEMY_ANIM_TEXTURES["raccoon"]["idle"][2].loadFromFile("graphics/monsters/raccoon/idle/2.png");
        ENEMY_ANIM_TEXTURES["raccoon"]["idle"][3].loadFromFile("graphics/monsters/raccoon/idle/3.png");
        ENEMY_ANIM_TEXTURES["raccoon"]["idle"][4].loadFromFile("graphics/monsters/raccoon/idle/4.png");
        ENEMY_ANIM_TEXTURES["raccoon"]["idle"][5].loadFromFile("graphics/monsters/raccoon/idle/5.png");
        ENEMY_ANIM_TEXTURES["raccoon"]["move"] = vector<Texture>(5);
        ENEMY_ANIM_TEXTURES["raccoon"]["move"][0].loadFromFile("graphics/monsters/raccoon/move/0.png");
        ENEMY_ANIM_TEXTURES["raccoon"]["move"][1].loadFromFile("graphics/monsters/raccoon/move/1.png");
        ENEMY_ANIM_TEXTURES["raccoon"]["move"][2].loadFromFile("graphics/monsters/raccoon/move/2.png");
        ENEMY_ANIM_TEXTURES["raccoon"]["move"][3].loadFromFile("graphics/monsters/raccoon/move/3.png");
        ENEMY_ANIM_TEXTURES["raccoon"]["move"][4].loadFromFile("graphics/monsters/raccoon/move/4.png");
        ENEMY_ANIM_TEXTURES["raccoon"]["attack"] = vector<Texture>(4);
        ENEMY_ANIM_TEXTURES["raccoon"]["attack"][0].loadFromFile("graphics/monsters/raccoon/attack/0.png");
        ENEMY_ANIM_TEXTURES["raccoon"]["attack"][1].loadFromFile("graphics/monsters/raccoon/attack/1.png");
        ENEMY_ANIM_TEXTURES["raccoon"]["attack"][2].loadFromFile("graphics/monsters/raccoon/attack/2.png");
        ENEMY_ANIM_TEXTURES["raccoon"]["attack"][3].loadFromFile("graphics/monsters/raccoon/attack/3.png");
        ENEMY_ANIM_TEXTURES["spirit"]["idle"] = vector<Texture>(4);
        ENEMY_ANIM_TEXTURES["spirit"]["idle"][0].loadFromFile("graphics/monsters/spirit/idle/0.png");
        ENEMY_ANIM_TEXTURES["spirit"]["idle"][1].loadFromFile("graphics/monsters/spirit/idle/1.png");
        ENEMY_ANIM_TEXTURES["spirit"]["idle"][2].loadFromFile("graphics/monsters/spirit/idle/2.png");
        ENEMY_ANIM_TEXTURES["spirit"]["idle"][3].loadFromFile("graphics/monsters/spirit/idle/3.png");
        ENEMY_ANIM_TEXTURES["spirit"]["move"] = vector<Texture>(4);
        ENEMY_ANIM_TEXTURES["spirit"]["move"][0].loadFromFile("graphics/monsters/spirit/move/0.png");
        ENEMY_ANIM_TEXTURES["spirit"]["move"][1].loadFromFile("graphics/monsters/spirit/move/1.png");
        ENEMY_ANIM_TEXTURES["spirit"]["move"][2].loadFromFile("graphics/monsters/spirit/move/2.png");
        ENEMY_ANIM_TEXTURES["spirit"]["move"][3].loadFromFile("graphics/monsters/spirit/move/3.png");
        ENEMY_ANIM_TEXTURES["spirit"]["attack"] = vector<Texture>(1);
        ENEMY_ANIM_TEXTURES["spirit"]["attack"][0].loadFromFile("graphics/monsters/spirit/attack/0.png");
        ENEMY_ANIM_TEXTURES["squid"]["idle"] = vector<Texture>(5);
        ENEMY_ANIM_TEXTURES["squid"]["idle"][0].loadFromFile("graphics/monsters/squid/idle/0.png");
        ENEMY_ANIM_TEXTURES["squid"]["idle"][1].loadFromFile("graphics/monsters/squid/idle/1.png");
        ENEMY_ANIM_TEXTURES["squid"]["idle"][2].loadFromFile("graphics/monsters/squid/idle/2.png");
        ENEMY_ANIM_TEXTURES["squid"]["idle"][3].loadFromFile("graphics/monsters/squid/idle/3.png");
        ENEMY_ANIM_TEXTURES["squid"]["idle"][4].loadFromFile("graphics/monsters/squid/idle/4.png");
        ENEMY_ANIM_TEXTURES["squid"]["move"] = vector<Texture>(4);
        ENEMY_ANIM_TEXTURES["squid"]["move"][0].loadFromFile("graphics/monsters/squid/move/0.png");
        ENEMY_ANIM_TEXTURES["squid"]["move"][1].loadFromFile("graphics/monsters/squid/move/1.png");
        ENEMY_ANIM_TEXTURES["squid"]["move"][2].loadFromFile("graphics/monsters/squid/move/2.png");
        ENEMY_ANIM_TEXTURES["squid"]["move"][3].loadFromFile("graphics/monsters/squid/move/3.png");
        ENEMY_ANIM_TEXTURES["squid"]["attack"] = vector<Texture>(1);
        ENEMY_ANIM_TEXTURES["squid"]["attack"][0].loadFromFile("graphics/monsters/squid/attack/0.png");
    }
    void create_map() {
        load_textures();
        Ground.setTexture(GROUND_TEXTURE);
        Ground.setPosition(Vector2f(0, 0));
        BoundaryMap = load_map_from_file("map/map_FloorBlocks.csv");
        GrassMap = load_map_from_file("map/map_Grass.csv");
        ObjectsMap = load_map_from_file("map/map_Objects.csv");
        EntitiesMap = load_map_from_file("map/map_Entities.csv");
        int x, y;
        for (int i=0; i<BoundaryMap.size(); i++) {
            for (int j=0; j<BoundaryMap[i].size(); j++) {
                x = j * TILESIZE;
                y = i * TILESIZE;
                if (BoundaryMap[i][j] != -1) {
                    Tile tile;
                    tile.set_name("boundary-block");
                    tile.set_pos({x, y});
                    tile.set_visibility(false);
                    tile.setTexture(ROCK_TEXTURE);
                    FloatRect hitbox = tile.getGlobalBounds();
                    inflate_rect(hitbox, -2, -10);
                    tile.set_hitbox(hitbox);
                    level_tiles.push_back(tile);
                    obstacle_tiles.push_back(tile);
                }
            }
        }
        for (int i=0; i<GrassMap.size(); i++) {
            for (int j=0; j<GrassMap[i].size(); j++) {
                x = j * TILESIZE;
                y = i * TILESIZE;
                if (GrassMap[i][j] != -1) {
                    Tile tile;
                    tile.set_name("grass");
                    tile.set_pos({x, y});
                    tile.set_visibility(true);
                    tile.setTexture(GRASS_TEXTURES[rand() % 3]);
                    FloatRect hitbox = tile.getGlobalBounds();
                    inflate_rect(hitbox, -2, -10);
                    tile.set_hitbox(hitbox);
                    level_tiles.push_back(tile);
                    obstacle_tiles.push_back(tile);
                }
            }
        }
        for (int i=0; i<ObjectsMap.size(); i++) {
            for (int j=0; j<ObjectsMap[i].size(); j++) {
                x = j * TILESIZE;
                y = i * TILESIZE;
                if (ObjectsMap[i][j] != -1) {
                    Tile tile;
                    tile.set_name("object");
                    tile.set_pos({x, y});
                    tile.set_visibility(true);
                    tile.setTexture(OBJECT_TEXTURES[ObjectsMap[i][j]]);
                    FloatRect hitbox = tile.getGlobalBounds();
                    inflate_rect(hitbox, -2, -10);
                    tile.set_hitbox(hitbox);
                    level_tiles.push_back(tile);
                    obstacle_tiles.push_back(tile);
                }
            }
        }
        for (int i=0; i<EntitiesMap.size(); i++) {
            for (int j=0; j<EntitiesMap[i].size(); j++) {
                x = j * TILESIZE;
                y = i * TILESIZE;
                if (EntitiesMap[i][j] == 394) {
                    Player obj;
                    obj.set_name("player");
                    obj.set_pos({x, y});
                    obj.setTexture(PLAYER_TEXTURE);
                    obj.set_visibility(true);
                    FloatRect hitbox = obj.getGlobalBounds();
                    inflate_rect(hitbox, 0, -26);
                    obj.set_hitbox(hitbox);
                    player = obj;
                }
                else if (EntitiesMap[i][j] != -1) {
                    Enemy tmp_obj;
                    string monster_name;
                    if (EntitiesMap[i][j] == 390) {
                        monster_name = "bamboo";
                    }
                    else if (EntitiesMap[i][j] == 391) {
                        monster_name = "spirit";
                    }
                    else if (EntitiesMap[i][j] == 392) {
                        monster_name = "raccoon";
                    }
                    else {
                        monster_name = "squid";
                    }
                    tmp_obj.set_name(monster_name);
                    tmp_obj.set_sprite_type(monster_name);
                    tmp_obj.set_pos({x, y});
                    tmp_obj.setTexture(ENEMY_ANIM_TEXTURES[tmp_obj.get_sprite_type()]["idle"][0]);
                    tmp_obj.set_visibility(true);
                    FloatRect hitbox = tmp_obj.getGlobalBounds();
                    if (monster_name != "raccoon") {
                        inflate_rect(hitbox, 0, -10);
                    }
                    else {
                        inflate_rect(hitbox, 0, -60);
                        hitbox.top -= 30;
                    }
                    tmp_obj.set_hitbox(hitbox);
                    enemys.push_back(tmp_obj);
                }
            }
        }
        // player.setPosition(Vector2f(2000, 1500));
    }
    void run(RenderWindow &screen, float time, Clock &clock) {
        // camera.set_screen_size(screen);
        screen.draw(Ground);
        for (int i=0; i<obstacle_tiles.size(); i++) {
            if (obstacle_tiles[i].isVisible() &&
                obstacle_tiles[i].get_hitbox().top <= player.get_hitbox().top) {
                screen.draw(obstacle_tiles[i]);
            }
        }
        vector<Enemy>before_player;
        vector<Enemy>after_player;
        for (auto enemy : enemys) {
            if (enemy.get_sprite_type() != "raccoon" && enemy.isVisible() &&
                enemy.get_hitbox().top <= player.get_hitbox().top) {
                screen.draw(enemy);
            }
            float player_center_y = player.get_hitbox().top + player.get_hitbox().height / 2;
            float player_center_x = player.get_hitbox().left + player.get_hitbox().width / 2;
            if (enemy.get_sprite_type() == "raccoon" && enemy.isVisible()
                 && (enemy.get_hitbox().top > player_center_y
                     || enemy.get_hitbox().top + enemy.get_hitbox().height < player_center_y)) {
                        screen.draw(enemy);
            }
            // screen.draw(shape);
        }
        if (player.isVisible()) {
            screen.draw(player);
        }
        for (auto weapon : weapons) {
            screen.draw(weapon);
            // weapon.draw_shape(screen);
        }
        for (auto enemy : enemys) {
            if (enemy.isVisible() &&
                enemy.get_hitbox().top > player.get_hitbox().top) {
                screen.draw(enemy);
            }
            float player_center_y = player.get_hitbox().top + player.get_hitbox().height / 2;
            float player_center_x = player.get_hitbox().left + player.get_hitbox().width / 2;
            if (enemy.get_sprite_type() == "raccoon" && enemy.isVisible()
                 && enemy.get_hitbox().top <= player_center_y
                     && enemy.get_hitbox().top + enemy.get_hitbox().height >= player_center_y) {
                        screen.draw(enemy);
            }
            // screen.draw(shape);
        }
        for (int i=0; i<obstacle_tiles.size(); i++) {
            if (obstacle_tiles[i].isVisible() &&
                obstacle_tiles[i].get_hitbox().top > player.get_hitbox().top) {
                screen.draw(obstacle_tiles[i]);
            }
            FloatRect tile_box = obstacle_tiles[i].getGlobalBounds();
            RectangleShape rect;
            rect.setSize(Vector2f(tile_box.width, tile_box.height));
            rect.setPosition(Vector2f(tile_box.left, tile_box.top));
            rect.setFillColor(Color::White);
            // screen.draw(rect);
            tile_box = obstacle_tiles[i].get_hitbox();
            rect.setSize(Vector2f(tile_box.width, tile_box.height));
            rect.setPosition(Vector2f(tile_box.left, tile_box.top));
            rect.setFillColor(Color::Blue);
            // screen.draw(rect);
        }
        player.set_obstacle_tiles(obstacle_tiles);
        for (int i=0; i<enemys.size(); i++) {
            enemys[i].set_obstacle_tiles(obstacle_tiles);
        }
        // camera.set_stop(true);
        // player.cout_hitbox();
        // player.cout_rect();
        player.update(time, clock);
        if (player.get_nead_create_attack()) {
            this->create_attack();
            player.set_nead_create_attack(false);
        }
        if (player.get_nead_destroy_attack()) {
            this->destroy_attack();
            player.set_nead_destroy_attack(false);
        }
        FloatRect player_rect = player.getGlobalBounds();
        float center_x = player_rect.left + player_rect.width / 2;
        float center_y = player_rect.top + player_rect.height / 2;
        camera = screen.getView();
        camera.setCenter(Vector2f(center_x, center_y));
        screen.setView(camera);
        FloatRect player_box = player.getGlobalBounds();
        RectangleShape rect;
        rect.setSize(Vector2f(player_box.width, player_box.height));
        rect.setPosition(Vector2f(player_box.left, player_box.top));
        rect.setFillColor(Color::White);
        for (int i=0; i<enemys.size(); i++) {
            enemys[i].update(player);
        }
        // screen.draw(rect);
        /* FloatRect enemy_box = enemy.get_hitbox();
        rect.setSize(Vector2f(enemy_box.width, enemy_box.height));
        rect.setPosition(Vector2f(enemy_box.left, enemy_box.top));
        rect.setFillColor(Color::Red);*/
        ui.display(player, screen);
    }
};
