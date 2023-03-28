#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <time.h>
#include <stdlib.h>
#include <algorithm>

using namespace std;

const int STD_COUNT_PER_GROUP = 3;
const int NOT_RESERVED = -1;

vector<vector<string> > get_ids(int count_groups){
    string student_id;
    vector<vector<string> > groups;
   for (int i = 0; i < count_groups; i++)
    {
        groups.push_back(vector<string>());
        for (int j = 0; j < STD_COUNT_PER_GROUP; j++)
        {
            cin >> student_id;
            groups[i].push_back(student_id);
        }
    }
    return groups;
}

vector<vector <int> > make_src_index(int count_groups){
    vector<vector <int> > indexes;
    int count_students = count_groups * STD_COUNT_PER_GROUP;
    for (int i = 0; i < count_students; i++)
    {
        indexes.push_back(vector<int>());
        indexes[i].push_back(i / STD_COUNT_PER_GROUP);
        indexes[i].push_back(i % STD_COUNT_PER_GROUP);
    }
    return indexes;
}

bool does_same_group_pres(vector<vector<int> > homework_slots,int group){
    bool is_pres_by_group = false;
    for (int i = 0; i < homework_slots.size(); i++)
    {
        if (homework_slots[i][0] == group)
        {
            is_pres_by_group = true;
        }              
    }
    return is_pres_by_group;
}

vector<vector<int> > find_empty_slot(vector<vector<vector<int> > > incomplete_list){
    vector<vector<int> > incompletes;
    int count_hws = incomplete_list.size();
    int count_slots = incomplete_list[0].size();
    for (int i = 0; i < count_hws; i++)
    {
        for (int j = 0; j < count_slots; j++)
        {
            if (incomplete_list[i][j][0] == NOT_RESERVED)
            {
                incompletes.push_back(vector<int>());
                incompletes[incompletes.size()-1].push_back(i);
                incompletes[incompletes.size()-1].push_back(j);
            } 
        }
    }
    return incompletes;
}

bool does_reserved_completly(vector<vector<int> > hw_slots){
    bool does_reserved = true;
    int group;
    for (int i = 0; i < hw_slots.size(); i++)
    {
        group = hw_slots[i][0];
        if (group == NOT_RESERVED )
        {
            does_reserved = false;
        }    
    }
    return does_reserved;
}

bool is_special_case(vector<vector<vector<int> > > incomplete_index, vector<int> last_student){
    bool is_special = false;
    int last_std_group = last_student[0];
    int available_hws =0;
    bool is_available ;
    for (int i = 0; i < incomplete_index.size(); i++)
    {
        is_available = !does_same_group_pres(incomplete_index[i],last_std_group) & 
                        !does_reserved_completly(incomplete_index[i]);
        if (is_available)
        {
            available_hws +=1;
        }    
    }
    if (available_hws == 0)
    {
        is_special = true;
    }
    return is_special;
}

vector<vector<vector<int> > > make_index(int count_slots ,int count_hws ,
                                            vector<vector <int> > students){
    
    bool special_case = false;
    vector<vector<vector<int> > > index(count_hws, 
                                vector<vector<int> >(count_slots, vector<int>(2, NOT_RESERVED)));
    vector<vector<vector<int> > > index_original = index;
    vector<vector<int> >  students_original = students;
    srand(time(NULL));

    while (students.size() > 0)
    {   
        special_case = is_special_case(index,students[students.size()-1]);
        if (special_case)
        {
            index = index_original;
            students = students_original;
            special_case = true;
        }
        vector<int> student = students[students.size()- 1];
        int student_grp = student[0];
        int student_std = student[1];
        bool time_found = false;

        while (!time_found)
        {
            int random_hw = rand() % count_hws;
            int available_slot;
            bool is_pres_by_group = does_same_group_pres(index[random_hw],student_grp);
            bool is_there_empty_slot =false;
                        
            for (int i = 0; i < count_slots; i++)
            {
                if (index[random_hw][i][1] == NOT_RESERVED)
                {
                    is_there_empty_slot = true ;
                    available_slot = i;
                }    
            }
            if (!is_pres_by_group & is_there_empty_slot)
            {
                time_found = true;
                index[random_hw][available_slot][0] = student_grp;
                index[random_hw][available_slot][1] = student_std;
                students.pop_back();
            }
        }
    }
    return index;
}

void comlete_index(int count_group, vector<vector<vector<int> > >& incomplete_list){
    vector<vector<int> > empty_slots = find_empty_slot(incomplete_list);
    srand(time(NULL));
    bool proper_group_finded ;
    int rand_group, rand_person, empty_slots_group, empty_slots_std;
    for (int i = 0; i < empty_slots.size();i++)
    {   
        empty_slots_group = empty_slots[i][0];
        empty_slots_std = empty_slots[i][1];
        proper_group_finded=false;
        while(!proper_group_finded)
        {
            rand_group = rand() % count_group;
            if (!does_same_group_pres(incomplete_list[empty_slots_group],rand_group))
            {
                proper_group_finded = true;
                rand_person = rand() % STD_COUNT_PER_GROUP;
                incomplete_list[empty_slots_group][empty_slots_std][0] = rand_group;
                incomplete_list[empty_slots_group][empty_slots_std][1] = rand_person;
            }
            
        }
    }
}

void print_resaults(vector<vector<string> > ids, 
                    vector<vector<vector<int> > > presenter_of_slot)
{
    vector <int> index;
    int count_hws = presenter_of_slot.size();
    int count_slots = presenter_of_slot[0].size();
    for (int i = 0; i < count_hws; i++)
    {
        for (int j = 0; j < count_slots; j++)
        {   
            index = presenter_of_slot[i][j];
            cout << ids[index[0]][index[1]] << "  ";
        }
        cout << '\n';
    }
}

int main() {
    int count_groups, count_hw, count_slot;
    cin >> count_groups >> count_hw >> count_slot;
    vector<vector<string> > ids = get_ids(count_groups);
    vector<vector <int> > src_index = make_src_index(count_groups);
    vector<vector<vector<int> > > index_vec = make_index(count_slot,count_hw,src_index);
    comlete_index(count_groups,index_vec);
    print_resaults(ids,index_vec);
    return 0;
}