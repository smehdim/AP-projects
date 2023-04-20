#include <iostream>
#include <vector>

using namespace std;

vector<int> get_input(){
    int count_apartment,last_apartment;
    cin >> count_apartment;
    vector<int> apartments; 
    for (int i = 0; i < count_apartment ; i++){   
        cin >> last_apartment;
        apartments.push_back(last_apartment);
    }
    return apartments;
}

int print_index_tallest(vector<int> apartments, int index =0){
    if (index == apartments.size()-1){
        cout << index + 1 << endl;
        return 0;
    }
    else if (apartments[index] > apartments[index +1]){
        cout << index + 1 << endl;
        return 0;
    }
    else
    {
        print_index_tallest(apartments,index+1);
    }
}


int main (){
    vector<int>apartments = get_input();
    print_index_tallest(apartments);
    return 0;
}