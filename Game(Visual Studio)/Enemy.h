#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <queue>;
#include <stack>;
#include "Player.h";

using namespace std;
using namespace sf;

class Enemy {
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


    pair<int, int> CurrentTile;
    bool isMove = false;
    pair<int, int> CurrentWay;
    float NeedChangeWay = 0;

    //vector<int> d();
    stack<pair<int, int> >Ways;


    Enemy(string F, float X, float Y, float W, float H)
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

    void FindWay(Player& player, sf::String TileMap[],int n,int m,int fin1,int fin2) {
        vector<vector<pair<int, int> > > put(HEIGHT_MAP+1, vector<pair<int, int> >(WIDTH_MAP+1, {-1,-1}));
        vector<vector<int> >  used(HEIGHT_MAP + 1, vector<int>(WIDTH_MAP+1,0));
        queue<pair<int, int>> q;
        q.push({ n,m });              //� �������� ��������� ������� ���������� 0.M
        vector<int> dx = { 1,0,-1,0};
        vector<int> dy = { 0,1,0,-1};


        while (!q.empty()) {
            pair<int, int> cur = q.front();  //��������� �� ������� ������� �������
            q.pop();

            //����� ������ ���� ��������� ������� �������.
            int y = cur.first;
            int x = cur.second;
            used[y][x] = 1;
            for (int i = 0; i < dx.size(); i++) {
                int nx = x + dx[i], ny = y + dy[i];
                
                if (nx >= 0 && ny >= 0 && ny < HEIGHT_MAP && nx < WIDTH_MAP && !used[ny][nx] && TileMap[ny][nx] != '0') {
                    q.push({ ny,nx });
                    used[ny][nx] = 1;
                    put[ny][nx] = { y,x };
                }
            }
        }

        for (int i = 0; i < HEIGHT_MAP; i++) {
            for (int j = 0; j < WIDTH_MAP; j++) {
                cout << '(' << put[i][j].first << ' ' << put[i][j].second << ')' << ' ';
            }
            cout << '\n';
        }

        pair<int, int> buffer = put[fin1][fin2];
        if(buffer.first != -1 && buffer.second != -1){ Ways.push({ fin1,fin2 }); }
        while (buffer.first != -1 && buffer.second != -1) {
            Ways.push(buffer);
            buffer = put[buffer.first][buffer.second];
        }
    }

    void calcSpriteMove(float& time) {
        float VectY = CurrentWay.first * 32 - CurrentTile.first * 32;
        float VectX = CurrentWay.second * 32 - CurrentTile.second * 32;
        float speed = sqrt(VectX * VectX + VectY * VectY);
        sprite.setPosition(sprite.getPosition().x + (VectX / speed) * 0.2 * time, sprite.getPosition().y + (VectY / speed) * 0.2 * time);
    }

    void move(float time) {
        if (!isMove && !Ways.empty()) {
            CurrentWay = Ways.top();
            Ways.pop();
            isMove = true;
        }
        if(CurrentTile != CurrentWay && isMove) {
            //float VectX = CurrentWay.second - CurrentTile.second;
           // float VectY = CurrentWay.first - CurrentTile.first;
            calcSpriteMove(time);
            
        }
        if (Ways.size() > 0) {
            CurrentWay = Ways.top();
        }
        

    }

    void update(float time,Player& player, sf::String TileMap[]) {
        if (NeedChangeWay <= 0) {
            
            isMove = false;  
            FindWay(player, TileMap, CurrentTile.first, CurrentTile.second, player.CurrentTile.first, player.CurrentTile.second);
            
            NeedChangeWay = 5;
        }
        move(time);
        cout << CurrentTile.first << ' ' << CurrentTile.second << '\n';
        NeedChangeWay -= 0.1 * time;
    }
};