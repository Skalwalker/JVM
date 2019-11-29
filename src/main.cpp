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

void helpScreen(){
    cout << "====================JVM Grupo 1====================" << endl;
    cout << "Yes LAWD!" << endl << "Coloque o nome do .class que quer rodar, precisa estar dentro da pasta test_examples." << endl;
    cout << "-p Ativa o Exibidor!" << endl;
    cout << "--help Mostra este menu" << endl;
    exit(0);

}

int main(int argc, char* argv[]) {
    string file_name;

    bool print = false;
    string mainfile;
    string path;
    FILE * fp;
    bool printFlag = false;

    // Check the number of parameters

    if (argc == 1) {
        path = get_path(argv[1]);
        mainfile = get_mainfile(argv[1]);
    } else if (argc == 2) {
        if(strcmp(argv[1],"--help") == 0) {
            helpScreen();
        } else if(strcmp(argv[1],"-p") == 0) {
            printFlag = true;
        } else {
            path = get_path(argv[1]);
            mainfile = get_mainfile(argv[1]);
        }
    } else if (argc == 3) {
        if(strcmp(argv[1],"--help") == 0) {
            helpScreen();
        } else if(strcmp(argv[1],"-p") == 0) {
            printFlag = true;
            if(strcmp(argv[2],"--help") == 0){
                helpScreen();
            } else {
                path = get_path(argv[2]);
                mainfile = get_mainfile(argv[2]);
            }
        } else {
            path = get_path(argv[1]);
            mainfile = get_mainfile(argv[1]);
            if(strcmp(argv[2],"--help") == 0){
                helpScreen();
            } else if (strcmp(argv[2],"-p") == 0){
                printFlag = true;
            }
        }
    }


    fp = fopen((path + mainfile).c_str(), "rb");
    if (fp != NULL) {
        ClassFile classFile(fp);
        MethodArea methodArea;
        ClassLoader classLoader(path);
        classLoader.methodArea = &methodArea;
        classFile = classLoader.loadClassFile(mainfile);
        InstructionsManager instructionsManager(&classLoader);
        if (printFlag == true){
            Printer printer(classFile, &instructionsManager);
        }
        ExecutionEngine executionEngine(classFile, &methodArea, &instructionsManager);
        executionEngine.run();

    }
    return 0;
}
