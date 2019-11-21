#ifndef THREAD_H_INCLUDED
#define THREAD_H_INCLUDED

#include <stack>
#include "Frame.hpp"

using namespace std;

class Thread {
public:
    stack<Frame> framesStack;
    uint32_t pc;
    Thread();
};

#endif
