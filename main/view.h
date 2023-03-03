#include <SFML/Graphics.hpp>
using namespace sf;

sf::View view;

void getplayercoordinateforview(float x, float y) { //функция для считывания координат игрока
	view.setCenter(x+16, y+16);
}

