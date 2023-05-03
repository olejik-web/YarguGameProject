#pragma once
#include "head.h"

using namespace std;

class object
{
private:

	string file_name;
	int imageCoordX;
	int imageCoordY;
	int tile_width;
	int tile_height;
	bool collision;
	bool interaction;
	bool reaction_to_the_player;
	long double radius;

public:
	object(string file = "f", int imageCoordX = 1, int imageCoordY = 1, int tile_width = 1, int tile_height = 1,
		bool collision = 0, bool reaction_to_the_player = 0)
	{
		file_name = file;
		this->imageCoordX = imageCoordX;
		this->imageCoordY = imageCoordY;
		this->tile_width = tile_width;
		this->tile_height = tile_height;
		this->collision = collision;
		this->reaction_to_the_player = reaction_to_the_player;
	}

	string getFileName() { return file_name; }
	pair<int, int> getImageCoord() { return pair<int, int>(imageCoordX, imageCoordY); }
	int getTileWidth() { return tile_width; }
	int getTileHeight() { return tile_height; }
	bool getColision() { return collision; }
	bool getInteraction() { return interaction; }
	bool getReactionToThePlayer() { return reaction_to_the_player; }
	long double getRadius() { return radius; };

	void setFileName(string FileName) { file_name = FileName; }
	void setImageCoord(int x, int y) { imageCoordX = x; imageCoordY = y; }
	void setTileWidth(int value) { tile_width = value; }
	void setTileHeight(int value) {tile_height = value; }
	void setColision(bool value) { collision = value; }
	void setInteraction(bool value) { interaction = value; }
	void setReactionToThePlayer(bool value) { reaction_to_the_player = value; }
	void setRadius(long double r) { radius = r; }

	~object()
	{
		file_name.clear();
	}
};
