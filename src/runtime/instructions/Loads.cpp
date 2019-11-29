#include "../../../include/runtime/instructions/Instruction.hpp"

/** \file Loads.cpp
 * Referente às instruções definidas em Instruction.hpp do tipo Load da Java SE 8 Edition.
 * Instruções do tipo Load recuperam valores do vetor de variáveis locais e empilham na pilha de operandos.
 */



/**
Instrução fload: Carrega um valor float.

Recupera um elemento float do vetor de variáveis locais da posição indicada por index.
Index é recuperado do atributo code de codeAttribute definido em AttributeInfo.cpp. 
O valor é empilhado na pilha de operandos.

@param frame Frame correspondente ao método sendo executado.
@returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.
*/
uint32_t Instruction::fload(Frame * frame){
    uint8_t* bytecode = frame->codeAttribute.code;
    uint8_t index = bytecode[++frame->local_pc];

    Type value = frame->localVariables[index];
    frame->operandStack.push(value);

    return ++frame->local_pc;
}

/**
Instrução fload_0: Carrega um valor float.

Do grupo de instruções fload_<n>, recupera um elemento float do vetor de variáveis locais da posição 
indicada por n. 
O valor é empilhado na pilha de operandos.

@param frame Frame correspondente ao método sendo executado.
@returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.
*/
uint32_t Instruction::fload_0(Frame * frame){
    Type value = frame->localVariables[0];
    frame->operandStack.push(value);

    return ++frame->local_pc;
}

/**
Instrução fload_1: Carrega um valor float.

Do grupo de instruções fload_<n>, recupera um elemento float do vetor de variáveis locais da posição 
indicada por n. 
O valor é empilhado na pilha de operandos.

@param frame Frame correspondente ao método sendo executado.
@returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.
*/
uint32_t Instruction::fload_1(Frame * frame){
    Type value = frame->localVariables[1];
    frame->operandStack.push(value);

    return ++frame->local_pc;
}

/**
Instrução fload_2: Carrega um valor float.

Do grupo de instruções fload_<n>, recupera um elemento float do vetor de variáveis locais da posição 
indicada por n. 
O valor é empilhado na pilha de operandos.

@param frame Frame correspondente ao método sendo executado.
@returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.
*/
uint32_t Instruction::fload_2(Frame * frame){
    Type value = frame->localVariables[2];
    frame->operandStack.push(value);

    return ++frame->local_pc;
}

/**
Instrução fload_3: Carrega um valor float.

Do grupo de instruções fload_<n>, recupera um elemento float do vetor de variáveis locais da posição 
indicada por n. 
O valor é empilhado na pilha de operandos.

@param frame Frame correspondente ao método sendo executado.
@returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.
*/
uint32_t Instruction::fload_3(Frame * frame){
    Type value = frame->localVariables[3];
    frame->operandStack.push(value);

    return ++frame->local_pc;
}

/**
Instrução fload: Carrega um valor inteiro.

Recupera um elemento inteiro do vetor de variáveis locais da posição indicada por index.
Index é recuperado do atributo code de codeAttribute definido em AttributeInfo.cpp. 
O valor é empilhado na pilha de operandos.

@param frame Frame correspondente ao método sendo executado.
@returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.
*/
uint32_t Instruction::iload(Frame * frame){
    uint8_t* bytecode = frame->codeAttribute.code;
    uint8_t index = bytecode[++frame->local_pc];

    Type val = frame->localVariables[index];
    frame->operandStack.push(val);

    return ++frame->local_pc;
}

/**
Instrução iload_0: Carrega um valor inteiro.

Do grupo de instruções iload_<n>, recupera um elemento inteiro do vetor de variáveis locais da posição 
indicada por n. 
O valor é empilhado na pilha de operandos.

@param frame Frame correspondente ao método sendo executado.
@returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.
*/
uint32_t Instruction::iload_0(Frame * frame){
    Type val = frame->localVariables[0];
    frame->operandStack.push(val);
    return ++frame->local_pc;
}

/**
Instrução iload_1: Carrega um valor inteiro.

Do grupo de instruções iload_<n>, recupera um elemento inteiro do vetor de variáveis locais da posição 
indicada por n. 
O valor é empilhado na pilha de operandos.

@param frame Frame correspondente ao método sendo executado.
@returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.
*/
uint32_t Instruction::iload_1(Frame * frame){
    Type val = frame->localVariables[1];
    frame->operandStack.push(val);

    return ++frame->local_pc;
}

/**
Instrução iload_2: Carrega um valor inteiro.

Do grupo de instruções iload_<n>, recupera um elemento inteiro do vetor de variáveis locais da posição 
indicada por n. 
O valor é empilhado na pilha de operandos.

@param frame Frame correspondente ao método sendo executado.
@returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.
*/
uint32_t Instruction::iload_2(Frame * frame){
    Type val = frame->localVariables[2];
    frame->operandStack.push(val);

    return ++frame->local_pc;
}

/**
Instrução iload_3: Carrega um valor inteiro.

Do grupo de instruções iload_<n>, recupera um elemento inteiro do vetor de variáveis locais da posição 
indicada por n. 
O valor é empilhado na pilha de operandos.

@param frame Frame correspondente ao método sendo executado.
@returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.
*/
uint32_t Instruction::iload_3(Frame * frame){
    Type val = frame->localVariables[3];
    frame->operandStack.push(val);

    return ++frame->local_pc;
}

/**
Instrução lload: Carrega um valor long.

Recupera um elemento long do vetor de variáveis locais da posição indicada por index.
Index é recuperado do atributo code de codeAttribute definido em AttributeInfo.cpp. 
O valor é empilhado na pilha de operandos.

@param frame Frame correspondente ao método sendo executado.
@returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.
*/
uint32_t Instruction::lload(Frame * frame){
    uint8_t* bytecode = frame->codeAttribute.code;
    uint8_t index = bytecode[++frame->local_pc];

    Type value = frame->localVariables[index];
    frame->operandStack.push(value);

    return ++frame->local_pc;
}

/**
Instrução lload_0: Carrega um valor long.

Do grupo de instruções lload_<n>, recupera um elemento long do vetor de variáveis locais da posição 
indicada por n. 
O valor é empilhado na pilha de operandos.

@param frame Frame correspondente ao método sendo executado.
@returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.
*/
uint32_t Instruction::lload_0(Frame * frame){
    Type val = frame->localVariables[0];
    frame->operandStack.push(val);

    return ++frame->local_pc;
}

/**
Instrução lload_1: Carrega um valor long.

Do grupo de instruções lload_<n>, recupera um elemento long do vetor de variáveis locais da posição 
indicada por n. 
O valor é empilhado na pilha de operandos.

@param frame Frame correspondente ao método sendo executado.
@returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.
*/
uint32_t Instruction::lload_1(Frame * frame){
    Type val = frame->localVariables[1];
    frame->operandStack.push(val);

    return ++frame->local_pc;
}

/**
Instrução lload_2: Carrega um valor long.

Do grupo de instruções lload_<n>, recupera um elemento long do vetor de variáveis locais da posição 
indicada por n. 
O valor é empilhado na pilha de operandos.

@param frame Frame correspondente ao método sendo executado.
@returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.
*/
uint32_t Instruction::lload_2(Frame * frame){
    Type val = frame->localVariables[2];
    frame->operandStack.push(val);

    return ++frame->local_pc;
}

/**
Instrução lload_3: Carrega um valor long.

Do grupo de instruções lload_<n>, recupera um elemento long do vetor de variáveis locais da posição 
indicada por n. 
O valor é empilhado na pilha de operandos.

@param frame Frame correspondente ao método sendo executado.
@returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.
*/
uint32_t Instruction::lload_3(Frame * frame){
    Type val = frame->localVariables[3];
    frame->operandStack.push(val);

    return ++frame->local_pc;
}

/**
Instrução dload: Carrega um valor double.

Recupera um elemento double do vetor de variáveis locais da posição indicada por index.
Index é recuperado do atributo code de codeAttribute definido em AttributeInfo.cpp. 
O valor é empilhado na pilha de operandos.

@param frame Frame correspondente ao método sendo executado.
@returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.
*/
uint32_t Instruction::dload(Frame * frame){
    uint8_t* bytecode = frame->codeAttribute.code;
    uint8_t index = bytecode[++frame->local_pc];

    Type value = frame->localVariables[index];
    frame->operandStack.push(value);

    return ++frame->local_pc;
}

/**
Instrução dload_0: Carrega um valor double.

Do grupo de instruções dload_<n>, recupera um elemento double do vetor de variáveis locais da posição 
indicada por n. 
O valor é empilhado na pilha de operandos.

@param frame Frame correspondente ao método sendo executado.
@returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.
*/
uint32_t Instruction::dload_0(Frame * frame){
    Type val = frame->localVariables[0];
    frame->operandStack.push(val);

    return ++frame->local_pc;
}

/**
Instrução dload_1: Carrega um valor double.

Do grupo de instruções dload_<n>, recupera um elemento double do vetor de variáveis locais da posição 
indicada por n. 
O valor é empilhado na pilha de operandos.

@param frame Frame correspondente ao método sendo executado.
@returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.
*/
uint32_t Instruction::dload_1(Frame * frame){
    Type val = frame->localVariables[1];
    frame->operandStack.push(val);

    return ++frame->local_pc;
}

/**
Instrução dload_2: Carrega um valor double.

Do grupo de instruções dload_<n>, recupera um elemento double do vetor de variáveis locais da posição 
indicada por n. 
O valor é empilhado na pilha de operandos.

@param frame Frame correspondente ao método sendo executado.
@returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.
*/
uint32_t Instruction::dload_2(Frame * frame){
    Type val = frame->localVariables[2];
    frame->operandStack.push(val);

    return ++frame->local_pc;
}

/**
Instrução dload_3: Carrega um valor double.

Do grupo de instruções dload_<n>, recupera um elemento double do vetor de variáveis locais da posição 
indicada por n. 
O valor é empilhado na pilha de operandos.

@param frame Frame correspondente ao método sendo executado.
@returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.
*/
uint32_t Instruction::dload_3(Frame * frame){
    Type val = frame->localVariables[3];
    frame->operandStack.push(val);

    return ++frame->local_pc;
}

/**
Instrução aload_0: Carrega um valor do tipo referência.

Do grupo de instruções aload_<n>, recupera um elemento do tipo referência do vetor de variáveis locais da posição 
indicada por n. 
O valor é empilhado na pilha de operandos.

@param frame Frame correspondente ao método sendo executado.
@returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.
*/
uint32_t Instruction::aload_0(Frame * frame){
    Type val = frame->localVariables[0];
    frame->operandStack.push(val);

    return ++frame->local_pc;
}

/**
Instrução aload_1: Carrega um valor do tipo referência.

Do grupo de instruções aload_<n>, recupera um elemento do tipo referência do vetor de variáveis locais da posição 
indicada por n. 
O valor é empilhado na pilha de operandos.

@param frame Frame correspondente ao método sendo executado.
@returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.
*/
uint32_t Instruction::aload_1(Frame * frame){
    Type val = frame->localVariables[1];
    frame->operandStack.push(val);

    return ++frame->local_pc;
}

/**
Instrução aload_2: Carrega um valor do tipo referência.

Do grupo de instruções aload_<n>, recupera um elemento do tipo referência do vetor de variáveis locais da posição 
indicada por n. 
O valor é empilhado na pilha de operandos.

@param frame Frame correspondente ao método sendo executado.
@returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.
*/
uint32_t Instruction::aload_2(Frame * frame){
    Type val = frame->localVariables[2];
    frame->operandStack.push(val);

    return ++frame->local_pc;
}

/**
Instrução aload_3: Carrega um valor do tipo referência.

Do grupo de instruções aload_<n>, recupera um elemento do tipo referência do vetor de variáveis locais da posição 
indicada por n. 
O valor é empilhado na pilha de operandos.

@param frame Frame correspondente ao método sendo executado.
@returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.
*/
uint32_t Instruction::aload_3(Frame * frame){
    Type val = frame->localVariables[3];
    frame->operandStack.push(val);

    return ++frame->local_pc;
}

/**
Instrução iaload: Carrega um valor do tipo inteiro de um array.

Recupera um elemento do tipo inteiro de um array (que é do tipo referência). Tanto o index quanto  o array
são recuperados da pilha de operandos.
O elemento é empilhado na pilha de operandos.

@param frame Frame correspondente ao método sendo executado.
@returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.
*/
uint32_t Instruction::iaload(Frame * frame){
    int32_t index = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    Type* array = (Type*)frame->operandStack.top().type_reference;
    frame->operandStack.pop();
    Type value;
    value.tag = TAG_INT;
    value.type_int = array[index].type_int;

    frame->operandStack.push(value);

    return ++frame->local_pc;
}

/**
Instrução aaload: Carrega um valor do tipo referência de um array.

Recupera um elemento do tipo referência de um array (que é do tipo referência). Tanto o index quanto  o array
são recuperados da pilha de operandos.
O elemento é empilhado na pilha de operandos.

@param frame Frame correspondente ao método sendo executado.
@returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.
*/
uint32_t Instruction::aaload(Frame * frame){
    Type index, array_ref;
    index = frame->operandStack.top();
    frame->operandStack.pop();
    array_ref = frame->operandStack.top();
    frame->operandStack.pop();

    Type *arr = (Type*)array_ref.type_reference;
    Type res = arr[index.type_int];

    frame->operandStack.push(res);

    return ++frame->local_pc;
}
