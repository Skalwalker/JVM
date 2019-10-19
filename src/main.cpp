#include "../include/Printer.hpp"
#include <iostream>

using namespace std;

int main() {
    FILE * fp;

    fp = fopen("test_examples/InterfaceClass$ClassClass.class", "rb");
    if (fp != NULL) {
        ClassFile classFile(fp);
        Printer printer;
        printer.manualHelloWorld(classFile);
    }
    return 0;
}
