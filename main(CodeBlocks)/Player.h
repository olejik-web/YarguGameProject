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

    void DirClear() { dir = 0; } // ������ �����������, � ������� ����� ��������.
    void DirPlus(int n) { dir |= n; } // �������� �����������.

    void setSpeed(float n) { speed = n; } // ������� �������� ������������ ���������.

    void move() // ���������� ������� � ���������� ������� ������� �����������.
    {
        if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A) ||
            Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D) ||
            Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W) ||
            Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S)) // �������� ������� �������.
            CurrentFrame += 0.01; // ������������ ��������, ���� ������� ������.
        if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W)) // ��� �����.
        {
            DirPlus(1 << 3); setSpeed(0.1);
            sprite.setTextureRect(IntRect(16 * int(CurrentFrame), 0, w, h));
        }
        if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S)) // ��� ����.
        {
            DirPlus(1 << 2); setSpeed(0.1);
            sprite.setTextureRect(IntRect(16 * int(CurrentFrame), 0, w, h));
        }
        if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)) // ��� ������.
        {
            DirPlus(1 << 1); setSpeed(0.1);
            sprite.setTextureRect(IntRect(16 * int(CurrentFrame), 16, w, h));
        }
        if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)) // ��� �����.
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
            if ((dx < 0) && TileMap[int(x + dx) / 16][int(y + i) / 16] == '0') // �������� �������������� �� ������ ��� ����������� ������.
            {
                x = int((x + dx) / 16) * 16 + w;
                break;
            }

            // ���������� �������� � ����������� ���������.
            if(i == h-1)
                x += dx * time;
        }

        for (int j = 0; j < w; j++)
        {
            if ((dy > 0) && TileMap[int(x + j) / 16][int(y + h + dy) / 16] == '0') // �������� �������������� �� ������ ��� ����������� ����.
            {
                y = int(y + dy);
                break;
            }
            if ((dy < 0) && TileMap[int(x + j) / 16][int(y + dy) / 16] == '0') // �������� �������������� �� ������ ��� ����������� �����.
            {
                y = int((y + dy + h) / 16) * 16;
                break;
            }

            // ���������� �������� � ����������� ���������.
            if(j == w-1)
                y += dy * time;
        }

    }

    void update(float time, String* TileMap)
    {
        dx = ((1 << 0) & dir ? 1 : 0) * speed - ((1 << 1) & dir ? 1 : 0) * speed; // ��������� �������� �� x ����� ���� dir.
        dy = ((1 << 2) & dir ? 1 : 0) * speed - ((1 << 3) & dir ? 1 : 0) * speed; // ��������� �������� �� y ����� ���� dir.

        interactionWithMap(TileMap, time);

        sprite.setPosition(x, y);
    }

    float getPlayerCoordinateX() { return x; }
    float getPlayerCoordinateY() { return y; }
};
