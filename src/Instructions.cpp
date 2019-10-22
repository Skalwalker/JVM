#include "../include/Instructions.hpp"

Instructions::Instructions() {
    string line;
    ifstream myfile ("external_data/opcode_mnemonics.txt");
    if (myfile.is_open()) {
        while ( getline (myfile,line) ) {
          cout << line << '\n';
        }
        myfile.close();
    }
}
