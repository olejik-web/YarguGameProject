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

        x = 50;
        y = 50;

        if (X > 0 && Y > 0)
        {
            x = (Y) * 2 * roomWidth * 32 + 50;
            y = (X) * 2 * roomHieght * 32 + 50;
        }
        else if (X > 0)
            y = (X) * 2 * roomHieght * 32 + 50;
        else if (Y > 0)
            x = (Y) * 2 * roomWidth * 32 + 50;

        File = F;
        w = W; h = H;
        image.loadFromFile(File);
        texture.loadFromImage(image);
        sprite.setTexture(texture);

        sprite.setTextureRect(IntRect(w, h, w, h));
        sprite.setPosition(x, y);
    }

    void DirClear() { dir = 0; } // ������ �����������, � ������� ����� ��������.
    void DirPlus(int n) { dir |= n; } // �������� �����������.

    void setSpeed(float n) { speed = 3; } // ������� �������� ������������ ���������.

    void move() // ���������� ������� � ���������� ������� ������� �����������.
    {
        if (!isAttack && Health) {
            if (Keyboard::isKeyPressed(Keyboard::Left) ||
                Keyboard::isKeyPressed(Keyboard::Right)||
                Keyboard::isKeyPressed(Keyboard::Up) ||
                Keyboard::isKeyPressed(Keyboard::Down)) // �������� ������� �������.
                CurrentFrame += 0.05; // ������������ ��������, ���� ������� ������.
            if (Keyboard::isKeyPressed(Keyboard::Up)) // ��� �����.
            {
                DirPlus(1 << 3); setSpeed(0.3);
                sprite.setTextureRect(IntRect(32 * int(CurrentFrame) + 32, 64, -32, 32));
            }
            if (Keyboard::isKeyPressed(Keyboard::Down)) // ��� ����.
            {
                DirPlus(1 << 2); setSpeed(0.3);
                sprite.setTextureRect(IntRect(32 * int(CurrentFrame), 64, 32, 32));
            }
            if (Keyboard::isKeyPressed(Keyboard::Left)) // ��� �����.
            {
                isRight = false;
                DirPlus(1 << 1); setSpeed(0.3);
                sprite.setTextureRect(IntRect(32 * int(CurrentFrame) + 32, 64, -32, 32));
            }
            if (Keyboard::isKeyPressed(Keyboard::Right)) // ��� ������.
            {
                isRight = true;
                DirPlus(1 << 0); setSpeed(0.3);
                sprite.setTextureRect(IntRect(32 * int(CurrentFrame), 64, 32, 32));
            }
            if (CurrentFrame >= 4) CurrentFrame -= 4;
        }
    }

    void Attack(float& time) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !isAttack) { //�=��������� ��������� ��� ����� ��������
            CurrentFrame = 0;
            isAttack = true;
        }

        if (isAttack) { // �������� �����
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

    void interactionWithMap(float& time, vector<vector<char> > TileMap)
    {
        for (int i = 0; i < h; i++)
        {

            //if ((dx > 0) && TileMap[int(x + w + dx) / TILE_SIZE][int(y + i) / TILE_SIZE] == '0')
            if ((dx > 0) && TileMap[int(y + i) / TILE_SIZE][int(x + w + dx) / TILE_SIZE] == '0')
            {
                x = int(x + dx);
                break;
            }
            //if ((dx < 0) && TileMap[int(x + dx) / TILE_SIZE][int(y + i) / TILE_SIZE] == '0')
            if ((dx < 0) && TileMap[int(y + i) / TILE_SIZE][int(x + dx) / TILE_SIZE] == '0') // �������� �������������� �� ������ ��� ����������� ������.
            {
                x = int((x + dx) / TILE_SIZE) * TILE_SIZE + w;
                break;
            }

            // ���������� �������� � ����������� ���������.
            if (i == h - 1)
                x += dx * time;
        }

        for (int j = 0; j < w; j++)
        {
            //if ((dy > 0) && TileMap[int(x + j) / TILE_SIZE][int(y + h + dy) / TILE_SIZE] == '0')
            if ((dy > 0) && TileMap[int(y + h + dy) / TILE_SIZE][int(x + j) / TILE_SIZE] == '0') // �������� �������������� �� ������ ��� ����������� ����.
            {
                y = int(y + dy);
                break;
            }
            //if ((dy < 0) && TileMap[int(x + j) / TILE_SIZE][int(y + dy) / TILE_SIZE] == '0')
            if ((dy < 0) && TileMap[int(y + dy) / TILE_SIZE][int(x + j) / TILE_SIZE] == '0') // �������� �������������� �� ������ ��� ����������� �����.
            {
                y = int((y + dy + h) / TILE_SIZE) * TILE_SIZE;
                break;
            }

            // ���������� �������� � ����������� ���������.
            if (j == w - 1)
                y += dy * time;
        }

    }

    void update(float& time, vector<vector<char> > TileMap,View& view)
    {


        dx = ((1 << 0) & dir ? 1 : 0) * speed - ((1 << 1) & dir ? 1 : 0) * speed; // ��������� �������� �� x ����� ���� dir.
        dy = ((1 << 2) & dir ? 1 : 0) * speed - ((1 << 3) & dir ? 1 : 0) * speed; // ��������� �������� �� y ����� ���� dir.
        DirClear();
        
        view.setCenter(getPlayerCoordinateX(), getPlayerCoordinateY());


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::G) && !isAttack) { //�=��������� ��������� ��� ����� ��������
            cout << dir << ' ' << speed << '\n';
        }

        move();
        interactionWithMap(time,TileMap);
        sprite.setPosition(x, y);
        //move();
        Attack(time);
    }

    float getPlayerCoordinateX() { return x; }
    float getPlayerCoordinateY() { return y; }

    void setPlayerCoordinateX(float X) { x = X; }
    void setPlayerCoordinateY(float Y) { y = Y; }
};
