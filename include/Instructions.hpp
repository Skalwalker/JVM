#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

class Instructions {
public:
    map<uint8_t, string> opcode;
    Instructions();
};
