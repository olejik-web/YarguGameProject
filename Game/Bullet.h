#pragma once
#include<SFML/Graphics.hpp>

using namespace sf;


class Bullet {
public:
    float x, y, speed, dx, dy;
    Sprite sprite;
    Texture texture;
    Image image;
    string File;
    bool isFired = false;

    Bullet(String FileName, float X, float Y, float targX, float targY,float speedBuff,float scale) {
        File = FileName;
        speed = speedBuff;
        image.loadFromFile(File);
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        //sprite.setScale(scale, scale);
        x = X; y = Y; 
        dx = (targX - x);
        dy = (targY - y);
        if (dy >= 0)
        {
            sprite.setRotation(-atan(dx / dy) * 90 / 3.14);
        }
        else
        {
            sprite.setRotation(-atan(dx / dy) * 90 / 3.14 + 90);
        }
        sprite.setPosition(x, y);
        float dlinna = sqrt(dx * dx + dy * dy);
        dx /= dlinna;
        dy /= dlinna;
    }


    Bullet(String FileName, float X, float Y, float targX, float targY, float speedBuff, float scale,int q) {
        File = FileName;
        speed = speedBuff;
        image.loadFromFile(File);
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        //sprite.setScale(scale, scale);
        x = X; y = Y;
        dx = targX;
        dy = targY;
        if (dy >= 0)
        {
            sprite.setRotation(-atan(dx / dy) * 90 / 3.14);
        }
        else
        {
            sprite.setRotation(-atan(dx / dy) * 90 / 3.14 + 90);
        }
        sprite.setPosition(x, y);
        float dlinna = sqrt(dx * dx + dy * dy);
        dx /= dlinna;
        dy /= dlinna;
    }

    virtual void Update(float& time) {
        
    }

    ~Bullet()
    {

    }
};

class IceShard : public Bullet {

public:
    float CurrentFrame = 0;
    IceShard(String FileName, float X, float Y, float targX, float targY, float speed, float scale) :Bullet(FileName, X, Y, targX, targY,speed, scale) { 
        sprite.setTextureRect(IntRect(0, 0, 48, 32));
        sprite.setOrigin(24, 16);
        sprite.setScale(scale, scale);
        if (dy >= 0)
        {
            sprite.setRotation(-atan(dx / dy) * 180 / 3.14 + 90);
        }
        else
        {
            sprite.setRotation(-atan(dx / dy) * 180 / 3.14 + 270);
        }
        sprite.setPosition(x, y);
    }
    
    void Animation(float& time) {
        if (CurrentFrame > 10) {
            CurrentFrame = 0;
        }
        sprite.setTextureRect(IntRect((int)CurrentFrame * 48, 0, 48, 32));
        CurrentFrame += 0.01 * time;
    }

    void Update(float& time) {
        Animation(time);
        sprite.move(dx * speed * time, dy * speed * time);
    }
    
};

class FireShard : public Bullet {

public:
    float CurrentFrame = 0;
    FireShard(String FileName, float X, float Y, float targX, float targY, float speed, float scale, int q) :Bullet(FileName, X, Y, targX, targY, speed, scale,q) {
        sprite.setTextureRect(IntRect(0, 0, 32, 32));
        sprite.setOrigin(16, 16);
        sprite.setScale(scale, scale);
        if (dy >= 0)
        {
            sprite.setRotation(-atan(dx / dy) * 180 / 3.14 + 90);
        }
        else
        {
            sprite.setRotation(-atan(dx / dy) * 180 / 3.14 + 270);
        }
        //sprite.setPosition(x, y);
    }

    void Animation(float& time) {
        if (CurrentFrame > 8) {
            CurrentFrame = 0;
        }
        sprite.setTextureRect(IntRect((int)CurrentFrame * 32, 0, 32, 32));
        CurrentFrame += 0.06 * time;
    }

    void Update(float& time) {
        Animation(time);
        sprite.move(dx * speed * time, dy * speed * time);
    }

};

class FireBall : public Bullet {

public:
    float CurrentFrame = 0;
    FireBall(String FileName, float X, float Y, float targX, float targY, float speed, float scale) :Bullet(FileName, X, Y, targX, targY, speed, scale) {
        sprite.setTextureRect(IntRect(0, 0, 18, 12));
        sprite.setOrigin(9, 6);
        sprite.setScale(scale, scale);
        if (dy >= 0)
        {
            sprite.setRotation(-atan(dx / dy) * 180 / 3.14 + 90);
        }
        else
        {
            sprite.setRotation(-atan(dx / dy) * 180 / 3.14 + 270);
        }
        //sprite.setPosition(x, y);
    }

    void Animation(float& time) {
        if (CurrentFrame > 4) {
            CurrentFrame = 0;
        }
        sprite.setTextureRect(IntRect((int)CurrentFrame * 32, 0, 18, 12));
        CurrentFrame += 0.06 * time;
    }

    void Update(float& time) {
        Animation(time);
        sprite.move(dx * speed * time, dy * speed * time);
    }

};

class Bolt : public Bullet {

public:
    float CurrentFrame = 0;
    Bolt(String FileName, float X, float Y, float targX, float targY, float speed, float scale) :Bullet(FileName, X, Y, targX, targY, speed, scale) {
        sprite.setTextureRect(IntRect(0, 0, 32, 19));
        sprite.setOrigin(16, 9.5);
        sprite.setScale(scale, scale);
        if (dy >= 0)
        {
            sprite.setRotation(-atan(dx / dy) * 180 / 3.14 + 90);
        }
        else
        {
            sprite.setRotation(-atan(dx / dy) * 180 / 3.14 + 270);
        }
        //sprite.setPosition(x, y);
    }

    void Animation(float& time) {
        if (CurrentFrame > 4) {
            CurrentFrame = 0;
        }
        sprite.setTextureRect(IntRect((int)CurrentFrame * 32, 0, 32, 19));
        CurrentFrame += 1 * time;
    }

    void Update(float& time) {
        Animation(time);
        sprite.move(dx * speed * time, dy * speed * time);
    }

};

vector<Bullet*> bullets;