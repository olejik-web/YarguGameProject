#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#if defined _WIN32 || defined _WIN64

#include <Windows.h>

int SCREENX = GetSystemMetrics(SM_CXSCREEN);
int SCREENY = GetSystemMetrics(SM_CYSCREEN);

#endif

using namespace std;

class Player : public sf::Sprite {
    public:
        sf::Image image;
        sf::Texture texture;
        int original_scale_x;
        int original_scale_y;
        Player() {
            image.loadFromFile("../Assets/BlueWitch/run.png");
            texture.loadFromImage(image);
            this->setTexture(texture);
            this->setTextureRect(sf::IntRect(0, 0, 31, 32));
            this->setPosition(10, 10);
            sf::Vector2f scale = this->getScale();
            original_scale_x = scale.x;
            original_scale_y = scale.y;
            this->setScale(original_scale_x * SCREENX * 0.005,
                                original_scale_y * SCREENY * 0.0065);
        }
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREENX, SCREENY), "GameProject", sf::Style::Fullscreen);
    // sf::Style::Fullscreen
    // sf::RenderWindow window(sf::VideoMode(800, 600), "GameProject");
    // sf::CircleShape shape(100.f);
    Player player;
    while (window.isOpen())
    {
        sf::Clock clock;
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time /= 1500;
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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            player.move(-300.0*time, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            player.move(300.0*time, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            player.move(0, -300.0*time);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            player.move(0, 300.0*time);
        }
        window.clear();
        window.draw(player);
        window.display();
    }
    return 0;
}
