#include "../../include/execution/ExceptionThrower.hpp"

ExceptionThrower::ExceptionThrower(){
}

void ExceptionThrower::arrayIndexOutOfBounds(uint32_t index) {
    cout << "Exception in thread 'main' java.lang.ArrayIndexOutOfBoundsException: " << index << endl;
    exit(0);
}

void ExceptionThrower::arrayStoreException(uint32_t index) {
    cout << "Exception in thread 'main' java.lang.ArrayStoreException: " << index << endl;
    exit(0);
}


void ExceptionThrower::nullPointerException() {
    cout << "Exception in thread 'main' java.lang.NullPointerException" << endl;
    exit(0);
}

void ExceptionThrower::arithmeticException(uint32_t type) {
    cout << "Exception in thread 'main' java.lang.ArithmeticException:";
    if (type == 0) {
        cout << " / by zero" << endl;
    }
    exit(0);
}

void ExceptionThrower::instructionNotImplemented(uint32_t type) {
    cout << "Exception in thread 'main' no.lawd.instructionNotImplemented:" << endl;
    if (type == 0) {
        cout << "\tThread Related Instruction" << endl;
    }
    exit(0);
}

void ExceptionThrower::negativeArraySizeException() {
    cout << "Exception in thread 'main' java.lang.NegativeArraySizeException" << endl;
    exit(0);
}
