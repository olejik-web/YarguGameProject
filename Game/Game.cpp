#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <iostream>
#include <cmath>
#include <iomanip>
#include <Windows.h>
#include <SFML/Graphics/Font.hpp>
#include "settings.h"
#include "debug.h"
#include "Level.h"
#include "tile.h"
#include "player.h"
#include "Weapon.h"
#include "enemy.h"

using namespace sf;
using namespace std;

class Game {
private:
    RenderWindow screen;
    Level level;
    Clock clock;
public:
    Game() {
        screen.create(VideoMode(WIDTH, HEIGTH), "Our Game");
        clock.restart();
    }
    void run() {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        while (screen.isOpen()) {
            Event event;
            while (screen.pollEvent(event)) {
                if (event.type == Event::Closed) {
                    screen.close();
                }
            }
            screen.clear(Color::Black);
            level.run(screen, time, clock);
            screen.display();
        }
    }
};

int main()
{
    DebugFont.loadFromFile("Samson.ttf");
    Game game;
    game.run();
    return 0;
}
