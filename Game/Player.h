#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>

using namespace std;
using namespace sf;

const int TILE_SIZE = 32;

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

    bool isAttack = false;
    bool isRight = true;
    int Health = 5;

    Player(string F, float X, float Y, float W, float H)
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

    Player(string F, pair<int, int> coordSpawn, int roomWidth, int roomHieght, float W, float H)
    {
        int X = coordSpawn.first;
        int Y = coordSpawn.second;

        x = (Y) * 2 * roomWidth * 32 + 50;
        y = (X) * 2 * roomHieght * 32 + 50;

        File = F;
        w = W; h = H;
        image.loadFromFile(File);
        texture.loadFromImage(image);
        sprite.setTexture(texture);

        sprite.setTextureRect(IntRect(w, h, w, h));
        sprite.setPosition(x, y);
    }

    void DirClear() { dir = 0; } // Забыть направление, в котором бежал персонаж.
    void DirPlus(int n) { dir |= n; } // Сложение направление.

    void setSpeed(float n) { speed = 0.5; } // Задание скорости передвижения персонажа.

    void move() // Обновление фреймов и вычисление нажатой клавиши перемещения.
    {
        if (!isAttack && Health) {
            if (Keyboard::isKeyPressed(Keyboard::Left) ||
                Keyboard::isKeyPressed(Keyboard::Right)||
                Keyboard::isKeyPressed(Keyboard::Up) ||
                Keyboard::isKeyPressed(Keyboard::Down)) // Проверка нажатия клавиши.
                CurrentFrame += 0.05; // Проигрывания анимации, если клавиша нажата.
            if (CurrentFrame >= 4) CurrentFrame -= 4;
            if (Keyboard::isKeyPressed(Keyboard::Up)) // Бег вверх.
            {
                DirPlus(1 << 3); setSpeed(0.3);
                sprite.setTextureRect(IntRect(32 * int(CurrentFrame) + 32, 64, -32, 32));
            }
            if (Keyboard::isKeyPressed(Keyboard::Down)) // Бег вниз.
            {
                DirPlus(1 << 2); setSpeed(0.3);
                sprite.setTextureRect(IntRect(32 * int(CurrentFrame), 64, 32, 32));
            }
            if (Keyboard::isKeyPressed(Keyboard::Left)) // Бег влево.
            {
                isRight = false;
                DirPlus(1 << 1); setSpeed(0.3);
                sprite.setTextureRect(IntRect(32 * int(CurrentFrame) + 32, 64, -32, 32));
            }
            if (Keyboard::isKeyPressed(Keyboard::Right)) // Бег вправо.
            {
                isRight = true;
                DirPlus(1 << 0); setSpeed(0.3);
                sprite.setTextureRect(IntRect(32 * int(CurrentFrame), 64, 32, 32));
            }
        }
    }

    void Attack(float& time) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !isAttack) { //ь=булевская переменая что герой аттакует
            CurrentFrame = 0;
            isAttack = true;
        }

        if (isAttack) { // анимация атаки
            CurrentFrame += 0.06 * time;
            if (isRight) {
                sprite.setTextureRect(IntRect(32 * int(CurrentFrame), 256, 32, 32));
            }
            else {
                sprite.setTextureRect(IntRect(32 * int(CurrentFrame) + 32, 256, -32, 32));
            }
            if (CurrentFrame > 7) {
                isAttack = false;
                CurrentFrame = 0;
                if (isRight) {
                    sprite.setTextureRect(IntRect(0, 0, 32, 32));;
                }
                else {
                    sprite.setTextureRect(IntRect(32, 0, -32, 32));;
                }
            }
        }
    }

    void interactionWithMap(float& time, vector<vector<char> >& TileMap)
    {
        bool X = 0, Y = 0;
        dx *= time;
        dy *= time;
        for (long double i = 0; i < h; i+=1)
        {

            // Проверка пересикаечения со стеной при перемещении вправо.
            if ((dx > 0) && TileMap[int(y + i) / TILE_SIZE][int(x + w + dx) / TILE_SIZE] == '0')
            {
                cout << 1 << '\n';
                x = int((x + dx) / TILE_SIZE) * TILE_SIZE;
                break;
            }
            // Проверка пересикаечения со стеной при перемещении влево.
            if ((dx < 0) && TileMap[int(y + i) / TILE_SIZE][int(x + dx) / TILE_SIZE] == '0')
            {
                cout << 2 << '\n';
                x = int((x + dx) / TILE_SIZE + 1) * TILE_SIZE;
                break;
            }

            // Прибавляем смещение к координатам персонажа.
            if (i == h - 1)
                X = true;
        }

        for (long double j = 0; j < w; j+=1)
        {
            // Проверка пересикаечения со стеной при перемещении вниз.
            if ((dy > 0) && TileMap[int(y + h + dy) / TILE_SIZE][int(x + j) / TILE_SIZE] == '0')
            {
                cout << 3 << '\n';
                y = int((y + dy) / TILE_SIZE) * TILE_SIZE;
                break;
            }
            // Проверка пересикаечения со стеной при перемещении вверх.
            if ((dy < 0) && TileMap[int(y + dy) / TILE_SIZE][int(x + j + 0.1) / TILE_SIZE] == '0')
            {
                cout << 4 << '\n';
                y = int((y + dy + h) / TILE_SIZE) * TILE_SIZE;
                break;
            }

            // Прибавляем смещение к координатам персонажа.
            if (j == w - 1)
                Y = true;
        }
        if (X)
            x += dx;
        if(Y)
            y += dy;
        cout << fixed << setprecision(18) << x << ' ' << y << '\n';

    }

    void update(float& time, vector<vector<char> >& TileMap,View& view)
    {


        dx = ((1 << 0) & dir ? 1 : 0) * speed - ((1 << 1) & dir ? 1 : 0) * speed; // Вычисляем смещение по x через биты dir.
        dy = ((1 << 2) & dir ? 1 : 0) * speed - ((1 << 3) & dir ? 1 : 0) * speed; // Вычисляем смещение по y через биты dir.
        DirClear();
        
        view.setCenter(getPlayerCoordinateX(), getPlayerCoordinateY());

        interactionWithMap(time, TileMap);
        move();
        sprite.setPosition(x, y);
    }

    float getPlayerCoordinateX() { return x; }
    float getPlayerCoordinateY() { return y; }

    void setPlayerCoordinateX(float X) { x = X; }
    void setPlayerCoordinateY(float Y) { y = Y; }
};
