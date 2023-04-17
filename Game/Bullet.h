#pragma once
#include<SFML/Graphics.hpp>

using namespace sf;

class Bullet {
public:
    float x, y, speed;
    Sprite sprite;
    Texture texture;
    Image image;
    string File;
    bool isFired = false;

    Bullet(string F, float X, float Y, float Speed) {
        File = F;
        image.loadFromFile(File);
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        x = X; y = Y;
        speed = Speed;
    }

    void Fire() {
        if (Keyboard::isKeyPressed(Keyboard::Space))
        {
            isFired = true;
            sprite.setPosition(x, y);
        }
    }

    void Move(float& time) {
        x += speed * time;
        y += 0;
        sprite.setPosition(x, y);
    }

    void Update(float& time, float X, float Y) {
        if (isFired) {
            Move(time);
        }
        else
        {
            x = X;
            y = Y;
        }
        Fire();
    }
};