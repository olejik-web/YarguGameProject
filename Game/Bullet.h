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

    Bullet(float X, float Y) {
        File = "Assets/Just_arrow.png";
        image.loadFromFile(File);
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        x = X + 8; y = Y + 8;
        sprite.setPosition(x, y);
        speed = 0.5;
    }

    void Update(float& time) {
            x += speed * time;
            y += 0;
            sprite.setPosition(x, y);
    }

    ~Bullet()
    {

    }
};