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

    Enemy(string F, float X, float Y,float Left,float Top, float W, float H)
    {
        File = F;
        w = W; h = H;
        image.loadFromFile(File);
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        x = X; y = Y;
        sprite.setTextureRect(IntRect(Top, Left, w, h));
        sprite.setPosition(x, y);
    }
};


class Ghost : public Enemy {
public:
    float dx, dy, speed = 0.2;
    int dir = 0;
    float CurrentFrame = 0;
    bool isTeleporting = false;
    bool Hide = false;
    int currentAlpha = 255;

    Ghost(string F, float X, float Y, float Left, float Top, float W, float H):Enemy(F,X,Y,Left,Top,W,H){}

    void teleport(sf::String TileMap[]) {
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
        changeSprite(dlina);
        dx /= dlina;
        dy /= dlina;
        if (dx != 0 && dy != 0) {
            sprite.move(dx * speed * time, dy * speed * time);
        }
    }

    void changeSprite(float &dlina) {
        if (dx < 0) {
            if (dlina <= 96) {
                sprite.setTextureRect(IntRect(128, 0, 64, 80));
            }
            else {
                sprite.setTextureRect(IntRect(0, 0, 64, 80));
            }
        }
        else {
            if (dlina <= 96) {
                sprite.setTextureRect(IntRect(192, 0, -64, 80));
            }
            else {
                sprite.setTextureRect(IntRect(64, 0, -64, 80));
            }
        }
    }
    
    void TeleportAnimation(float time, sf::String TileMap[]) {
        if (Hide) {
            currentAlpha -= 1;
            sprite.setColor(Color(sprite.getColor().r, sprite.getColor().g, sprite.getColor().b, currentAlpha));
            if (currentAlpha <= 0) {
                currentAlpha = 0;
                sprite.setColor(Color(sprite.getColor().r, sprite.getColor().g, sprite.getColor().b, currentAlpha));
                Hide = false;
                teleport(TileMap);
            }
        }
        else {
            currentAlpha += 1;
            sprite.setColor(Color(sprite.getColor().r, sprite.getColor().g, sprite.getColor().b, currentAlpha));
            if (currentAlpha > 255) {
                currentAlpha = 255;
                isTeleporting = false;
                sprite.setColor(Color(sprite.getColor().r, sprite.getColor().g, sprite.getColor().b, currentAlpha));
            }
        }
        
    }

    void update(float& time,Player &player,sf::String TileMap[]) {
        rand();
        if (sprite.getGlobalBounds().intersects(player.sprite.getGlobalBounds())) {
            isTeleporting = true;
            Hide = true;
        }
        if (isTeleporting == false) {
            move(time, player);
        }
        else {
            TeleportAnimation(time,TileMap);
        }
    }
};