#ifndef platform_hpp
#define platform_hpp 

#include <iostream>
#include "rsdl.hpp"
#include "consts.hpp"

class platform {
public:
    platform(int x,int y);
    void draw(Window* _window, int camera);
    Point get_position();
protected:
    Point position;
};

class breakable_platform : public platform {
public:
    breakable_platform(int x,int y);
    void draw(Window* _window, int camera);
    void set_state(bool state);
private:
    bool broken = false;
};

class moving_platform : public platform {
public:
    moving_platform(int x,int y,  Window* _window);
    void move();
    void base_draw(Window* _window, int camera);
private:
    bool reach_border(int x);
    Window* _window;
    int v_x = PLATFORM_V_X;
};

#endif