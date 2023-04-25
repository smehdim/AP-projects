#include "enemy.hpp"
#include "consts.hpp"
enemy::enemy(int x,int y){
    position.x = x;
    position.y = y;
}

void enemy::draw(Window* Window, int camera){
    Window->draw_img(game_tiles,Rectangle(position.x,position.y + camera,ENEMY_WIDTH,ENEMY_HEIGHT),Rectangle(125,0,170,185));

}

Point enemy::get_position() {
    return position;
}