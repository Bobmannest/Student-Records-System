#include "module.h"

using namespace std;

module::module()
    : credit(""), module_name("") {}

module::module(string c, string mn)
    : credit(c), module_name(mn) {}