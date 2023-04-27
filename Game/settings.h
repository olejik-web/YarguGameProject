#pragma once
#include <iostream>
#include <vector>

using namespace std;
using namespace sf;

int WIDTH = 1280;
int HEIGTH = 720;
int FPS = 60;
int TILESIZE = 64;

int BAR_HEIGHT = 20;
int HEALTH_BAR_WIDTH = 200;
int ENERGY_BAR_WIDTH = 140;
int ITEM_BOX_SIZE = 80;
string UI_FONT = "graphics/font/joystix.ttf";
int UI_FONT_SIZE = 18;

// general colors
Color WATER_COLOR(113, 221, 238);
Color UI_BG_COLOR(34, 34, 34);
Color UI_BORDER_COLOR(17, 17, 17);
Color TEXT_COLOR(238, 238, 238);

// ui colors
Color HEALTH_COLOR = Color::Red;
Color ENERGY_COLOR = Color::Blue;
Color UI_BORDER_COLOR_ACTIVE(255, 215, 0);
