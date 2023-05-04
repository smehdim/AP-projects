#ifndef DOC_H
#define DOC_H

#include <iostream>
#include <vector>

class document {
public:
    virtual void show_doc(int req_level) = 0;
    virtual void add_requirement(document* doc) = 0;
    virtual void proceed_doc() = 0;
    void print_tabs(int tab_level);
    bool is_doc_proceeded() {return is_proceeded;}
    document(std::string name_) : name(name_) {}
    bool has_same_name(std::string input_name);
    virtual void add_req_for(document* doc) = 0;

protected:
    std::string name;
    bool is_proceeded = false;
};

class form : public document {
public:
    void add_requirement(document* doc);
    form(std::string name, std::string contents);
    void show_doc(int req_level);
    void proceed_doc();
    void add_req_for(document* docum);
private:
    std::vector <document*> required_for_docs;
    std::string contents;
};

class permit : public document {
public :
    permit(std::string name,std::string ceo_name,std::string sign_type,std::string office_name,
    std::string manager_name);
    void proceed_doc();
    void add_requirement(document* doc);
    void show_doc(int req_level);
    void add_req_for(document* docum);

private:
    std::vector <document*> required_for_docs;
    std::vector <document*> requirements;
    std::string manager_name;
    std::string ceo_name;
    std::string sign_type;
    std::string office_name;
};

#endif