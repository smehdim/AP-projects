#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

typedef vector<vector<int> > table;

const int POSSIBLE_MOVES = 4;
const int accesible_difference = 1;
const int row_delta[POSSIBLE_MOVES] = {1, -1, 0, 0};
const int col_delta[POSSIBLE_MOVES] = {0, 0, 1, -1};

table get_heights(){
    int rows,cols,input;
    table heights;
    cin >> cols >> rows;
    for (int i = 0; i < rows; i++){
        heights.push_back(vector<int>());
        for (int j = 0; j < cols; j++){
            cin >> input;
            heights[i].push_back(input);
        }    
    }
    return heights;
}

void copy_list(vector<int> source,vector<int>& destination){
    destination.clear();
    for (int i = 0; i < source.size(); i++){
        destination.push_back(source[i]);
    }
}

void print_list(vector<int> list){
    for (int i = 0; i < list.size(); i++){
        cout << list[i]<< " ";
    }
    cout << endl;
}

bool is_passed(vector<int> route, int row, int col){
    if (route.size() == 0){
        return false;
    }
    else
    {
        for (int i = 0; i < route.size(); i++){
            if (route[i] == row*10 + col){
                return true;
            }    
        }
    }
    return false;
}

bool is_off_table(table heights,int row, int col){
    if (row < 0 || row >= heights.size() || col < 0 || col >= heights[0].size()){
        return true;
    }
    return false;
}

bool room_available(table heights, int cur_row, int cur_col, vector<int> passed_route){
    for (int move = 0; move < POSSIBLE_MOVES; move++){

        int new_row = cur_row + row_delta[move];
        int new_col = cur_col + col_delta[move];
        bool flag =false;
		if (is_passed(passed_route, new_row, new_col)){
			continue;
		}
        if (is_off_table(heights,new_row,new_col)){
            continue;
		}
        
        int last_apartment_height = heights[passed_route[passed_route.size()-1]/10][passed_route[passed_route.size()-1]%10];
        if (abs(heights[new_row][new_col] - last_apartment_height) != accesible_difference){
            continue;
        }
        return true;
    }
    return false;
}

void find_longest_each(table heights, vector<int> route,vector<int>& longest_found,
                                            vector<int> passed_route, int cur_row, int cur_col){
    
    if (!room_available(heights,cur_row,cur_col,passed_route)){
        if (route.size() > longest_found.size()){
            copy_list(route,longest_found);
        }
    }
    
    else
    {
        for (int move = 0; move < POSSIBLE_MOVES; move++){
         	int new_row = cur_row + row_delta[move];
    	    int new_col = cur_col + col_delta[move];
        	
            if (is_passed(passed_route, new_row, new_col) || is_off_table(heights, new_row, new_col)){
			    continue;
		    }
            bool is_jump_possible = (abs(heights[new_row][new_col] - route[route.size()-1]) == accesible_difference);
            
            if (!is_jump_possible){
                continue;
            }
            
            route.push_back(heights[new_row][new_col]);
            passed_route.push_back(new_row*10 + new_col);

            find_longest_each(heights,route, longest_found, passed_route, new_row, new_col);

            passed_route.pop_back();
            route.pop_back();
        }        
    }
}

vector<int> find_longest_all(table heights){
    vector<int> longest_route;

    for (int i = 0; i < heights.size(); i++)
    {
        for (int j = 0; j < heights[0].size(); j++){
            vector<int> route = { heights[i][j] };
            vector<int> passed_route ={i*10 + j};
            find_longest_each(heights,route,longest_route,passed_route,i,j);
        }    
    }
    return longest_route;
}

int main(){
    table input = get_heights();
    vector<int> longest_route = find_longest_all(input);
    print_list(longest_route);
    return 0;
}