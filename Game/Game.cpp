#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <iostream>
#include <cmath>
#include<iomanip>
#include<Windows.h>
#include "Maps.h";
#include "View.h";
#include "Player.h";

using namespace sf;
using namespace std;

int SCREENX = 1000;
int SCREENY = 600;


void GenerateMap(Sprite& s_map,RenderWindow& window,Player& play,float& time) {
    for (int i = 0; i < HEIGHT_MAP; i++)
        for (int j = 0; j < WIDTH_MAP; j++)
        {
            if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(64, 224, 32, 32)); //если встретили символ пробел, то рисуем 1й квадратик
            if (TileMap[i][j] == 's')  s_map.setTextureRect(IntRect(160, 160, 32, 32));//если встретили символ s, то рисуем 2й квадратик
            if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(160, 160, 32, 32));//если встретили символ 0, то рисуем 3й квадратик
            if ((TileMap[i][j] == '+')) { s_map.setTextureRect(IntRect(0, 160, 32, 32));  }
            s_map.setPosition(j * 32, i * 32);//по сути раскидывает квадратики, превращая в карту. то есть задает каждому из них позицию. если убрать, то вся карта нарисуется в одном квадрате 32*32 и мы увидим один квадрат
            


            /*s_map.setScale(SCREENX * 0.002,
                SCREENY * 0.0035);*/

            window.draw(s_map);//рисуем квадратики на экран
        }

}

int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREENX, SCREENY), "GameProject");
    view.reset(FloatRect(0, 0, SCREENX/4, SCREENY/4));


    Image map_image;//объект изображения для карты
    map_image.loadFromFile("Assets/Kings and Pigs/Sprites/14-TileSets/Terrain (32x32).png");//загружаем файл для карты
    Texture map;//текстура карты
    map.loadFromImage(map_image);//заряжаем текстуру картинкой
    Sprite s_map;//создаём спрайт для карты
    s_map.setTexture(map);//заливаем текстуру спрайтом




    //"Assets/AnimationSheet_Character.png"
    sf::Clock clock;
    Player player("Assets/AnimationSheet_Character.png",50,50,32,32);
    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time /= 3000;
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        player.update(time, TileMap, view);
        window.setView(view); // обновление камеры


        window.clear(Color(128,106,89));

        GenerateMap(s_map,window,player,time); // Генерация карты
        window.draw(player.sprite);
        window.display();
    }
    return 0;
}
