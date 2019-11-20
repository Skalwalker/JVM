#ifndef EXECUTION_ENGINE_H_INCLUDED
#define EXECUTION_ENGINE_H_INCLUDED

#include <string>
#include "ClassFile.hpp"
// #include "ClassLoader.hpp"
// #include "Heap.hpp"
#include "MethodArea.hpp"
#include "InstructionsManager.hpp"
#include "Thread.hpp"
#include "Frame.hpp"

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
