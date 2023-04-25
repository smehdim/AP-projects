#ifndef consts
#define consts

#include "rsdl.hpp"

const std::string root_folder = "assets/main pictures/";
const std::string game_tiles = "assets/main pictures/game-tiles.png";
const double SCALE_FACTOR = 0.66;
const int SCREEN_WIDTH = 640 * SCALE_FACTOR ;
const int SCREEN_HEIGTH = 1024 * SCALE_FACTOR;
const int PLATFORM_WIDTH = 120 * SCALE_FACTOR ;
const int PLATFORM_HEIGHT = 36 * SCALE_FACTOR;
const int PLATFORM_V_X = 8 ;
const int ENEMY_WIDTH = 136 * SCALE_FACTOR;
const int ENEMY_HEIGHT = 184 * SCALE_FACTOR;
const int DOODLE_WIDTH = 124 * SCALE_FACTOR;
const int DOODLE_HEIGHT = 120 * SCALE_FACTOR;
typedef Point velocity;
const bool right = true;
const bool left = false;
const int SPRING_WIDTH = 56 * SCALE_FACTOR;
const int SPRING_HEIGHT =46 * SCALE_FACTOR;
const int SPRING_WIDTH_STRECHED = 56 * SCALE_FACTOR;
const int SPRING_HEIGHT_STRECHED = 120 * SCALE_FACTOR;
const int GRAVITY_CONST = 1;
const int START_HEIGHT = SCREEN_HEIGTH - 2*DOODLE_HEIGHT;
#endif
