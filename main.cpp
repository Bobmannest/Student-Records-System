#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>

#include "grade.h"
#include "module.h"

using namespace std;

/* Opens txt files, reads from them using a string stream and seperates the contents into 
elements which are seperated by white space and places them into a 2D vector */
vector<grade> vector_grade_file(string fileName){
    vector<grade> strings;
    int lineNum = 0;
    string line;

    ifstream file(fileName);
    if (file.is_open()){
        while (getline(file, line)){
            stringstream ss(line);
            string item;
            string student_id, term_code, module_code, mark;
            ss >> student_id >> term_code >> module_code >> mark;
            strings.emplace_back(student_id, term_code, module_code, mark);
        }
    } else {
        cout << "Error When Reading File!";
    }

    file.close();
    return strings;
}

// Does the same as the function above but uses a map which points to module objects 
map<string, module> map_modules(string fileName){
    map<string, module> map;
    string line;

    ifstream file(fileName);
    if (file.is_open()){
        while (getline(file, line)){
            stringstream ss(line);
            string module_code;
            ss >> module_code;

            string credit, module_name;
            ss >> credit >> module_name;
            map.emplace(module_code, module(credit, module_name));
        }
    } else {
        cout << "Error When Reading File!";
    }

    file.close();
    return map;
}

/* Unlike the previous 2 functions, this does not need to use classes as each student_id 
key points to a single term_code */
map<string, string> map_requests(string fileName){
    map<string, string> map;
    string line;

    ifstream file(fileName);
    if (file.is_open()){
        while (getline(file, line)){
            stringstream ss(line);
            string key, item;

            ss >> key >> item;
            map.emplace(key, item);
        }
    } else {
        cout << "Error When Reading File!";
    }

    file.close();
    return map;

}

float calculate_avg(int module_and_credit_sum, int credit_sum){
    return (float)module_and_credit_sum / credit_sum;
}

int main(){
    //Enter file names below in the format: "filename.txt"
    vector<grade> grades = vector_grade_file("grades.txt");
    map<string, module> modules = map_modules("modules.txt");
    map<string, string> requests = map_requests("requests.txt");

    string previous_student_id = "";
    string previous_term_code = "";

    bool request_exists;
    bool valid_term_code;
    int overall_credit_and_module = 0;
    int overall_credit = 0;
    int term_credit_and_module = 0;
    int term_credit = 0;

    for (int i=0; i<grades.size(); i++){
        string current_student_id = grades[i].student_id;
        string current_term_code = grades[i].term_code;
        string current_module_code = grades[i].module_code;
        string current_mark = grades[i].mark;

        request_exists = (requests[current_student_id] != "");

        //This is used to ignore terms which must be ignored because another term has been specified in requests
        valid_term_code = (requests[current_student_id] == current_term_code || requests[current_student_id] == "");

        //student_id
        if (current_student_id != previous_student_id){
            cout << "\nStudent ID: " << current_student_id << "\n";
            previous_student_id = current_student_id;
            previous_term_code = "";
            overall_credit_and_module = 0;
            overall_credit = 0;
        }
        
        //term_code
        if (current_term_code != previous_term_code && valid_term_code){
            previous_term_code = current_term_code;
            cout << "  Term " << previous_term_code << ":\n";
            term_credit_and_module = 0;
            term_credit = 0;
        }

        //module_code, module_name, credit, mark
        if (valid_term_code) {
            cout << "    " 
                 << current_module_code << " " 
                 << modules[current_module_code].module_name << " (" 
                 << modules[current_module_code].credit << " credits): " 
                 << current_mark << "\n";

            int current_credit = stoi(modules[current_module_code].credit);
            
            term_credit_and_module += current_credit * stoi(current_mark);
            term_credit += current_credit;
            overall_credit_and_module += current_credit * stoi(current_mark);
            overall_credit += current_credit;
        }

        //Term average
        if (i<grades.size()-1){
            if (valid_term_code && grades[i+1].term_code != current_term_code && previous_term_code != ""){
                cout << "  Term Average: " << fixed << setprecision(2) << 
                calculate_avg(term_credit_and_module, term_credit) << "\n";
            }
        } else {
            cout << "  Term Average: " << fixed << setprecision(2) << 
            calculate_avg(term_credit_and_module, term_credit) << "\n";
        }

        //Overall average
        if (!request_exists){
            if (i<grades.size()-1){
                if (grades[i+1].student_id != current_student_id){
                    cout << "  Overall Average: " << fixed << setprecision(2) << 
                    calculate_avg(overall_credit_and_module, overall_credit) << "\n";
                }
            } else {
                cout << "  Overall Average: " << fixed << setprecision(2) << 
                calculate_avg(overall_credit_and_module, overall_credit) << "\n";
            }
        }
    }
    return 0;
}