#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h";

using namespace std;
using namespace sf;


class Enemy {
private:

public:
    Sprite sprite;
    string File;
    Image image;
    Texture texture;
    //bool Intercet = false;
    float dx, dy, speed = 0;
    float x, y;
    float w, h;
    //pair<int, int> CurrentTile;
    int Health = 5;

    Enemy(string NamePicture, float X, float Y,float Left,float Top, float W, float H,float spriteScale,float speedBUFF)
    {
        speed = speedBUFF;
        File = NamePicture;
        w = W; h = H;
        image.loadFromFile(File);
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        x = X; y = Y;
        sprite.setTextureRect(IntRect(Top, Left, w, h));
        sprite.setScale(spriteScale, spriteScale);
        //sprite.setColor(Color(sprite.getColor().r, sprite.getColor().g, sprite.getColor().b, 245));
        sprite.setPosition(x, y);
    }
};


class Ghost : public Enemy {
public:
    //float speed = 0.177;
    //int dir = 0;
    float CurrentFrame = 0;
    bool isTeleporting = false;
    bool Hide = false;
    int currentAlpha = 245;

    Ghost(string NamePicture, float X, float Y, float Left, float Top, float W, float H, float spriteScale,float speed):Enemy(NamePicture,X,Y,Left,Top,W,H,spriteScale,speed){}

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
        if (dx != 0 || dy != 0) {
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
            if (currentAlpha > 245) {
                currentAlpha = 245;
                isTeleporting = false;
                sprite.setColor(Color(sprite.getColor().r, sprite.getColor().g, sprite.getColor().b, currentAlpha));
            }
        }
        
    }

    void update(float& time,Player &player,sf::String TileMap[]) {
        
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



class Test : public Enemy {
public:
    float CurrentFrame = 0;
    //bool isTeleporting = false;
    //bool Hide = false;
    //int currentAlpha = 255;

    Test(string NamePicture, float X, float Y, float Left, float Top, float W, float H, float spriteScale, float speed) :Enemy(NamePicture, X, Y, Left, Top, W, H, spriteScale, speed) {}



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


    void update(float& time, Player& player, sf::String TileMap[]) {


        move(time, player);
        //Intercet = false;
    }
   
};

class Turrel : public Enemy {
public:
    float CurrentFrame = 0;
    float fireRate = 2.2;
    float currentTime = 2.2;
    //bool isTeleporting = false;
    //bool Hide = false;
    //int currentAlpha = 255;

    Turrel(string NamePicture, float X, float Y, float Left, float Top, float W, float H, float spriteScale, float speed) :Enemy(NamePicture, X, Y, Left, Top, W, H, spriteScale, speed) {}



    void fire(float time, Player& player) {
       
    }

    void Animation(float time) {
        if (CurrentFrame > 6) {
            CurrentFrame = 0;
        }
        sprite.setTextureRect(IntRect((int)CurrentFrame*128, 0, 128, 128));
        CurrentFrame += 0.04 * time;
        
    }

    void update(float& time, Player& player, sf::String TileMap[]) {

        Animation(time);
        if (currentTime <= 0) {
            fire(time, player);
            currentTime = fireRate;
        }
        currentTime -= 0.01 * time;

        //move(time, player);
        //Intercet = false;
    }

};