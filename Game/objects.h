#pragma once
#include "head.h"
#include "object.h"

using namespace std;

// Изображения из определённого файла // 

object upper_wall_1("Tileset.png", 1 * 32, 0 * 32, 32, 32, 1);
object upper_wall_2("Tileset.png", 2 * 32, 0 * 32, 32, 32, 1);
object upper_wall_3("Tileset.png", 3 * 32, 0 * 32, 32, 32, 1);
object upper_wall_4("Tileset.png", 4 * 32, 0 * 32, 32, 32, 1);

object lower_wall_1("Tileset.png", 1 * 32, 4 * 32, 32, 32, 1);
object lower_wall_2("Tileset.png", 2 * 32, 4 * 32, 32, 32, 1);
object lower_wall_3("Tileset.png", 3 * 32, 4 * 32, 32, 32, 1);
object lower_wall_4("Tileset.png", 4 * 32, 4 * 32, 32, 32, 1);
object lower_wall_5("Tileset.png", 1 * 32, 5 * 32, 32, 32, 1);
object lower_wall_6("Tileset.png", 2 * 32, 5 * 32, 32, 32, 1);

object wall_angle_in_45_1("Tileset.png", 3 * 32, 5 * 32, 32, 32, 1);
object wall_angle_in_45_2("Tileset.png", 5 * 32, 5 * 32, 32, 32, 1);

object wall_angle_in_135_1("Tileset.png", 0 * 32, 5 * 32, 32, 32, 1);
object wall_angle_in_135_2("Tileset.png", 5 * 32, 4 * 32, 32, 32, 1);

object wall_angle_in_225("Tileset.png", 0 * 32, 4 * 32, 32, 32, 1);
object wall_angle_in_315("Tileset.png", 5 * 32, 4 * 32, 32, 32, 1);

object right_wall_1("Tileset.png", 5 * 32, 0 * 32, 32, 32, 1);
object right_wall_2("Tileset.png", 5 * 32, 1 * 32, 32, 32, 1);
object right_wall_3("Tileset.png", 5 * 32, 2 * 32, 32, 32, 1);
object right_wall_4("Tileset.png", 5 * 32, 3 * 32, 32, 32, 1);

object left_wall_1("Tileset.png", 0 * 32, 0 * 32, 32, 32, 1);
object left_wall_2("Tileset.png", 0 * 32, 1 * 32, 32, 32, 1);
object left_wall_3("Tileset.png", 0 * 32, 2 * 32, 32, 32, 1);
object left_wall_4("Tileset.png", 0 * 32, 3 * 32, 32, 32, 1);

object floor_1("Tileset.png", 2 * 32, 2 * 32, 32, 32);
object floor_2("Tileset.png", 3 * 32, 2 * 32, 32, 32);
object floor_3("Tileset.png", 6 * 32, 0 * 32, 32, 32);
object floor_4("Tileset.png", 7 * 32, 0 * 32, 32, 32);
object floor_5("Tileset.png", 8 * 32, 0 * 32, 32, 32);
object floor_6("Tileset.png", 9 * 32, 0 * 32, 32, 32);
object floor_7("Tileset.png", 6 * 32, 1 * 32, 32, 32);
object floor_8("Tileset.png", 7 * 32, 1 * 32, 32, 32);
object floor_9("Tileset.png", 8 * 32, 1 * 32, 32, 32);
object floor_10("Tileset.png", 9 * 32, 1 * 32, 32, 32);
object floor_11("Tileset.png", 6 * 32, 2 * 32, 32, 32);
object floor_12("Tileset.png", 7 * 32, 2 * 32, 32, 32);
object floor_13("Tileset.png", 8 * 32, 2 * 32, 32, 32);
object floor_14("Tileset.png", 9 * 32, 2 * 32, 32, 32);
object floor_15("Tileset.png", 0 * 32, 7 * 32, 32, 32);
object floor_16("Tileset.png", 1 * 32, 7 * 32, 32, 32);
object floor_17("Tileset.png", 2 * 32, 7 * 32, 32, 32);
object floor_18("Tileset.png", 3 * 32, 7 * 32, 32, 32);

object floor_angle_45("Tileset.png", 4 * 32, 1 * 32, 32, 32);
object floor_angle_135("Tileset.png", 1 * 32, 1 * 32, 32, 32);
object floor_angle_225("Tileset.png", 1 * 32, 3 * 32, 32, 32);
object floor_angle_315("Tileset.png", 4 * 32, 3 * 32, 32, 32);

object floor_angle_0("Tileset.png", 4 * 32, 2 * 32, 32, 32);

object floor_angle_90_1("Tileset.png", 2 * 32, 1 * 32, 32, 32);
object floor_angle_90_2("Tileset.png", 3 * 32, 1 * 32, 32, 32);
object floor_angle_90_3("Tileset.png", 0 * 32, 6 * 32, 32, 32);
object floor_angle_90_4("Tileset.png", 1 * 32, 6 * 32, 32, 32);
object floor_angle_90_5("Tileset.png", 2 * 32, 6 * 32, 32, 32);
object floor_angle_90_6("Tileset.png", 3 * 32, 6 * 32, 32, 32);

object floor_angle_180("Tileset.png", 1 * 32, 2 * 32, 32, 32);

object floor_angle_270_1("Tileset.png", 2 * 32, 3 * 32, 32, 32);
object floor_angle_270_2("Tileset.png", 3 * 32, 3 * 32, 32, 32);

object vertical_closed_left_door("Tileset.png", 7 * 32, 5 * 32, 32, 32, 1);
object vertical_open_left_door("Tileset.png", 7 * 32, 4 * 32, 32, 32);

object vertical_closed_right_door("Tileset.png", 8 * 32, 5 * 32, 32, 32, 1);
object vertical_open_right_door("Tileset.png", 8 * 32, 4 * 32, 32, 32);

object horizontal_closed_left_door("Tileset.png", 6 * 32, 6 * 32, 32, 32);
object horizontal_closed_right_door("Tileset.png", 7 * 32, 6 * 32, 32, 32);

object horizontal_open_left_door_upper("Tileset.png", 7 * 32, 4 * 32, 32, 32, 1);
object horizontal_open_left_door_lower("Tileset.png", 7 * 32, 5 * 32, 32, 32, 1);

object horizontal_open_right_door_upper("Tileset.png", 8 * 32, 4 * 32, 32, 32, 1);
object horizontal_open_right_door_lower("Tileset.png", 8 * 32, 5 * 32, 32, 32, 1);

object upper_barrier("Tileset.png", 6 * 32, 4 * 32, 32, 32, 1);
object lower_barrier("Tileset.png", 6 * 32, 5 * 32, 32, 32, 1);

object left_barrier("Tileset.png", 6 * 32, 3 * 32, 32, 32, 1);
object right_barrier("Tileset.png", 7 * 32, 3 * 32, 32, 32, 1);

object avoid("Tileset.png", 8 * 32, 7 * 32, 32, 32);
object clear("Tileset.png", 12 * 32, 11 * 32, 32, 32);

map<int, object> room_item_id
{
	{0, upper_wall_1},
	{1, upper_wall_2},
	{2, upper_wall_3},
	{3, upper_wall_4},
	{4, lower_wall_1},
	{5, lower_wall_2},
	{6, lower_wall_3},
	{7, lower_wall_4},
	{8, lower_wall_5},
	{9, lower_wall_6},
	{10, wall_angle_in_45_1},
	{11, wall_angle_in_45_2},
	{12, wall_angle_in_135_1},
	{13, wall_angle_in_135_2},
	{14, avoid},
	{16, wall_angle_in_225},
	{17, wall_angle_in_315},
	{18, left_wall_1},
	{19, left_wall_2},
	{20, left_wall_3},
	{21, left_wall_4},
	{22, floor_1},
	{23, floor_2},
	{24, floor_3},
	{25, floor_4},
	{26, floor_5},
	{27, floor_6},
	{28, floor_7},
	{29, floor_8},
	{30, floor_9},
	{31, floor_10},
	{32, floor_11},
	{33, floor_12},
	{34, floor_13},
	{35, floor_14},
	{36, floor_15},
	{37, floor_16},
	{38, floor_17},
	{39, floor_18},
	{40, floor_angle_45},
	{41, floor_angle_135},
	{42, floor_angle_225},
	{43, floor_angle_315},
	{44, floor_angle_0},
	{45, floor_angle_90_1},
	{46, floor_angle_90_2},
	{47, floor_angle_90_3},
	{48, floor_angle_90_4},
	{49, floor_angle_90_5},
	{50, floor_angle_90_6},
	{51, floor_angle_180},
	{52, floor_angle_270_1},
	{53, floor_angle_270_2},
	{54, right_wall_1},
	{55, right_wall_2},
	{56, right_wall_3},
	{57, right_wall_4},
	{58, vertical_closed_left_door},
	{59, vertical_open_left_door},
	{60, vertical_closed_right_door},
	{61, vertical_open_right_door},
	{62, horizontal_open_left_door_upper},
	{63, horizontal_open_left_door_lower},
	{64, horizontal_closed_left_door},
	{65, horizontal_closed_right_door},
	{66, horizontal_open_right_door_upper},
	{67, horizontal_open_right_door_lower},
	{68, clear},
	{69, upper_barrier},
	{70, lower_barrier},
	{71, left_barrier},
	{72, right_barrier}
};