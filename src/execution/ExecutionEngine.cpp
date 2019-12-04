#include "../../include/execution/ExecutionEngine.hpp"

ExecutionEngine::ExecutionEngine(ClassFile * classFile, MethodArea * methodArea, InstructionsManager * instructionsManager) {
    vector<CPInfo>constantPool = classFile->getConstantPool();
    //GetInfo aqui resgata o nome da classe
    string mainName = constantPool[classFile->getThisClass()-1].getInfo(constantPool);
    this->methodArea = methodArea;
    this->instructionsManager = instructionsManager;
    this->mainClassFileName = mainName;
    findMainMethod();
}

void ExecutionEngine::findMainMethod() {
    ClassFile * mainClassFile = methodArea->getClassFile(mainClassFileName);
    vector<CPInfo> constantPool = mainClassFile->getConstantPool();
    vector<MethodInfo> methods = mainClassFile->getMethods();
    int i;
    bool foundMain = false;

    for (i = 0; i < mainClassFile->getMethodsCount() && !foundMain; i++) {
        MethodInfo method = methods[i];
        uint16_t nameIndex = method.name_index;
        uint16_t descriptorIndex = method.descriptor_index;
        string name = constantPool[nameIndex-1].getInfo(constantPool);
        string descriptor = constantPool[descriptorIndex-1].getInfo(constantPool);
        // É necessario comparar com o descriptor, pois o método main que inicializa
        // o programa necessita de ter um argumento do tipo string
        if (name.compare("main") == 0 && descriptor.compare("([Ljava/lang/String;)V") == 0) {
            foundMain = true;
            this->mainMethod = method;
        }
    }

    if (!foundMain) {
        printf("Método main não encontrada no arquivo\n");
        exit(0);
    }
}

void ExecutionEngine::run() {
    ClassFile * mainClassFile = methodArea->getClassFile(mainClassFileName);
    vector<CPInfo> constantPool = mainClassFile->getConstantPool();
    Thread thread;
    Frame mainFrame(constantPool, this->mainMethod, &(thread.framesStack));

    thread.framesStack.push(mainFrame);

    while(!thread.framesStack.empty()) {
        Frame* currentFrame = &(thread.framesStack.top());
        uint8_t* bytecode = currentFrame->codeAttribute.code;
        // uint32_t byteCodeLength = currentFrame->codeAttribute.codeLength;
        uint8_t opcode = bytecode[thread.pc];
        Instruction currentInstruction = instructionsManager->opcode[opcode];

        // cout << "Instrucao: " << thread.pc << " " << currentInstruction.mnemonic << " frame: " << currentFrame->method.name << endl;
        thread.pc = currentInstruction.exec(currentFrame);

        if (currentInstruction.mnemonic.compare("return") == 0) {
            thread.framesStack.pop();
            if (!thread.framesStack.empty()) {
                thread.pc = thread.framesStack.top().local_pc;
            }
        }
    }
}
