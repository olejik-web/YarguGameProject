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

class Level {
private:
    vector<Tile>level_tiles;
    vector<Tile>obstacle_tiles;
    Player player;
    Sprite Ground;
    vector< vector<int> >BoundaryMap;
    vector< vector<int> >GrassMap;
    vector< vector<int> >ObjectsMap;
    View camera;
    Clock clock;
    vector<Weapon>weapons;
    UI ui;
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
    }
    void create_map() {
        load_textures();
        Ground.setTexture(GROUND_TEXTURE);
        Ground.setPosition(Vector2f(0, 0));
        BoundaryMap = load_map_from_file("map/map_FloorBlocks.csv");
        GrassMap = load_map_from_file("map/map_Grass.csv");
        ObjectsMap = load_map_from_file("map/map_Objects.csv");
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
        Player obj;
        obj.set_name("player");
        obj.set_pos({2000, 1500});
        obj.setTexture(PLAYER_TEXTURE);
        obj.set_visibility(true);
        FloatRect hitbox = obj.getGlobalBounds();
        inflate_rect(hitbox, 0, -26);
        obj.set_hitbox(hitbox);
        player = obj;
        // player.setPosition(Vector2f(2000, 1500));
    }
    void run(RenderWindow &screen, float time) {
        // camera.set_screen_size(screen);
        screen.draw(Ground);
        for (int i=0; i<obstacle_tiles.size(); i++) {
            if (obstacle_tiles[i].isVisible() &&
                obstacle_tiles[i].get_hitbox().top <= player.get_hitbox().top) {
                screen.draw(obstacle_tiles[i]);
            }
        }
        if (player.isVisible()) {
            screen.draw(player);
        }
        for (auto weapon : weapons) {
            screen.draw(weapon);
            // weapon.draw_shape(screen);
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
        // screen.draw(rect);
        player_box = player.get_hitbox();
        rect.setSize(Vector2f(player_box.width, player_box.height));
        rect.setPosition(Vector2f(player_box.left, player_box.top));
        rect.setFillColor(Color::Red);
        ui.display(player, screen);
        // player.setTexture(PLAYER_ANIM_TEXTURES["up_attack"][0]);
        // player.get_status();
        // player.cooldowns(clock);
        // screen.draw(debug())
    }
};
