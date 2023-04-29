#pragma once
#include<SFML/Graphics.hpp>
#include <cmath>

using namespace sf;

class Bullet {
public:
    float x, y, targetX, targetY, speed = 0.3, dx, dy;
    Sprite sprite;
    Texture texture;
    Image image;
    string File;
    bool isFired = false;

    Bullet(float X, float Y, float targX, float targY) {
        File = "Assets/Just_arrow.png";
        image.loadFromFile(File);
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        sprite.setOrigin(8, 0);
        x = X + 16;
        y = Y + 16;
        targetX = targX;
        targetY = targY;
        dx = (targetX - x);
        dy = (targetY - y);
        if (dy >= 0)
        {
            sprite.setRotation(-atan(dx / dy) * 180 / 3.14);
        }
        else
        {
            sprite.setRotation(-atan(dx / dy) * 180 / 3.14 + 180);
        }
        sprite.setPosition(x, y);
        float dlinna = sqrt(dx * dx + dy * dy);
        dx /= dlinna;
        dy /= dlinna;
    }

    void Update(float& time) {
        sprite.move(dx * speed * time, dy * speed * time);
    }

    ~Bullet()
    {

    }
};