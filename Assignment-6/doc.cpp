#include "doc.hpp"

using namespace std;

bool document::has_same_name(string input_name) {
    return name == input_name;
}

void document::print_tabs(int tab_level) {
    for (int i = 0; i < tab_level; i++)
    {
        cout << "    ";
    }
}

form::form(string name,string contents_) :document(name){
    contents = contents_;
}

void form::add_req_for(document* doc) {
    required_for_docs.push_back(doc);
    return;
}

void form::add_requirement(document* doc) {
    return;
}

void form::show_doc(int req_level) {
    print_tabs(req_level);
    cout << "name: " << name << endl;
    print_tabs(req_level);
    cout << "content: " << contents << endl;
}

void form::proceed_doc() {
    is_proceeded = true;
    for (int i = 0; i < required_for_docs.size(); i++)
    {
        required_for_docs[i]->proceed_doc();
    }   
}

permit::permit(string name,string ceo_name_, string sign_type_,string office_name_,string manager_name_)
    :document(name) {
    manager_name = manager_name_;
    sign_type = sign_type_;
    office_name = office_name_;
    manager_name = manager_name_;
    ceo_name = ceo_name_;
}

void permit::proceed_doc() {
    for (int i = 0; i < requirements.size(); i++)
    {
        if (!requirements[i]->is_doc_proceeded())
        {
            return;
        }
    }
    is_proceeded = true;
    for (int i = 0; i < required_for_docs.size(); i++)
    {
        required_for_docs[i]->proceed_doc();   
    }
}

void permit::add_req_for(document* doc) {
    required_for_docs.push_back(doc);
    return;
}

void permit::add_requirement(document* doc) {
    requirements.push_back(doc);
}

void permit::show_doc(int req_level) {
    print_tabs(req_level);
    cout << "name: " << name << endl;
    print_tabs(req_level);
    cout << "This permit consists of: {" << endl;
    for (int i = 0; i < requirements.size(); i++)
    {
        print_tabs(req_level+1);
        cout << "#" << i+1 << endl;
        requirements[i]->show_doc(req_level+1);
    }
    print_tabs(req_level);
    cout << "}" << endl;
    print_tabs(req_level);
    cout << "signature: ";
    if (sign_type == "o")
    {
        cout << office_name << endl;
    }
    else if (sign_type == "c")
    {
        cout << ceo_name << endl;
    }
    else if (sign_type == "m")
    {
        cout << manager_name << endl;
    }

    return;
}
