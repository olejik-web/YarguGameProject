#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;


class Player {
private:
    float x, y;
    float w, h, dx, dy, speed = 0;
    int dir = 0;
    float CurrentFrame = 0;

public:
    Sprite sprite;
    string File;
    Image image;
    Texture texture;

    Player(string F, float X, float Y, float W, float H)
    {
        File = F;
        w = W; h = H;
        image.loadFromFile(File);
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        x = X; y = Y;
        sprite.setTextureRect(IntRect(w, h, w, h));
    }

    void DirClear() { dir = 0; } // Забыть направление, в котором бежал персонаж.
    void DirPlus(int n) { dir |= n; } // Сложение направление.

    void setSpeed(float n) { speed = n; } // Задание скорости передвижения персонажа.

    void move() // Обновление фреймов и вычисление нажатой клавиши перемещения.
    {
        if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A) ||
            Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D) ||
            Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W) ||
            Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S)) // Проверка нажатия клавиши.
            CurrentFrame += 0.01; // Проигрывания анимации, если клавиша нажата.
        if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W)) // Бег вверх.
        {
            DirPlus(1 << 3); setSpeed(0.1);
            sprite.setTextureRect(IntRect(16 * int(CurrentFrame), 0, w, h));
        }
        if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S)) // Бег вниз.
        {
            DirPlus(1 << 2); setSpeed(0.1);
            sprite.setTextureRect(IntRect(16 * int(CurrentFrame), 0, w, h));
        }
        if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)) // Бег вправо.
        {
            DirPlus(1 << 1); setSpeed(0.1);
            sprite.setTextureRect(IntRect(16 * int(CurrentFrame), 16, w, h));
        }
        if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)) // Бег влево.
        {
            DirPlus(1 << 0); setSpeed(0.1);
            sprite.setTextureRect(IntRect(16 * int(CurrentFrame), 0, w, h));
        }
        if (CurrentFrame >= 4) CurrentFrame -= 4;
    }

    void interactionWithMap(String* TileMap, float time)
    {
        for (int i = 0; i < h; i++)
        {
            if ((dx > 0) && TileMap[int(x + w + dx) / 16][int(y + i) / 16] == '0')
            {
                x = int(x + dx);
                break;
            }
            if ((dx < 0) && TileMap[int(x + dx) / 16][int(y + i) / 16] == '0') // Проверка пересикаечения со стеной при перемещении вправо.
            {
                x = int((x + dx) / 16) * 16 + w;
                break;
            }

            // Прибавляем смещение к координатам персонажа.
            if(i == h-1)
                x += dx * time;
        }

        for (int j = 0; j < w; j++)
        {
            if ((dy > 0) && TileMap[int(x + j) / 16][int(y + h + dy) / 16] == '0') // Проверка пересикаечения со стеной при перемещении вниз.
            {
                y = int(y + dy);
                break;
            }
            if ((dy < 0) && TileMap[int(x + j) / 16][int(y + dy) / 16] == '0') // Проверка пересикаечения со стеной при перемещении вверх.
            {
                y = int((y + dy + h) / 16) * 16;
                break;
            }

            // Прибавляем смещение к координатам персонажа.
            if(j == w-1)
                y += dy * time;
        }

    }

    void update(float time, String* TileMap)
    {
        dx = ((1 << 0) & dir ? 1 : 0) * speed - ((1 << 1) & dir ? 1 : 0) * speed; // Вычисляем смещение по x через биты dir.
        dy = ((1 << 2) & dir ? 1 : 0) * speed - ((1 << 3) & dir ? 1 : 0) * speed; // Вычисляем смещение по y через биты dir.

        interactionWithMap(TileMap, time);

        sprite.setPosition(x, y);
    }

    float getPlayerCoordinateX() { return x; }
    float getPlayerCoordinateY() { return y; }
};
