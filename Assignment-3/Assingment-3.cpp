#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <time.h>

using namespace std;

typedef vector<string> raw_map;

const int POSSIBLE_MOVES = 4;
const int row_delta[POSSIBLE_MOVES] = {-1,1,0,0};
const int col_delta[POSSIBLE_MOVES] = {0,0,1,-1};
const int NOT_DEFINED = -1;
const int MEMBER_PIC_SIZE = 40;
const char RED = 'R';
const char BLUE = 'B';
const char EMPETY = 'E';

struct members {
    char color;
    bool satisfied;
    bool place_finded_each_step; 
};
typedef vector<vector<members> > detailed_map;


struct rand_2d_index {
    int rand_row;
    int rand_col;
};

struct input {
    int required_turns = NOT_DEFINED;
    int satisfaction_wanted = 30;
    string filename;
};

int sum(vector<int> vec) {
    int sum = 0;
    for (int i = 0; i < vec.size(); i++)
    {
        sum += vec[i];
    }
    return sum;
}

input procces_input(int count_inputs, char* inputs[]) {
    vector<string> parameters;
    input input;
    if (count_inputs > 1) 
    {
    parameters.assign(inputs + 1, inputs + count_inputs);
    }
    for (int params = 0; params < count_inputs -1; params++)
    {
        if (!strcmp(parameters[params].c_str(),"-s"))
        {
            input.required_turns = stoi(parameters[params + 1]);
        }
        if (!strcmp(parameters[params].c_str(),"-p"))
        {
            input.satisfaction_wanted = stoi(parameters[params+1]);
        }
        if (!strcmp(parameters[params].c_str(),"-f"))
        {
            input.filename = parameters[params + 1];
        }
    }
    return input;
}

raw_map create_map(string map_dir) {    
    ifstream infile;
    string line;
    raw_map map;
	infile.open(map_dir);
        while(!infile.eof())
        {
	        getline(infile,line); 
            map.push_back(line);
        }
    map.pop_back();
    return map;
}

detailed_map create_structured_map(raw_map raw_map) {
    detailed_map structured_map;
    for (int i = 0; i < raw_map.size(); i++)
    {
        structured_map.push_back(vector<members>());
        for (int j = 0; j < raw_map[i].size(); j++)
        {
            structured_map[i].push_back(members());
            structured_map[i][j].color = raw_map[i][j];
        }
    }
    return structured_map;
}

bool off_map(detailed_map map, int row, int col, int move){
    if (row+row_delta[move] < 0 || col+col_delta[move] < 0)
    {
        return true;
    }
    int count_rows = map.size();
    int count_cols = map[0].size();
    if (row+row_delta[move] >= count_rows || col+col_delta[move] >= count_cols)
    {
        return true;
    }
    return false;
}

int is_compatible(detailed_map map,int row, int col, int move){
    if (map[row][col].color == map[row+row_delta[move]][col+col_delta[move]].color)
    {
        return 1;
    }
    if (map[row+row_delta[move]][col+col_delta[move]].color == EMPETY)
    {
        return  1;
    }
    return 0;
}

int cal_satisfaction(detailed_map structured_map, int row, int col) {
    vector<int> compatibility_neighbors;

    for (int move = 0; move < POSSIBLE_MOVES; move++)
    {
        if (!off_map(structured_map, row, col, move))
            {
            int compatibility = is_compatible(structured_map, row, col, move);
            compatibility_neighbors.push_back(compatibility);
            }
    }
    return 100*sum(compatibility_neighbors)/compatibility_neighbors.size();
}

void fill_satisfaction(detailed_map& structured_map,int satisfaction_wanted) {

    int satisfaction_rate;
    for (int i = 0; i < structured_map.size(); i++)
    {
        for (int j = 0; j < structured_map[0].size(); j++)
        {
            satisfaction_rate = cal_satisfaction(structured_map,i,j);
            if (satisfaction_rate >= satisfaction_wanted)
            {
                structured_map[i][j].satisfied = true;
            }
            else
            {
                structured_map[i][j].satisfied = false;
            }
        }
    }
}

bool all_satisfied(detailed_map map) {
    for (int i = 0; i < map.size(); i++)
    {
        for (int j = 0; j < map[0].size(); j++)
        {
            if (map[i][j].satisfied == false && map[i][j].color != EMPETY)
            {
                return  false;
            }
        }   
    }
    return true;
}

rand_2d_index make_guess(detailed_map map,int row,int col) {
    
    vector<rand_2d_index> proper_indexes;
    rand_2d_index rand_index;
    srand(time(NULL));
    
    for (int i = 0; i < map.size(); i++)
    {
        for (int j = 0; j < map[0].size(); j++)
        {
            if (map[i][j].color == EMPETY)
            {
                rand_index.rand_row = i;
                rand_index.rand_col = j;
                proper_indexes.push_back(rand_index);
            }
            else if (map[i][j].satisfied == false && map[i][j].place_finded_each_step == false)
            {
                if (row != i && col != j)
                {
                    rand_index.rand_row = i;
                    rand_index.rand_col = j;
                    proper_indexes.push_back(rand_index);
                }
            }
        }
    }
    if (proper_indexes.size() == 0)
    {
        rand_index.rand_row = NOT_DEFINED;
        rand_index.rand_col = NOT_DEFINED;
        return rand_index;
    }
    rand_index = proper_indexes[rand() % proper_indexes.size()];
    return rand_index;
}

void init_condition_step(detailed_map& map) {
    for (int i = 0; i < map.size(); i++)
    {
        for (int j = 0; j < map[0].size(); j++)
        {
            map[i][j].place_finded_each_step = false;
        }
    }
}

bool is_dest_ok(detailed_map map, int rand_row, int rand_col) {
    if (map[rand_row][rand_col].place_finded_each_step == true && map[rand_row][rand_col].color != EMPETY)
    {
        return false;
    }
    else if (map[rand_row][rand_col].satisfied == true & map[rand_row][rand_col].color != EMPETY)
    {
        return false;
    }
    return true;
}

void update_map(detailed_map& map,int satisfaction_rate) {

    init_condition_step(map);
    rand_2d_index rand_index;

    for (int i = 0; i < map.size(); i++)
    {
        for (int j = 0; j < map[0].size(); j++)
        {
            while (map[i][j].place_finded_each_step == false && map[i][j].color != EMPETY)
            {
                if (map[i][j].satisfied == true )
                {
                    map[i][j].place_finded_each_step = true;
                }
                else if (map[i][j].satisfied == false && map[i][j].color != EMPETY)
                {
                    rand_2d_index rand_index = make_guess(map,i,j);
                    if (rand_index.rand_row == NOT_DEFINED)
                    {
                        break;
                    }
                    if (is_dest_ok(map,rand_index.rand_row,rand_index.rand_col))
                    {
                        char color = map[i][j].color;
                        map[i][j].color = map[rand_index.rand_row][rand_index.rand_col].color;
                        map[rand_index.rand_row][rand_index.rand_col].color = color;

                        map[i][j].place_finded_each_step = true;
                        map[rand_index.rand_row][rand_index.rand_col].place_finded_each_step = true;
                    }    
                }
            }
        }      
    }
    fill_satisfaction(map,satisfaction_rate);
}

void simulation(detailed_map& map, int required_turns, int satisfaction_rate) {
    if (required_turns == NOT_DEFINED)
    {
        while (!all_satisfied(map))
        {
            update_map(map,satisfaction_rate);
        }
    }
    else
    {
        for (int i = 0; i < required_turns; i++)
        {
            update_map(map,satisfaction_rate);
        }
    }
}

int count_unhappy(detailed_map map) {
    int count = 0;
    for (int i = 0; i < map.size(); i++)
    {
        for (int j = 0; j < map[0].size(); j++)
        {
            if (map[i][j].satisfied == false && map[i][j].color != EMPETY)
            {
                count++;
            }
        }
    }
    return count;
}

void print_members(detailed_map map) {
    for (int i = 0; i < map.size(); i++)
    {
        for (int j = 0; j < map[0].size(); j++)
        {
            cout << map[i][j].color;
        }
        cout<< endl;
    }
}

void make_pic(detailed_map map) {
    int map_width = map.size();
    int map_height = map[0].size();
    int map_pixel_width = MEMBER_PIC_SIZE * map_width;
    int map_pixel_height = MEMBER_PIC_SIZE * map_height;
    
    ofstream fout("out.ppm");
    fout << "P3" << map_pixel_height << " " << map_pixel_width << " " << "255\n";

    for (int i = 0; i < map_pixel_width; i++)
    {
        for (int j = 0; j <  map_pixel_height; j++)
        {
            if(map[i/ MEMBER_PIC_SIZE][j/MEMBER_PIC_SIZE].color == RED)
            {
                fout << 255 << " " << 0 << " " << 0 << "  ";
            }
            else if (map[i/MEMBER_PIC_SIZE][j/MEMBER_PIC_SIZE].color == BLUE)
            {
                fout << 0 << " " << 0 << " " << 255 << "  ";
            }
            else
            {    
                fout << 255 << " " << 255 << " " << 255 << "  ";
            }
        }
    }
    fout.close();
}

int main(int argc,char* argv[]) {
    input inputs = procces_input(argc, argv);
    raw_map map = create_map(inputs.filename);
    detailed_map structured_map = create_structured_map(map);
    fill_satisfaction(structured_map, inputs.satisfaction_wanted);
    simulation(structured_map, inputs.required_turns, inputs.satisfaction_wanted);
    cout << count_unhappy(structured_map) << endl;
    print_members(structured_map); 
    make_pic(structured_map);   
    return 0;
}