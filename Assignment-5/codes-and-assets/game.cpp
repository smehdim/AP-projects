#include "game.hpp"

using namespace std;


game::game() {
    player.stop();
    platforms.push_back(platform(SCREEN_WIDTH/2,300));
    moving_platforms.push_back(moving_platform(SCREEN_WIDTH/2,0,&gwindow));
    springs.push_back(spring(SCREEN_WIDTH/2,250));
    b_platforms.push_back(breakable_platform(SCREEN_WIDTH/2 +20,250));
    return;
}


vector<string> game::split_string(string line) {
    vector<string> substrings;
    size_t pos = 0;
    string delimiter = " ";
    string token;
    while ((pos = line.find(delimiter)) != std::string::npos) {
        token = line.substr(0, pos);
        substrings.push_back(token);
        line.erase(0, pos + delimiter.length());
    }
    substrings.push_back(line);
    return substrings;
}

void game::add_proper_item(vector<string> params) {
    if (params[2] == "platform")
    {
        platforms.push_back(platform(SCALE_FACTOR * atoi(params[0].c_str())
                                    ,SCREEN_HEIGTH - atoi(params[1].c_str())));
    }
    else if (params[2] == "mplatform")
    {
        moving_platforms.push_back(moving_platform(SCALE_FACTOR * atoi(params[0].c_str())
                                        ,SCREEN_HEIGTH - atoi(params[1].c_str()),&gwindow));
    }
    else if (params[2] == "bplatform")
    {
        b_platforms.push_back(breakable_platform(SCALE_FACTOR *atoi(params[0].c_str())
                                        ,SCREEN_HEIGTH - atoi(params[1].c_str())));
    }
    else if (params[2] == "enemy")
    {
        enemies.push_back(enemy(SCALE_FACTOR *atoi(params[0].c_str())
                                        ,SCREEN_HEIGTH - atoi(params[1].c_str())));
    }
    else if (params[2] == "spring")
    {
        springs.push_back(spring(SCALE_FACTOR *atoi(params[0].c_str())
                                        ,SCREEN_HEIGTH - atoi(params[1].c_str())));
    }
    
}

void game::read_map() {
    fstream FILE("map.txt");
    string line;
    getline(FILE,line);
    int entity_count = atoi(line.c_str());
    for (int i = 0; i < entity_count; i++)
    {
        getline(FILE,line);
        vector<string> params = split_string(line);
        add_proper_item(params);
    }
    
}

void game::run_game() {
    read_map();
    while (player.get_position().y < SCREEN_HEIGTH - camera_y && !does_coli_enemy())
    {
        handle_event();
        update();
        draw();
    }
    end_game();
}

void game::handle_event() {
	while(gwindow.has_pending_event()) {
		Event e = gwindow.poll_for_event();
		switch(e.get_type()) {
			case Event::EventType::QUIT:
				exit(0);
				break;
			case Event::EventType::KEY_PRESS:
			{
				char pressed_char = e.get_pressed_key();
				if (pressed_char == 'd')
				{
					player.change_velocity(Point(3,0));
				}
				if (pressed_char == 'a')
				{
					player.change_velocity(Point(-3,0));
				}
				break;
			}
			case Event::EventType::KEY_RELEASE:
				player.stop();
				break;
		}
	}
}

void game::draw_background() {
	gwindow.draw_img(root_folder +"background.png",Rectangle(0,0,SCREEN_WIDTH,SCREEN_HEIGTH));
}

void game::draw_springs() {
    for (int i = 0; i < springs.size(); i++)
    {
        springs[i].display(&gwindow,camera_y);
    }
}

void game::draw_enemies() {
    for (int  i = 0; i < enemies.size(); i++)
    {
        enemies[i].draw(&gwindow,camera_y);
    }
}

void game::draw_doodle() {
    player.display(&gwindow,camera_y);
}

void game::show_point() {
    show_text("point :",Point(0,0),20);
    show_text(to_string(max_point),Point(60,0),20);
}

void game::draw_platforms() {
    for (int i = 0; i < platforms.size(); i++)
    {
        platforms[i].draw(&gwindow,camera_y);
    }
    for (int  i = 0; i < b_platforms.size(); i++)
    {
        b_platforms[i].draw(&gwindow,camera_y);
    }
    for (int  i = 0; i < moving_platforms.size(); i++)
    {
        moving_platforms[i].base_draw(&gwindow,camera_y);
    }
}

void game::draw() {
	gwindow.clear();
    draw_background();
    draw_platforms();
    draw_springs();
    draw_enemies();
    draw_doodle();
    show_point();
    gwindow.update_screen();
    delay(35);
}

void game::update_mplatforms() {
    for (int i = 0; i < moving_platforms.size(); i++)
    {
        moving_platforms[i].move();
    }
}

void game::update_camera() {
    if (player.get_position().y + camera_y < gwindow.get_height()/2)
    {
        camera_y = camera_y + gwindow.get_width()/3;
    }
}

void game::update_springs() {
    for (int i = 0; i < springs.size(); i++)
    {
        springs[i].set_strech(false);
    }
}

void game::update() {
    update_springs();
    affect_collisions();
    update_mplatforms();
    affect_on_breakables();
    player.move();
    update_camera();
    update_point();

}

bool game::does_coli_platforms() {
    for (int i = 0; i < platforms.size(); i++)
    {  
        if (platforms[i].get_position().y - player.get_position().y > 3*DOODLE_HEIGHT/5 &&
        platforms[i].get_position().y - player.get_position().y < DOODLE_HEIGHT &&
        abs(platforms[i].get_position().x - player.get_position().x) < 3*PLATFORM_WIDTH/4 && 
        player.get_velocity().y > 0)
        {
            return true;
        }
    }
    for (int i = 0; i < moving_platforms.size(); i++)
    {
        if (moving_platforms[i].get_position().y - player.get_position().y > 3*DOODLE_HEIGHT/5 &&
            moving_platforms[i].get_position().y - player.get_position().y < DOODLE_HEIGHT &&
            abs(moving_platforms[i].get_position().x - player.get_position().x) < 3*PLATFORM_WIDTH/4 &&
            player.get_velocity().y > 0)
        {
            return true;
        }   
    }
    return false;
}

bool game::does_coli_springs() {
    for (int  i = 0; i < springs.size(); i++)
    {
       if (springs[i].get_position().y - player.get_position().y > 3*DOODLE_HEIGHT/5 &&
            springs[i].get_position().y - player.get_position().y < DOODLE_HEIGHT &&
            abs(springs[i].get_position().x - player.get_position().x - SPRING_WIDTH/2) < 3*SPRING_WIDTH/4 &&
            player.get_velocity().y > 0)
        {
            springs[i].set_strech(true);
            return true;
        }
    }
    return false;
    
}

void game::affect_on_breakables() {
    for (int i = 0; i < b_platforms.size(); i++)
    {
        if (b_platforms[i].get_position().y - player.get_position().y > 3*DOODLE_HEIGHT/5 &&
            b_platforms[i].get_position().y - player.get_position().y < DOODLE_HEIGHT &&
            abs(b_platforms[i].get_position().x - player.get_position().x) < 3*PLATFORM_WIDTH/4 && 
            player.get_velocity().y > 0)
        {
            b_platforms[i].set_state(true);
        }
    }
    
}

bool  game::does_coli_enemy() {
    for (int i = 0; i < enemies.size(); i++)
    {
       if (enemies[i].get_position().y - player.get_position().y > 0 &&
            enemies[i].get_position().y - player.get_position().y < DOODLE_HEIGHT &&
            abs(enemies[i].get_position().x - player.get_position().x) < 3*ENEMY_WIDTH/4)
        {
            return true;
        } 
    }
}  

void game::affect_collisions() {
    if (does_coli_platforms())
    {
        player.set_velocity(Point(player.get_velocity().x,-20));
    }
    if (does_coli_springs())
    {
        player.set_velocity(Point(player.get_velocity().x,-28));
    }   
}

void game::update_point() {
    int point = -player.get_position().y + START_HEIGHT;
    if (point > max_point)
    {
        max_point = point;
    }
}

void game::show_text(std::string text,Point position,int size) {
    gwindow.show_text(text,position,RGB(102, 51, 0),"FreeSans.ttf",size);
}

void game::end_game() {
    gwindow.clear();
    draw_background();
    show_text("GAME OVER",Point(70,100),50);
    show_text("YOUR POINT IS :", Point(120, 200),24);
    show_text(to_string(max_point),Point(180,250),40);
    gwindow.update_screen();
	Event e = gwindow.poll_for_event();
    while (e.get_type() !=Event::EventType::KEY_PRESS)
    {
        e = gwindow.poll_for_event();
        delay(15);
    }
}