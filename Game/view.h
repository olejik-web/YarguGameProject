#include <SFML/Graphics.hpp>
using namespace sf;

sf::View view;

float coordCameraX = -1;
float coordCameraY = -1;

//функция для считывания координат игрока
void getplayercoordinateforview(float x, float y) {
	coordCameraX = x;
	coordCameraY = y;
	view.setCenter(x, y);
}


// Плавная камера, перемещающаяся за персонажем.
void passiveSmoothCamera(float x, float y, float time, float PersonSize)
{

	x += PersonSize / 2;
	if (abs(x - coordCameraX) > 20)
		coordCameraX += (time / 250 * abs(x - coordCameraX)) * (x - coordCameraX) / abs(x - coordCameraX);
	if (abs(x - coordCameraX) > 200)
		coordCameraX += x - 200 * (x - coordCameraX) / abs(x - coordCameraX);

	y += PersonSize / 2;
	if (abs(y - coordCameraY) > 20)
		coordCameraY += (time/250*abs(y - coordCameraY))*(y - coordCameraY) / abs(y - coordCameraY);
	if (abs(y - coordCameraY) > 200)
		coordCameraY =  y - 200 * (y - coordCameraY) / abs(y - coordCameraY);

	view.setCenter(coordCameraX, coordCameraY);
}

//int x = player.getPlayerCoordinateX();
//int y = player.getPlayerCoordinateY();