#include <iostream>
#include <vector>
#include <string>

using namespace std;

const bool MOVING = true;
const bool STAYING = false;

void print_OK() {
    cout << "OK" << endl;
}

class station {

public:
    station(string station_name,int taffy_price);
    string get_name(){return name;}
    int get_price(){return taffy_price;}

private:
    string name;
    int taffy_price;
};

station::station(string terminal,int price){
    name = terminal;
    taffy_price = price;
}


class train {
public:
    train(string start_station,string end_station,int travel_time, int cooldown_time);
    void set_id(int train_id){id = train_id;}
    void set_current_station(station* terminal);
    void set_next_station(station* station);

    string get_starting_point(){return start_staion;}
    string get_next_point(){return end_station;}
    int get_id() {return id;}
    bool get_status() {return is_moving;}
    station* get_current_station() {return current_station; }
    station* get_next_station() {return next_station;}

    bool is_proper_to_mount();
    void show_information();
    void advance_time();

private:
    int get_remained_time(){return remained_time;}
    int get_cooldown_time(){return cooldown_time;}
    int get_travel_time(){return travel_time;}
    void start_moving();
    void reach_dest();
    string start_staion;
    string end_station;
    int travel_time;
    int cooldown_time;
    station* current_station;
    station* next_station;
    bool is_moving;
    int remained_time;
    int id;
};


train::train(string starting_point,string end_point, int reaching_time, int staying_time) {
    start_staion = starting_point;
    end_station = end_point;
    travel_time = reaching_time;
    cooldown_time = staying_time;
    is_moving = false;
    remained_time = staying_time;
}

void train::set_current_station(station* terminal) {
    current_station = terminal;
}

void train::set_next_station(station* terminal) {
    next_station = terminal;
}

void train::show_information() {
    cout << "status : ";
    if (is_moving == false)
    {
        cout << "resting" << endl;
    }
    else
    {
        cout << "moving" << endl;
    }
    cout << "estimated remaining time : " << remained_time << endl;
    cout << "next station : " << next_station -> get_name() << endl;
}

void train::reach_dest() {
    station* current = next_station;
    next_station = current_station;
    current_station = current;
    remained_time = cooldown_time;  
    is_moving = !is_moving;
}

void train::start_moving() {

    remained_time = travel_time;
    is_moving = !is_moving;
}

void train::advance_time() {
    if (is_moving)
    {
        if (remained_time > 1)
        {
            remained_time = remained_time -1;
        }
        else if(remained_time <= 1 )
        {
            reach_dest();   
        }
    }
    else
    {       
        if (remained_time > 1)
        {
            remained_time = remained_time -1;
        }
        else if(remained_time <= 1 )
        {
            start_moving();
        }
    }
}

bool train::is_proper_to_mount() {
    bool stayed_enough = get_status() == STAYING && (get_remained_time() != get_cooldown_time()) ;
    bool left_just_now = get_status() == MOVING && (get_remained_time() == get_travel_time()) ;
    return stayed_enough || left_just_now;
}

class person {
public:
    person(int addiction_rate,vector<string> upcoming_stations);
    void set_id(int passenger_id) { id = passenger_id;}
    void set_status(bool status);
    void set_current_station(station* station);

    int get_id() {return id;}
    bool get_status() {return on_train;}
    string get_starting_point() {return upcoming_stations[0];}
    train* get_current_train() {return current_train;}
    station* get_current_station() {return current_station;}

    void reach_next_station();
    void advance_time(vector<train*> trains);
    void show_information();
    bool is_finished();

private:
    void get_in_train(train* train);
    void get_off_train(station* station);
    train* find_proper_train(vector<train*> trains);
    void increase_debt();
    void print_status();
    void print_place();
    int addiction_rate;
    int id;
    int spent;
    vector<string> upcoming_stations;
    bool on_train;
    station* current_station;
    train* current_train;
};

person::person(int rate,vector<string> stations) {
    addiction_rate = rate;
    spent = 0;
    for (int i = 0; i < stations.size(); i++)
    {
        upcoming_stations.push_back(stations[i]);
    }
    on_train = false;
}

void person::set_current_station(station* station) {
    current_station = station;
}

void person::get_in_train(train* train) {
    current_station = nullptr;
    current_train = train;
    on_train = true;
}

void person::set_status(bool status) {
    on_train = status;
}

void person::reach_next_station() {
    upcoming_stations.erase(upcoming_stations.begin());
}

void person::print_status() {
    cout << "status : ";
    if (upcoming_stations.size() == 0 && get_current_train() == nullptr)
    {
        cout << "arrived" << endl;
    }
    else if (on_train == true)
    {
        cout << "on train"<<endl;
    }
    else
    {
        cout << "in station"<<endl;
    }
}

void person::print_place() {
    cout << "current " ;
    if (on_train == true)
    {
        cout << "train " << current_train->get_id() << endl;
    }
    else
    {
        cout << "station " << current_station->get_name() <<endl;
    }
}

void person::show_information() {
    print_status();
    cout << "spent : "<< spent << endl;
    print_place();
}

void person::increase_debt() {
    spent += addiction_rate * current_station->get_price();
}

train* person::find_proper_train(vector<train*> trains) {
    for (int i = 0; i < trains.size(); i++)
    {
        bool is_dest_same = trains[i]-> get_next_station()-> get_name() == upcoming_stations[0] ;
        if ( is_dest_same && trains[i]-> is_proper_to_mount() )
        {
            return trains[i];
        }
    }
    return nullptr;
}

void person::get_off_train(station* terminal) {
    current_station = terminal;
    current_train = nullptr;
    on_train = false;
}

void person::advance_time(vector<train*> trains) {
    if (upcoming_stations.size() == 0 && get_current_train() == nullptr)
    {
        return;
    }
    else if (on_train == false)
    {
        train* proper_train = find_proper_train(trains);
        if (proper_train == nullptr)
        {
            increase_debt();
        }
        else
        {
            get_in_train(proper_train);
        }
    }
    else 
    {
        if (current_train-> get_current_station()-> get_name() == upcoming_stations[0])
        {
            reach_next_station();
            get_off_train(current_train-> get_current_station());
        }
    }
}

bool person::is_finished() {
    return upcoming_stations.size() == 0;
}

class world {

public:
    void add_person(person passenger);
    void add_train(train coupe);
    void add_station(station terminal);

    void show_traveler_info(int id);
    void show_train_info(int id);

    person* find_person(int id);
    station* find_station(string name); 
    train* find_train(int id);
    vector<train*> find_trains_on_station(string name);

    void advance_time(int turns);
    void finish();

private:
    void advance_time_one_unit();
    int passengers_on_train(int train_id);
    void train_initializer(station* curr_station,station* next_station);
    void person_initializer(station* curr_station);
    vector<train> trains;
    vector<person> persons;
    vector<station> stations;
};

int world::passengers_on_train(int id) {
    int count = 0;
    for (int i = 0; i < persons.size(); i++)
    {
        if(persons[i].get_status() == MOVING)
        {
            train* coupe = persons[i].get_current_train();
            if (coupe->get_id() == id)
            {
                count++;
            }
        }
    }
    return count;
}

train* world::find_train(int id) {
    for (int i = 0; i < trains.size(); i++)
    {
        if (trains[i].get_id() == id)
        {
            return &trains[i];
        }
    }
}

station* world::find_station(string name) {
    for (int i = 0; i < stations.size(); i++)
    {
        if(stations[i].get_name() == name)
        {
            return &stations[i];
        }
    }
}

person* world::find_person(int id) {
    for (int i = 0; i < persons.size(); i++)
    {
        if (persons[i].get_id() == id)
        {
            return &persons[i];
        }
    }
}

vector<train*> world::find_trains_on_station(string name) {
    vector<train*> finded_trains;
    for (int i = 0; i < trains.size(); i++)
    {
        if (trains[i].get_status() == STAYING && trains[i].get_current_station()->get_name() == name)
        {
            finded_trains.push_back(&trains[i]);
        }
    }
    return finded_trains;
}

void world::show_train_info(int id) {
    train* coupe  = find_train(id);
    coupe->show_information();
    cout << "passengers count : " << passengers_on_train(id) << endl;
}

void world::show_traveler_info(int id) {
    person* traveler = find_person(id);
    traveler ->show_information();
}

void world::add_station(station terminal) {
    stations.push_back(terminal);
    print_OK();
}

void world::train_initializer(station* curr_station,station* next_station) {
    trains[trains.size() -1].set_current_station(curr_station);
    trains[trains.size() -1].set_next_station(next_station);
    trains[trains.size() -1].set_id(trains.size());
}

void world::add_train(train coupe) {
    trains.push_back(coupe);
    station* stat = find_station(coupe.get_starting_point());
    station* next_point = find_station(coupe.get_next_point());
    train_initializer(stat,next_point);
    print_OK();
}

void world::person_initializer(station* curr_station) {
    persons[persons.size()-1].set_current_station(curr_station);
    persons[persons.size()-1].set_status(STAYING);
    persons[persons.size()-1].set_id(persons.size());
    persons[persons.size()-1].reach_next_station();
}

void world::add_person(person traveler) {
    persons.push_back(traveler);
    station* stat = find_station(traveler.get_starting_point());
    person_initializer(stat);
    print_OK();
}

void world::advance_time_one_unit() {
    for (int i = 0; i < trains.size(); i++)
    {
        trains[i].advance_time();
    }
    for (int i = 0; i < persons.size(); i++)
    {
        if (persons[i].get_current_station() != nullptr)
        {
            vector <train*> coupes = find_trains_on_station(persons[i].get_current_station()->get_name());
            persons[i].advance_time(coupes);
        }
        else
        {
            persons[i].advance_time({nullptr});
        }        
    }    
}

void world::advance_time(int turns) {
    for (int turn = 0; turn < turns; turn++)
    {
        advance_time_one_unit();
    }
    print_OK();
}

void world::finish() {
    for (int i = 0; i < persons.size(); i++)
    {
        while (persons[i].is_finished() != true)
        {
            advance_time_one_unit();
        } 
    }
    print_OK();
}

class command_manager {

public:
    void handle_commands();

private:
    world refrence;
    vector<string> split_input();
    vector<string> make_substring(vector<string> inputs, int start_index, int end_index);
    string line;
};

vector<string> command_manager::split_input() {
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

vector<string> command_manager::make_substring(vector<string> inputs, int start_index, int end_index) {
    vector<string> dest_vec;
    for (int i = start_index; i < end_index; i++)
    {
        dest_vec.push_back(inputs[i]);
    }
    return dest_vec;
}



void command_manager::handle_commands() {   

    getline(cin,line);
    while (line.size() != 0) {
        vector<string> splited_line = split_input();
        if (splited_line[0] == "add_station")
        {
            int taffy_price = stoi(splited_line[2]);
            refrence.add_station(station(splited_line[1], taffy_price));
        }
        else if (splited_line[0] == "add_train")
        {
            refrence.add_train(train(splited_line[1], splited_line[2], stoi(splited_line[3]), stoi(splited_line[4])));
        }
        else if (splited_line[0] == "add_passenger")
        {
            refrence.add_person( person( stoi(splited_line[1]), make_substring(splited_line,2,splited_line.size()) ) );
        }
        else if (splited_line[0] == "show_passenger_info")
        {
            refrence.show_traveler_info(stoi(splited_line[1]));
        }
        else if (splited_line[0] == "show_train_info")
        {
            refrence.show_train_info(stoi(splited_line[1]));
        }
        else if (splited_line[0] == "advance_time")
        {
            refrence.advance_time(stoi(splited_line[1]));
        }
        else if (splited_line[0] == "finish")
        {
            refrence.finish();
        }   
    getline(cin, line);
    }

}



int main() {
    command_manager console;
    console.handle_commands();
}