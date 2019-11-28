#ifndef EXCEPTION_THROWER_H_INCLUDED
#define EXCEPTION_THROWER_H_INCLUDED

#include <inttypes.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

class ExceptionThrower {
public:
    ExceptionThrower();
    static void arrayStoreException(uint32_t index);
    static void arrayIndexOutOfBounds(uint32_t index);
    static void nullPointerException();
    static void arithmeticException(uint32_t type);
};


#endif
