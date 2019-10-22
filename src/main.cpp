#include <iostream>
#include "../include/Printer.hpp"
#include "Instructions.hpp"
using namespace std;

int main(int argc, char* argv[]) {
    string file_name;
    string path = "test_examples/";
    // Check the number of parameters
    if (argc == 1) {
      file_name = path + "HelloWorld.class";
    } else if (argc == 2){
      file_name = path + argv[1];
    }

    FILE * fp;

    fp = fopen(file_name.c_str(), "rb");
    if (fp != NULL) {
        ClassFile classFile(fp);
        Printer printer(classFile);
    }
    return 0;
}
