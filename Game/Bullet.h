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
        x = X + 8;
        y = Y + 8;
        sprite.setPosition(x, y);
        targetX = targX;
        targetY = targY;
        dx = (targetX - x);
        dy = (targetY - y);
        cout << x << " " << y << " " << dx << " " << dy << " " << sqrt(dx * dx + dy * dy) << '\n';
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