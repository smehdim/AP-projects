#include "office.hpp"

using namespace std;

office::office() {}

vector<string> office::split_string(string source,string delimiter =",") {
    vector<string> substrings;
    size_t pos = 0;
    string token;
    while ((pos = source.find(delimiter)) != string::npos) {
        token = source.substr(0, pos);
        substrings.push_back(token);
        source.erase(0, pos + delimiter.length());
    }
    substrings.push_back(source);
    return substrings;
}

csv_table office::read_csv(string dir) {
    string line;
    ifstream infile(dir.c_str());
    csv_table table;
    while (std::getline(infile, line))
    {
        table.push_back(vector<string>());
        table[table.size()-1] = split_string(line);
    }
    infile.close();
    return table;
}

void office::read_files(string permits_dir, string forms_dir) {
    permits = read_csv(permits_dir);
    forms = read_csv(forms_dir);
}

void office::interpret_csvs() {
    for (int i = 1; i < permits.size(); i++)
    {
        documents.push_back(new permit(permits[i][2],permits[i][5],permits[i][1]
                            ,permits[i][0],permits[i][4]));
    }

    for (int i = 1; i < forms.size(); i++)
    {
        documents.push_back(new form(forms[i][0],forms[i][1]));
    }
}

void office::make_requirements_table() {
    for (int i = 1; i < permits.size(); i++)
    {
        permit_requirements.push_back(vector<string> ());
        permit_requirements[i-1] = split_string(permits[i][3],"-");      
    }
}

document* office::find_doc(string name) {
    for (int i = 0; i < documents.size(); i++)
    {
        if (documents[i]->has_same_name(name))
        {
            return documents[i];        
        }
    }
    return NULL;
}

void office::link_docs() {
    for (int i = 0; i < permit_requirements.size(); i++)
    {
        for (int j = 0; j < permit_requirements[i].size(); j++)
        {
            documents[i]->add_requirement(find_doc(permit_requirements[i][j]));
            find_doc(permit_requirements[i][j])->add_req_for(documents[i]);
        }
    }
}

bool office::is_work_done() {
    return documents[0]->is_doc_proceeded();
}

void office::do_confirm(string name) {
    find_doc(name)->proceed_doc();
}

vector<string> office::get_splited_line() {
    string line;
    getline(cin,line);
    vector<string> substrings;
    size_t pos = 0;
    pos = line.find(" ");
    substrings.push_back(line.substr(0, pos));
    substrings.push_back(line.substr(pos+1,line.length()));
    return substrings;
}

string office::get_confirmed_form_name() {
    vector<string> inputs = get_splited_line();

    if (inputs[0] == "confirm")
    {
        return inputs[1];
    }
}

void office::show_main_permit() {
    documents[0]->show_doc(0);
}

void office::procces_works(string permits_dir, string forms_dir) {
    read_files(permits_dir,forms_dir);
    interpret_csvs();
    make_requirements_table();
    link_docs();
    while (!is_work_done())
    {        
        string name = get_confirmed_form_name();
        do_confirm(name);
    }
    show_main_permit();
}

