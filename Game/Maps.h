#include <SFML\Graphics.hpp>
const int HEIGHT_MAP = 14;//������ ����� ������
const int WIDTH_MAP = 18;//������ ����� ������ 
const int TILE_SIZE = 32;

sf::String TileMap[HEIGHT_MAP] = {
	"000000000000000000",
	"0                0",
	"0                0",
	"0                0",
	"0                0",
	"0                0",
	"0                0",
	"0                0",
	"0                0",
	"0                0",
	"0                0",
	"0                0",
	"0                0",
	"000000000000000000"
};



void ChangeWindows(int x, int y, char z) {
	TileMap[y][x] = z;
}