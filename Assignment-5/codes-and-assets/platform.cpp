#include "platform.hpp"

platform::platform(int x,int y) {
    position.x = x;
    position.y = y;
}

void platform::draw(Window* _window, int camera) {
    _window->draw_img(game_tiles,Rectangle(position.x,position.y + camera,PLATFORM_WIDTH,PLATFORM_HEIGHT)
                    ,Rectangle(0,0,120,36));
}

Point platform::get_position() {
    return position;
}

breakable_platform::breakable_platform(int x ,int y) : platform(x, y){}

void breakable_platform::draw(Window* _window, int camera) {
    if (!broken)
    {
    _window->draw_img(game_tiles,Rectangle(position.x,position.y + camera,PLATFORM_WIDTH,PLATFORM_HEIGHT)
                        ,Rectangle(0,145,120,36));
    }
}

void breakable_platform::set_state(bool state) {
    broken = state;
}

moving_platform::moving_platform(int x,int y, Window* window) : platform(x,y){
    _window = window;
}

bool moving_platform::reach_border(int x) {
    return (x  < 0 ) || (x + PLATFORM_WIDTH > _window->get_width());
}

void moving_platform::move() {
    int new_x = position.x + v_x;
    if (reach_border(new_x))
    {
        v_x = -v_x;
        position.x = position.x - v_x;
    }
    else
    {
        position.x = new_x;
    }
}

void moving_platform::base_draw(Window* _window, int camera) {
    _window->draw_img(game_tiles,Rectangle(position.x,position.y + camera,PLATFORM_WIDTH,PLATFORM_HEIGHT)
                        ,Rectangle(0,37,120,36));
}
