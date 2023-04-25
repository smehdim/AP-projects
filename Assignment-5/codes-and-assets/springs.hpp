#ifndef spring_h
#define spring_h

#include <iostream>
#include "rsdl.hpp"
#include "consts.hpp"

class spring {
public:
    spring(int x,int y);
    void display(Window* window, int camera);
    Point get_position();
    void set_strech(bool state);
private:
    Point position;
    bool is_streched = false;
};

#endif