#include "doodle.hpp"

doodle::doodle(int x,int y,Window* _window) {
    position.x = x;
    position.y = y;
    window = _window;
}

void doodle::display(Window* Window, int camera) {
    if (direction == right && vel.y >= 0)
    {
        Window->draw_img(root_folder + "right.png",Rectangle(position.x,position.y +camera,
                        DOODLE_WIDTH,DOODLE_HEIGHT));     
    }
    else if (direction == left && vel.y >= 0)    
    {
        Window->draw_img(root_folder + "left.png",Rectangle(position.x,position.y + camera,
                        DOODLE_WIDTH,DOODLE_HEIGHT));     
    }
    else if (direction == right && vel.y <0)
    {
        Window->draw_img(root_folder + "right_jumping.png",Rectangle(position.x,position.y +camera,
                    DOODLE_WIDTH,DOODLE_HEIGHT));      
    }
    else
    {
        Window->draw_img(root_folder + "left_jumping.png",Rectangle(position.x,position.y +camera,
                    DOODLE_WIDTH,DOODLE_HEIGHT));  
    }   
}

void doodle::jump() {
    position.y = position.y + vel.y;
}

void doodle::set_velocity(velocity v) {
    vel.y = v.y;
    vel.x = v.x;
}

void doodle::change_direction() {
    if (vel.x > 0)
    {
        direction = right;
    }
    else if (vel.x < 0)
    {
        direction = left;
    }
}

void doodle::change_velocity(velocity _v) {
    vel.y = vel.y + _v.y;
    vel.x = vel.x + _v.x;
    change_direction();
}

bool doodle::reach_border(int x) {
    return (x  < 0 ) || (x + PLATFORM_WIDTH > window->get_width());
}

void doodle::walk() {
    int new_x = position.x + vel.x;
    if (reach_border(new_x))
    {
        if (position.x > DOODLE_WIDTH )
        {
            position.x = 0;
        }
        else
        {
            position.x = SCREEN_WIDTH - DOODLE_WIDTH;
        }
    }
    else 
    {
        position.x = new_x;
    }
}

void doodle::stop() {
    vel.x = 0;
}

bool doodle::reached_bottom() {
    return   position.y >= window->get_height() - DOODLE_HEIGHT;
}

void doodle::affect_gravity() {
    vel.y = vel.y + GRAVITY_CONST;
}

void doodle::move() {
    jump();
    walk();
    affect_gravity();
}

Point doodle::get_position() {
    return position;
}

Point doodle::get_velocity() {
    return vel;
}