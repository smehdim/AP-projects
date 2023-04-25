#ifndef doodle_h
#define doodle_h

#include <iostream>
#include "consts.hpp"
#include "rsdl.hpp"

class doodle {
public:
    doodle(int x,int y,Window* window);
    void move();
    void display(Window* Window, int camera);
    void change_velocity(velocity v);
    void stop();
    bool reached_bottom();
    Point get_position();
    Point get_velocity();
    void set_velocity(velocity v);
private:
    void affect_gravity();
    void change_direction();
    void jump();
    void walk();
    bool reach_border(int x);
    Point position;
    velocity vel;
    Window* window;
    bool direction = right;
};

#endif