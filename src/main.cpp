#include "../include/main.hpp"

using namespace std;
void list_dir(string path) {
   struct dirent *entry;
   DIR *dir = opendir(path);

   if (dir == NULL) {
      return;
   }
   while ((entry = readdir(dir)) != NULL) {
       cout << entry->d_name << endl;
   }
   closedir(dir);
}

int main(int argc, char* argv[]) {
    string file_name;
    string path = "test_examples/";
    bool print = false;
    // Check the number of parameters
    if (argc == 1) {
      file_name = path + "HelloWorld.class";
    } else if (argc == 2) {
      file_name = path + argv[1];
    } else if (argc == 3) {
        print = true;
    }

    FILE * fp;

    fp = fopen(file_name.c_str(), "rb");
    if (fp != NULL) {
        if (print) {
            ClassFile classFile(fp);
            Printer printer(classFile);
        } else {
            list_dir(path);
            MethodArea methodArea;
            ClassLoader classLoader;
            classLoader.methodArea = &methodArea;
            classLoader.loadClassFile(classFile);
            InstructionsManager instructionsManager(&classLoader);
            ExecutionEngine executionEngine(classFile, &methodArea, &instructionsManager);
            executionEngine.run();
        }

    }
    return 0;
}
