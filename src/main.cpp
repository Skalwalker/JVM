#include "../include/ClassFile.hpp"

int main() {
    FILE * fp;

    fp = fopen("../examples/HelloWorld.class", "rb");
    ClassFile classFile(fp);

    return 0;
}
