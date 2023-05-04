#ifndef office_h
#define office_h

#include "doc.hpp"
#include <fstream>
#include <string>

typedef std::vector <std::vector<std::string> > csv_table;

class office {
public:
    office();
    void read_files(std::string permits_dir, std::string forms_dir);
    void interpret_csvs();
    void make_requirements_table();
    void link_docs();
    void do_confirm(std::string name);
    bool is_work_done();
    std::string get_confirmed_form_name();
    void procces_works(std::string permits_dir,std::string forms_dir);
    void show_main_permit();
private:
    std::vector<std::string> get_splited_line();
    document* find_doc(std::string name);
    std::vector <std::string> split_string(std::string source,std::string delimiter);
    csv_table read_csv(std::string dir);
    std::vector <document*> documents;
    csv_table forms;
    csv_table permits;  
    csv_table permit_requirements;
};

#endif