#include <SFML/Graphics.hpp>
using namespace sf;

sf::View view;

void getplayercoordinateforview(float x, float y) { //������� ��� ���������� ��������� ������
	view.setCenter(x+16, y+16);
}

