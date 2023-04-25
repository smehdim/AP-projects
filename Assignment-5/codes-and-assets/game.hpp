#ifndef game_h
#define game_h

#include <iostream>
#include <cmath>
#include <vector>
#include <strings.h>
#include <fstream>
#include <string>
#include "rsdl.hpp"
#include "consts.hpp"
#include "platform.hpp"
#include "enemy.hpp"
#include "doodle.hpp"
#include "springs.hpp"

class game {
public:
    game();
    void read_map();
    void run_game();
    void handle_event();
    void update();
    void end_game();
    void draw();
    void affect_collisions();
    void affect_on_breakables();

private:
    void add_proper_item(std::vector<std::string> params);
    std::vector<std::string> split_string(std::string source);
    void show_point();
    void update_point();
    bool does_coli_springs();
    bool does_coli_platforms();
    bool does_coli_enemy();
    void update_mplatforms();
    void draw_platforms();
    void draw_enemies();
    void draw_springs();
    void show_text(std::string text,Point position,int size);
    void update_camera();
    void draw_background();
    void draw_doodle();
    void update_springs();
    int max_point;
    int camera_y = 0;
    std::vector<platform> platforms;
    std::vector<breakable_platform> b_platforms;
    std::vector<moving_platform> moving_platforms;
    std::vector<enemy> enemies;
    std::vector<spring> springs;
    Window gwindow = Window(SCREEN_WIDTH, SCREEN_HEIGTH, "doodle jump");
    doodle player = doodle(SCREEN_WIDTH/2,START_HEIGHT,&gwindow);
};
#endif