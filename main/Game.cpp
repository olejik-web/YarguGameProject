#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <iostream>
#include<Windows.h>

using namespace sf;
using namespace std;

int SCREENX = 1000;
int SCREENY = 600;

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

    Player() {
        image.loadFromFile("Assets/AnimationSheet_Character.png");
        texture.loadFromImage(image);
        this->setTexture(texture);
        this->setTextureRect(sf::IntRect(0, 0, 32, 32));
        this->setPosition(10, 10);
        sf::Vector2f scale = this->getScale();
        original_scale_x = scale.x;
        original_scale_y = scale.y;
        this->setScale(original_scale_x * SCREENX * 0.005,
            original_scale_y * SCREENY * 0.0065);
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
    }
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREENX, SCREENY), "GameProject");
    // sf::Style::Fullscreen
    // sf::RenderWindow window(sf::VideoMode(800, 600), "GameProject");
    // sf::CircleShape shape(100.f);

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

        /*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.close();
        }
        sf::Int32 time_to_sleep = int(1.f / 60) - time;
        if (time_to_sleep > 0) {
            sf::sleep(sf::microseconds(time_to_sleep));
        }*/


        player.update(time);
        window.clear();
        window.draw(player);
        window.display();
    }
    return 0;
}