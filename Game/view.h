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

void passiveSmoothCamera(float x, float y, float PersonSize)
{
	x += PersonSize / 2;
	if (abs(x - coordCameraX) > 50)
		coordCameraX = x - 49.99 * (x - coordCameraX) / abs(x - coordCameraX);
	y += PersonSize / 2;
	if (abs(y - coordCameraY) > 50)
		coordCameraY = y - 49.99 * (y - coordCameraY) / abs(y - coordCameraY);
	view.setCenter(coordCameraX, coordCameraY);

	//if (Map.characterInTheRoom(y, x, 32))
	//{
	//	view.setCenter(Map.coordinatesOfTheRoomByPlayer(x, y, 32).first.first +
	//		(Map.coordinatesOfTheRoomByPlayer(x, y, 32).second.first - Map.coordinatesOfTheRoomByPlayer(x, y, 32).first.first) * 0.5,
	//		Map.coordinatesOfTheRoomByPlayer(x, y, 32).first.second +
	//		(-Map.coordinatesOfTheRoomByPlayer(x, y, 32).first.second + Map.coordinatesOfTheRoomByPlayer(x, y, 32).second.second) * 0.5);
	//}
}

//int x = player.getPlayerCoordinateX();
//int y = player.getPlayerCoordinateY();