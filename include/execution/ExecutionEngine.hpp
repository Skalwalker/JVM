#ifndef EXECUTION_ENGINE_H_INCLUDED
#define EXECUTION_ENGINE_H_INCLUDED

#include <string>
#include "../models/ClassFile.hpp"
#include "../runtime/MethodArea.hpp"
#include "../runtime/InstructionsManager.hpp"
#include "../runtime/Thread.hpp"
#include "../runtime/Frame.hpp"

class ExecutionEngine {
public:
    string mainClassFileName;
    InstructionsManager * instructionsManager;
    MethodInfo mainMethod;
    MethodArea * methodArea;
    ExecutionEngine(ClassFile, MethodArea*, InstructionsManager*);
    void findMainMethod();
    void executeInstruction(uint8_t, uint32_t, Frame);
    void run();
};

#endif
