#include "grade.h"

using namespace std;

grade::grade(
    string sid,
    string t,
    string mc,
    string mk)
    : student_id(sid), term_code(t), module_code(mc), mark(mk) {}