#ifndef enemy_h
#define enemy_h

#include <iostream>
#include "rsdl.hpp"

class enemy{
public:
    enemy(int x,int y);
    void draw(Window* _window, int camera);
    Point get_position();
private:
    Point position;
};


#endif