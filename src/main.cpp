#include "../include/main.hpp"

void helpScreen(){
    cout << "====================JVM Grupo 1====================" << endl;
    cout << "Yes LAWD!" << endl << "Coloque o nome do .class que quer rodar, precisa estar dentro da pasta test_examples." << endl;
    cout << "-p Ativa o Exibidor!" << endl;
    cout << "--help Mostra este menu" << endl;
    exit(0);
}

int main(int argc, char* argv[]) {
    string file_name;
    string path = "test_examples/";
    bool printFlag = false;
    // Check the number of parameters

    if (argc == 1) {
        file_name = path + "HelloWorld.class";
    } else if (argc == 2) {
        file_name = path + "HelloWorld.class";
        if(strcmp(argv[1],"--help") == 0) {
            helpScreen();
        } else if(strcmp(argv[1],"-p") == 0) {
            printFlag = true;
        }
    } else if (argc == 3) {
        if(strcmp(argv[1],"--help") == 0) {
            helpScreen();
        } else if(strcmp(argv[1],"-p") == 0) {
            printFlag = true;
            if(strcmp(argv[2],"--help") == 0){
                helpScreen();
            } else {
                file_name = path + argv[2];
            }
        } else {
            file_name = path + argv[1];
            if(strcmp(argv[2],"--help") == 0){
                helpScreen();
            } else if (strcmp(argv[2],"-p") == 0){
                printFlag = true;
            }
        }
    }

    FILE * fp;

    fp = fopen(file_name.c_str(), "rb");
    if (fp != NULL) {
        ClassFile classFile(fp);
        if (printFlag == true){
            Printer printer(classFile);
        }
        MethodArea methodArea;
        ClassLoader classLoader;
        classLoader.methodArea = &methodArea;
        classLoader.loadClassFile(classFile);
        InstructionsManager instructionsManager(&classLoader);
        ExecutionEngine executionEngine(classFile, &methodArea, &instructionsManager);
        executionEngine.run();

    }
    return 0;
}
