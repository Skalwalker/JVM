#include "../include/main.hpp"

string get_path(string arg){
    int i = arg.size();
    while (i >= 0 && arg[i] != '/') {
        i--;
    }
    return arg.substr(0, i);
}

string get_mainfile(string arg){
    int i = arg.size();
    while (i >= 0 && arg[i] != '/') {
        i--;
    }
    return arg.substr(i, (arg.size()-i));
}

int main(int argc, char* argv[]) {
    string file_name;
    bool print = false;
    string mainfile;
    string path;
    FILE * fp;

    // Check the number of parameters
    if (argc == 1) {
        cout << "Número errado de argumentos ./bin/jvm path -e(Ativa exibidor)" << endl;
        exit(0);
    } else if (argc == 3) {
        print = true;
    } else {
        path = get_path(argv[1]);
        mainfile = get_mainfile(argv[1]);
    }


    if (print) {
        fp = fopen((path + mainfile).c_str(), "rb");
        if (fp != NULL) {
            ClassFile classFile(fp);
            Printer printer(classFile);
        }
    } else {
        ClassFile classFile;
        MethodArea methodArea;
        ClassLoader classLoader(path);
        classLoader.methodArea = &methodArea;
        classFile = classLoader.loadClassFile(mainfile);
        InstructionsManager instructionsManager(&classLoader);
        ExecutionEngine executionEngine(classFile, &methodArea, &instructionsManager);
        executionEngine.run();

    }
    return 0;
}
