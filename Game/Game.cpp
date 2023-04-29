#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <iostream>
#include <cmath>
#include<iomanip>
#include<Windows.h>
//#include "Maps.h";
#include "View.h";
#include "Player.h";
#include "map.h";
//#include "Enemy.h";
#include "EnemyTest.h";
#include "Bullet.h"
#include <string>

#include <sstream>

using namespace sf;
using namespace std;

int SCREENX = 1000;
int SCREENY = 600;

vector<vector<char> > TileMap;

void GenerateMap(Sprite& s_map, RenderWindow& window, Player& play, Enemy& Enemy, float& time) {
    for (int i = 0; i < HEIGHT_MAP; i++)
        for (int j = 0; j < WIDTH_MAP; j++)
        {
            if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(64, 224, 32, 32)); //���� ��������� ������ ������, �� ������ 1� ���������
            if (TileMap[i][j] == 's')  s_map.setTextureRect(IntRect(160, 160, 32, 32));//���� ��������� ������ s, �� ������ 2� ���������
            if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(160, 160, 32, 32));//���� ��������� ������ 0, �� ������ 3� ���������
            if ((TileMap[i][j] == '+')) { s_map.setTextureRect(IntRect(0, 160, 32, 32)); }
            s_map.setPosition(j * 32, i * 32);//�� ���� ����������� ����������, ��������� � �����. �� ���� ������ ������� �� ��� �������. ���� ������, �� ��� ����� ���������� � ����� �������� 32*32 � �� ������ ���� �������


            window.draw(s_map);//������ ���������� �� �����
        }

}

int main()
{
    std::srand(std::time(nullptr));
    qmap Map;
    Map.initMap();
    Map.initMainMap();
    Map.addDoor();

    TileMap = Map.getMainMap();

    sf::RenderWindow window(sf::VideoMode(SCREENX, SCREENY), "GameProject");
    view.reset(FloatRect(0, 0, SCREENX, SCREENY));

    Font font;
    font.loadFromFile("KarmaFuture.ttf");
    Text textCoord("", font, 16);
    Text textSpawnPoint("", font, 16);

    Image map_image;//������ ����������� ��� �����
    map_image.loadFromFile("Assets/Kings and Pigs/Sprites/14-TileSets/Terrain (32x32).png");//��������� ���� ��� �����
    Texture tmap;//�������� �����
    tmap.loadFromImage(map_image);//�������� �������� ���������
    Sprite s_map;//������ ������ ��� �����
    s_map.setTexture(tmap);//�������� �������� ��������

    sf::Clock clock;
    int X = Map.getSpawn().first;
    int Y = Map.getSpawn().second;
    //Player player("Assets/AnimationSheet_Character.png", 50, 50, 32, 32);
    Player player("Assets/AnimationSheet_Character.png",
        Map.getSpawn(), Map.getRoomWidth(), Map.getRoomHieght(), 32, 32);
    Ghost ghost("Assets/AnimationSheet_Character.png", 3 * 32, 9 * 32, 32, 32);
    Bullet bullet("Assets/Just_arrow.png", 50, 50, 0.5);

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time /= 16000;
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
                window.close();
        }

        window.setView(view); // ���������� ������

        std::ostringstream playerCoordX;
        playerCoordX << player.getPlayerCoordinateX();
        std::ostringstream playerCoordY;
        playerCoordY << player.getPlayerCoordinateY();

        std::ostringstream SpawnPointX;
        SpawnPointX << Map.getSpawn().first;
        std::ostringstream SpawnPointY;
        SpawnPointY << Map.getSpawn().second;

        textCoord.setString("Score " + playerCoordX.str() + " " + playerCoordY.str());
        textCoord.setPosition(view.getCenter().x - SCREENX / 2, view.getCenter().y - SCREENY / 2);
        textSpawnPoint.setString("Spawn coord: " + SpawnPointX.str() + " " + SpawnPointY.str());
        textSpawnPoint.setPosition(view.getCenter().x - SCREENX / 2, view.getCenter().y - SCREENY / 2 + 32);

        window.clear(Color(128, 106, 89));
        GenerateMap(s_map, window, player, ghost, time); // ��������� �����
        player.update(time, TileMap, view);
        ghost.update(time, player, TileMap);
        bullet.Update(time, player.getPlayerCoordinateX(), player.getPlayerCoordinateY());

        window.draw(player.sprite);
        window.draw(ghost.sprite);
        window.draw(bullet.sprite);

        window.draw(textCoord);
        window.draw(textSpawnPoint);



        window.display();
    }
    return 0;
}
