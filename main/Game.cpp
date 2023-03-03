#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <iostream>
#include<Windows.h>
#include "Maps.h";
#include "View.h";

using namespace sf;
using namespace std;

int SCREENX = 1000;
int SCREENY = 600;

class Player : public sf::Sprite {
public:
    int x = 50, y = 50;
    sf::Image image;
    sf::Texture texture;
    int original_scale_x;
    int original_scale_y;
    float CurrentAsset = 0;
    int Health = 5;

    bool isAttack = false;
    bool isRight = true;

    Player() {
        image.loadFromFile("Assets/AnimationSheet_Character.png");
        texture.loadFromImage(image);
        this->setTexture(texture);
        this->setTextureRect(sf::IntRect(0, 0, 32, 32));
        this->setPosition(x, y);
        sf::Vector2f scale = this->getScale();
        original_scale_x = scale.x;
        original_scale_y = scale.y;
        /*this->setScale(original_scale_x * SCREENX * 0.005,
            original_scale_y * SCREENY * 0.0065);*/
    }



    void update(float time) {
        if (!isAttack && Health) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                CurrentAsset += 0.05 * time;
                if (CurrentAsset > 4) { CurrentAsset = 0; }
                this->setTextureRect(IntRect(32 * int(CurrentAsset) + 32, 64, -32, 32));
                this->move(-1.2 * time, 0);
                isRight = false;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                CurrentAsset += 0.05 * time;
                if (CurrentAsset > 4) { CurrentAsset = 0; }
                this->setTextureRect(IntRect(32 * int(CurrentAsset), 64, 32, 32));
                this->move(1.2 * time, 0);
                isRight = true;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                if (isRight) {
                    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { CurrentAsset += 0.05 * time; }
                    if (CurrentAsset > 4) { CurrentAsset = 0; }
                    this->setTextureRect(IntRect(32 * int(CurrentAsset), 64, 32, 32));
                }
                else {
                    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) { CurrentAsset += 0.05 * time; }
                    if (CurrentAsset > 4) { CurrentAsset = 0; }
                    this->setTextureRect(IntRect(32 * int(CurrentAsset) + 32, 64, -32, 32));
                }
                this->move(0, -1.2 * time);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                if (isRight) {
                    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { CurrentAsset += 0.05 * time; }
                    if (CurrentAsset > 4) { CurrentAsset = 0; }
                    this->setTextureRect(IntRect(32 * int(CurrentAsset), 64, 32, 32));
                }
                else {
                    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) { CurrentAsset += 0.05 * time; }
                    if (CurrentAsset > 4) { CurrentAsset = 0; }
                    this->setTextureRect(IntRect(32 * int(CurrentAsset) + 32, 64, -32, 32));
                }
                this->move(0, 1.2 * time);
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !isAttack) {
            CurrentAsset = 0;
            isAttack = true;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            Health = 0;
        }

        if (!Health) {
            CurrentAsset += 0.01 * time;
            if (isRight) {
                this->setTextureRect(IntRect(32 * int(CurrentAsset), 224, 32, 32));
            }
            else {
                this->setTextureRect(IntRect(32 * int(CurrentAsset) + 32, 224, -32, 32));
            }
            if (CurrentAsset > 7) {
                cout << "Die";
                CurrentAsset = 0;
                Health = -1;
            }
        }

        if (isAttack) {
            CurrentAsset += 0.06 * time;
            if (isRight) {
                this->setTextureRect(IntRect(32 * int(CurrentAsset), 256, 32, 32));
            }
            else {
                this->setTextureRect(IntRect(32 * int(CurrentAsset) + 32, 256, -32, 32));
            }
            if (CurrentAsset > 7) {
                isAttack = false;
                CurrentAsset = 0;
                if (isRight) {
                    this->setTextureRect(sf::IntRect(0, 0, 32, 32));;
                }
                else {
                    this->setTextureRect(sf::IntRect(32, 0, -32, 32));;
                }
            }
        }

        //y = this->getPosition().y;
        //x = this->getPosition().x;
        getplayercoordinateforview(this->getPosition().x, this->getPosition().y);
    }
};


void GenerateMap(Sprite& s_map,RenderWindow& window) {
    for (int i = 0; i < HEIGHT_MAP; i++)
        for (int j = 0; j < WIDTH_MAP; j++)
        {
            if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(64, 224, 32, 32)); //если встретили символ пробел, то рисуем 1й квадратик
            if (TileMap[i][j] == 's')  s_map.setTextureRect(IntRect(160, 160, 32, 32));//если встретили символ s, то рисуем 2й квадратик
            if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(160, 160, 32, 32));//если встретили символ 0, то рисуем 3й квадратик

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





    sf::Clock clock;
    Player player;
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
            if (event.type == sf::Event::Resized) {
                // player.setScale(player.original_scale_x * event.size.width * 0.01,
                                // player.original_scale_y * event.size.height * 0.01);
            }
        } 


        player.update(time);

        window.setView(view); // обновление камеры


        window.clear(Color(128,106,89));

        GenerateMap(s_map,window); // Генерация карты
        window.draw(player);
        window.display();
    }
    return 0;
}