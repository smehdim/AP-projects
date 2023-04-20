#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

typedef vector<vector<int> >  table;

const int POSSIBLE_MOVES = 4;
const int WANTED_LENGTH = 3;
const int ACCESIBLE_DIFFERENCE = 1;
const int NO_PREVIOUS = -1;

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

void print_list(vector<int> list){
    for (int i = 0; i < list.size(); i++){
        cout << list[i]<< " ";
    }
    cout << endl;
}

bool is_off_table(table heights,int row, int col) {
    if (row < 0 || row >= heights.size() || col < 0 || col >= heights[0].size()){
        return true;
    }
    return false;
}

bool previous_same_next(int previous, int next_row, int next_col){
	if (previous == next_row*10 + next_col){
		return true;
	}
	return false;
}

int find_route(table heights,vector<int> route ,int previous,int cur_row, int cur_col){
	if (route.size() == WANTED_LENGTH ){
		print_list(route);
		return 1;
	}

	for (int move = 0; move < POSSIBLE_MOVES; move++){

    	int new_row = cur_row + row_delta[move];
    	int new_col = cur_col + col_delta[move];
		if (previous_same_next(previous, new_row, new_col) || is_off_table(heights,new_row,new_col)){
			continue;
		}
		if (abs(heights[new_row][new_col] - route[route.size()-1]) != ACCESIBLE_DIFFERENCE){
			continue;
		}
		route.push_back(heights[new_row][new_col]);
		if (find_route(heights, route, cur_row*10 + cur_col, new_row, new_col)){
			return 1;
		}
		route.pop_back();
	}
	return 0 ;
}

int  find_route_wrapper(table heights){
	vector<int> route;
	int is_done;
    
	for (int i = 0; i < heights.size(); i++){
    	for (int j = 0; j < heights[0].size(); j++){	
    		
			route.push_back(heights[i][j]);
    		is_done = find_route(heights, route, NO_PREVIOUS, i, j);
    		route.pop_back();
    		if (is_done){
    			return 0;
			}
    	}
    }
    cout << -1 << endl;
    return 0;
}

int main(){
    table heights = get_heights();
    find_route_wrapper(heights);
    return 0;
}