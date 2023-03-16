#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <sstream>
#include <vector>
#include <stack>
#include <vector>
#include "Maps.h";
#include "View.h";
#if defined _WIN32 || defined _WIN64

#include <Windows.h>

int SCREENX = GetSystemMetrics(SM_CXSCREEN);
int SCREENY = GetSystemMetrics(SM_CYSCREEN);

#endif

using namespace std;
using namespace sf;

float TIME;

class FPS
{
public:
    sf::Font font;
    sf::Text text;
	FPS() : mFrame(0), mFps(0) {
        font.loadFromFile("DoomFont.ttf");
        text.setFont(font);
        text.setCharacterSize(34);
        text.setFillColor(sf::Color::Red);
        text.setPosition(SCREENX - 120, 30.f);
	}
	const unsigned int getFPS() const { return mFps; }

private:
	unsigned int mFrame;
	unsigned int mFps;
	sf::Clock mClock;

public:
	void update()
	{
		if(mClock.getElapsedTime().asSeconds() >= 1.f)
		{
			mFps = mFrame;
			mFrame = 0;
			mClock.restart();
		}
		++mFrame;
        ostringstream out_fps;
		out_fps << this->getFPS();
        this->text.setString("FPS: " + out_fps.str());
	}
};

class Player : public sf::Sprite {
public:
    sf::Image image;
    sf::Texture texture;
    int original_scale_x;
    int original_scale_y;
    float CurrentAsset = 0;
    int Health = 5;
    bool isAttack = false;
    bool isRight = true;
    int AttackTime;
    Vector2f vec;
    Player() {
        image.loadFromFile("../Assets/AnimationSheet_Character.png");
        texture.loadFromImage(image);
        this->setTexture(texture);
        this->setTextureRect(sf::IntRect(0, 0, 32, 32));
        this->setPosition(10, 10);
        sf::Vector2f scale = this->getScale();
        original_scale_x = scale.x;
        original_scale_y = scale.y;
        this->setScale(original_scale_x * SCREENX * 0.001,
            original_scale_y * SCREENY * 0.0013);
        vec.x = 0;
        vec.y = 0;
        AttackTime = 0;
    }
    void update(float time) {
        if (Health) {
            if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
                || !sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                    if (!isAttack) {
                        CurrentAsset += 0.05 * time;
                        if (CurrentAsset > 4) { CurrentAsset = 0; }
                        this->setTextureRect(IntRect(32 * int(CurrentAsset) + 32, 64, -32, 32));
                        isRight = false;
                    }
                    vec.x = -1.2;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                    if (!isAttack) {
                        CurrentAsset += 0.05 * time;
                        if (CurrentAsset > 4) { CurrentAsset = 0; }
                        this->setTextureRect(IntRect(32 * int(CurrentAsset), 64, 32, 32));
                        isRight = true;
                    }
                    if (vec.x == 0) vec.x = 1.2;
                    else vec.x = 0;
                }
            }
            if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
                || !sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                    if (isRight && !isAttack) {
                        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                            CurrentAsset += 0.05 * time;
                        }
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
                            && sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                                CurrentAsset += 0.05 * time;
                            }
                        if (CurrentAsset > 4) { CurrentAsset = 0; }
                        this->setTextureRect(IntRect(32 * int(CurrentAsset), 64, 32, 32));
                    }
                    else if (!isAttack) {
                        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                            CurrentAsset += 0.05 * time;
                        }
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
                            && sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                                CurrentAsset += 0.05 * time;
                            }
                        if (CurrentAsset > 4) { CurrentAsset = 0; }
                        this->setTextureRect(IntRect(32 * int(CurrentAsset) + 32, 64, -32, 32));
                    }
                    vec.y = -1.2 * time;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                    if (isRight && !isAttack) {
                        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { CurrentAsset += 0.05 * time; }
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
                            && sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                                CurrentAsset += 0.05 * time;
                            }
                        if (CurrentAsset > 4) { CurrentAsset = 0; }
                        this->setTextureRect(IntRect(32 * int(CurrentAsset), 64, 32, 32));
                    }
                    else if (!isAttack) {
                        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) { CurrentAsset += 0.05 * time; }
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
                            && sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                                CurrentAsset += 0.05 * time;
                            }
                        if (CurrentAsset > 4) { CurrentAsset = 0; }
                        this->setTextureRect(IntRect(32 * int(CurrentAsset) + 32, 64, -32, 32));
                    }
                    if (vec.y == 0) vec.y = 1.2;
                    else vec.y = 0;
                }
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !isAttack && AttackTime <= 0) {
            CurrentAsset = 0;
            isAttack = true;
            AttackTime = 500;
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
                    this->setTextureRect(sf::IntRect(0, 0, 32, 32));
                }
                else {
                    this->setTextureRect(sf::IntRect(32, 0, -32, 32));
                }
            }
        }
        this->move(vec.x * time, vec.y * time);
        vec.x = 0;
        vec.y = 0;
        AttackTime--;
        getplayercoordinateforview(this->getPosition().x, this->getPosition().y);
    }
};

FPS GameFPS;

void GenerateMap(Sprite& s_map,RenderWindow& window) {
    for (int i = 0; i < HEIGHT_MAP; i++) {
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
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREENX, SCREENY), "GameProject");
    sf::Clock clock;
    Player player;
    view.reset(FloatRect(0, 0, SCREENX / 4, SCREENY / 4));
    Image map_image;//объект изображения для карты
    map_image.loadFromFile("../Assets/Kings and Pigs/Sprites/14-TileSets/Terrain (32x32).png");//загружаем файл для карты
    Texture map;//текстура карты
    map.loadFromImage(map_image);//заряжаем текстуру картинкой
    Sprite s_map;//создаём спрайт для карты
    s_map.setTexture(map);//заливаем текстуру спрайтом
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
        player.update(time);
        GameFPS.update();
        window.setView(view); // обновление камеры
        window.clear(Color(128,106,89));
        GenerateMap(s_map, window); // Генерация карты
        window.draw(player);
        window.draw(GameFPS.text);
        window.display();
    }
    return 0;
}
