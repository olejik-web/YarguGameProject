#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <sstream>
#include <vector>
#include <stack>
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
    Player() {
        image.loadFromFile("../Assets/AnimationSheet_Character.png");
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
                    this->setTextureRect(sf::IntRect(0, 0, 32, 32));
                }
                else {
                    this->setTextureRect(sf::IntRect(32, 0, -32, 32));
                }
            }
        }
    }
};

FPS GameFPS;

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
        }
        player.update(time);
        GameFPS.update();
        window.clear();
        window.draw(player);
        window.draw(GameFPS.text);
        window.display();
    }
    return 0;
}
