#ifndef MODULES_H
#define MODULES_H

#include <string>

using namespace std;

class module {
public:
  string credit;
  string module_name;

  module();                                
  module(string c, string mn); 
};

#endif