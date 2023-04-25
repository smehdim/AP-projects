#include "springs.hpp"

spring::spring(int x,int y) {
    position.x = x;
    position.y = y;
}

void spring::display(Window* window, int camera) {
    if (is_streched == true)
    {
        window->draw_img(game_tiles,Rectangle(position.x,position.y + camera,SPRING_WIDTH_STRECHED,SPRING_HEIGHT_STRECHED)
                                ,Rectangle(805,222,42,120));   
    }
    else
    {
    window->draw_img(game_tiles,Rectangle(position.x,position.y + camera,SPRING_WIDTH,SPRING_HEIGHT*3/2)
                                ,Rectangle(805,160,42,70));
    }
}

Point spring::get_position() {
    return position;
}

void spring::set_strech(bool state) {
    is_streched = state;
}