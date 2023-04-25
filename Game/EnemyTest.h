#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h";

using namespace std;
using namespace sf;


class Enemy {
private:
    float x, y;
    float w, h;

public:
    Sprite sprite;
    string File;
    Image image;
    Texture texture;

    pair<int, int> CurrentTile;
    int Health = 5;

    Enemy(string F, float X, float Y, float W, float H)
    {
        File = F;
        w = W; h = H;
        image.loadFromFile(File);
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        x = X; y = Y;
        sprite.setTextureRect(IntRect(w, h, w, h));
        sprite.setPosition(x, y);
    }
};


class Ghost : public Enemy {
public:
    float dx, dy, speed = 0.2;
    int dir = 0;
    float CurrentFrame = 0;

    Ghost(string F, float X, float Y, float W, float H):Enemy(F,X,Y,W,H){}

    void teleport(vector<vector<char> > TileMap) {
        //Временно
        int Tx = (rand() % WIDTH_MAP);
        int Ty = (rand() % HEIGHT_MAP);
        while (TileMap[Ty][Tx] == '0') {
            Tx = (rand() % WIDTH_MAP);
            Ty = (rand() % HEIGHT_MAP);
        }
        sprite.setPosition(Tx * TILE_SIZE, Ty * TILE_SIZE);
    }

    void move(float time, Player& player) {
        dx = player.sprite.getPosition().x - sprite.getPosition().x;
        dy = player.sprite.getPosition().y - sprite.getPosition().y;
        float dlina = sqrt(dx * dx + dy * dy);
        dx /= dlina;
        dy /= dlina;
        if (dx != 0 || dy != 0) {
            sprite.move(dx * speed * time, dy * speed * time);
        }
    }

    void update(float& time,Player &player,vector<vector<char> > TileMap) {
        rand();
        move(time, player);
        if (sprite.getGlobalBounds().intersects(player.sprite.getGlobalBounds())) {
            teleport(TileMap);
        }
    }
};