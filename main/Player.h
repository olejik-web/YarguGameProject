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
            sprite.setTextureRect(IntRect(78 * int(CurrentFrame), 58, 78, 58));
        }
        if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S)) // Бег вниз.
        {
            DirPlus(1 << 2); setSpeed(0.1);
            sprite.setTextureRect(IntRect(78 * int(CurrentFrame), 0, 78, 58));
        }
        if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)) // Бег вправо.
        {
            DirPlus(1 << 1); setSpeed(0.1);
            sprite.setTextureRect(IntRect(78 * int(CurrentFrame), 58, 78, 58));
        }
        if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)) // Бег влево.
        {
            DirPlus(1 << 0); setSpeed(0.1);
            sprite.setTextureRect(IntRect(78 * int(CurrentFrame), 0, 78, 58));
        }
        if (CurrentFrame > 7) CurrentFrame -= 7;
    }

    void interactionWithMap(String* TileMap)
    {
        if ((dx > 0) && TileMap[int(x + w + dx) / 16][int(y + h) / 16] == '0') // Проверка пересикаечения со стеной при перемещении влево.
            x -= dx;
        if ((dx < 0) && TileMap[int(x + dx) / 16][int(y) / 16] == '0') // Проверка пересикаечения со стеной при перемещении вправо.
            x -= dx;
        if ((dy > 0) && TileMap[int(x + w) / 16][int(y + h + dy) / 16] == '0') // Проверка пересикаечения со стеной при перемещении вниз.
            y -= dy;
        if ((dy < 0) && TileMap[int(x) / 16][int(y + dy) / 16] == '0') // Проверка пересикаечения со стеной при перемещении вверх.
            y -= dy;

        // Движение во внешний угол. Если стена по диагонали, но не по вертикали и горизонтали.
        if ((dx > 0) && (dy > 0) && TileMap[int(x + w + dx) / 16][int(y + h + dy) / 16] == '0' &&
            !((dx > 0) && TileMap[int(x + w + dx) / 16][int(y + h) / 16] == '0') && 
            !((dy > 0) && TileMap[int(x + w) / 16][int(y + h + dy) / 16] == '0'))
        {
            x -= dx;
            y -= dy;
        }
        if ((dx > 0) && (dy < 0) && TileMap[int(x + w + dx) / 16][int(y + dy) / 16] == '0' &&
            !((dx > 0) && TileMap[int(x + w + dx) / 16][int(y + h) / 16] == '0') &&
            !((dy < 0) && TileMap[int(x) / 16][int(y + dy) / 16] == '0'))
        {
            x -= dx;
            y -= dy;
        }
        if ((dx < 0) && (dy > 0) && TileMap[int(x + dx) / 16][int(y + h + dy) / 16] == '0' &&
            !((dx < 0) && TileMap[int(x + dx) / 16][int(y) / 16] == '0') &&
            !((dy > 0) && TileMap[int(x + w) / 16][int(y + h + dy) / 16] == '0'))
        {
            x -= dx;
            y -= dy;
        }
        if ((dx < 0) && (dy < 0) && TileMap[int(x + dx) / 16][int(y + dy) / 16] == '0' &&
            !((dx < 0) && TileMap[int(x + dx) / 16][int(y) / 16] == '0') &&
            !((dy < 0) && TileMap[int(x) / 16][int(y + dy) / 16] == '0'))
        {
            x -= dx;
            y -= dy;
        }
    }

    void update(float time, String* TileMap)
    {
        dx = ((1 << 0) & dir ? 1 : 0) * speed - ((1 << 1) & dir ? 1 : 0) * speed; // Вычисляем смещение по x через биты dir.
        dy = ((1 << 2) & dir ? 1 : 0) * speed - ((1 << 3) & dir ? 1 : 0) * speed; // Вычисляем смещение по y через биты dir.

        // Прибавляем смещение к координатам персонажа.
        x += dx * time;
        y += dy * time;

        //speed = 0; // Сбрасываем скорость.
        sprite.setPosition(x, y);
        interactionWithMap(TileMap);
    }

    float getPlayerCoordinateX() { return x; }
    float getPlayerCoordinateY() { return y; }
};
