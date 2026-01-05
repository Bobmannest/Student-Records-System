#ifndef GRADE_H
#define GRADE_H

#include <string>

using namespace std;

class grade {
public:
    string student_id;
    string term_code;
    string module_code;
    string mark;

    grade(string sid, string t, string mc, string mk);
};

#endif