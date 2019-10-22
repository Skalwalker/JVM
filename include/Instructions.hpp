#ifndef __INSTRUCTIONS_H__
#define __INSTRUCTIONS_H__

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <map>

using namespace std;

class Instructions {
public:
    map<uint8_t, string> opcode;
    Instructions();
};

#endif
