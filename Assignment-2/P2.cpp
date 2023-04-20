#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
 
int pow(int x,int n){
	int ans = 1 ;
	if (n ==0)
	{
		return ans;
	}
	else{
		ans = x * pow(x,n-1);
	}
}

int print_numbers(int sofar, int difference, int length){
    
    if (sofar < 10 && sofar > 1){
        print_numbers(sofar -1,difference,length);
    }
    
    int previous = sofar % 10;
    
    if (sofar >= pow(10,length - 1)){
        cout << sofar << endl;
        return 0;
    }
    
    else
    {
        if (previous - difference >=0 ){
            print_numbers(sofar*10 + previous - difference, difference, length);
        }
        if (previous + difference <= 9 && difference != 0){
            print_numbers(sofar*10 + previous + difference, difference, length);
        }
    }
    return 0;
}

void print_wrapper(int difference,int length){
    print_numbers(9,difference,length);   
}

int main(){
    int difference, length;
    cin >> length >> difference;
    print_wrapper(difference,length);
    return 0;
}