#include "../../../include/runtime/instructions/Instruction.hpp"

/** \file Conversions.cpp
 * Referente às instruções definidas em Instruction.hpp do tipo Conversion da Java SE 8 Edition.
 * Instruções do tipo Conversion realizam a conversão de tipos, exemplo: inteiro para double. Elas 
 * são dividas em duas categorias:
 * - Widening numeric conversion instructions: Instruction::i2l, Instruction::i2f, Instruction::i2d, 
 * Instruction::l2f, Instruction::l2d, e Instruction::f2d
 * - Narrowing numeric conversions instructions: Instruction::i2b, Instruction::i2c, Instruction::i2s, 
 * Instruction::l2i, Instruction::f2i, Instruction::f2l, Instruction::d2i, Instruction::d2l, e Instruction::d2f
 */


/**
Instrução i2d: Converte int para double.

Recupera o valor a ser convertido da pilha de operandos do método sendo executado.
O valor é convertido de acordo com a tag definida em Frame.hpp que representa o tipo double.

@param frame Frame correspondente ao método sendo executado.
@returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.
*/
uint32_t Instruction::i2d(Frame* frame) {
    int32_t value = frame->operandStack.top().type_int;
    frame->operandStack.pop();

    Type res;
    res.tag = TAG_DOUBLE;
    res.type_double = (double)value;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

/**
Instrução i2f: Converte int para float.

Recupera o valor a ser convertido da pilha de operandos do método sendo executado.
O valor é convertido de acordo com a tag definida em Frame.hpp que representa o tipo float.

@param frame Frame correspondente ao método sendo executado.
@returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.
*/
uint32_t Instruction::i2f(Frame* frame) {
    int32_t value = frame->operandStack.top().type_int;
    frame->operandStack.pop();

    Type res;
    res.tag = TAG_FLOAT;
    res.type_float = (float)value;

    frame->operandStack.push(res);

    return ++frame->local_pc;
}

/**
Instrução i2l: Converte int para long.

Recupera o valor a ser convertido da pilha de operandos do método sendo executado.
O valor é convertido de acordo com a tag definida em Frame.hpp que representa o tipo int64_t.

@param frame Frame correspondente ao método sendo executado.
@returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.
*/
uint32_t Instruction::i2l(Frame* frame) {
    int32_t value = frame->operandStack.top().type_int;

    frame->operandStack.pop();

    Type res;
    res.tag = TAG_LONG;
    res.type_long = (long)value;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

/**
Instrução i2b: Converte int para byte.

Recupera o valor a ser convertido da pilha de operandos do método sendo executado.
O valor é convertido de acordo com a tag definida em Frame.hpp que representa o tipo int8_t.

@param frame Frame correspondente ao método sendo executado.
@returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.
*/
uint32_t Instruction::i2b(Frame* frame) {
    int32_t value = frame->operandStack.top().type_int;
    frame->operandStack.pop();

    Type res;
    res.tag = TAG_BYTE;
    res.type_byte = (int8_t)value;

    frame->operandStack.push(res);

    return ++frame->local_pc;
}

/**
Instrução i2s: Converte int para short.

Recupera o valor a ser convertido da pilha de operandos do método sendo executado.
O valor é convertido de acordo com a tag definida em Frame.hpp que representa o tipo int16_t.

@param frame Frame correspondente ao método sendo executado.
@returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.
*/
uint32_t Instruction::i2s(Frame* frame) {
    int32_t value = frame->operandStack.top().type_int;
    frame->operandStack.pop();

    Type res;
    res.tag = TAG_SHORT;
    res.type_short = (int16_t)value;

    frame->operandStack.push(res);

    return ++frame->local_pc;
}

/**
Instrução i2c: Converte int para char.

Recupera o valor a ser convertido da pilha de operandos do método sendo executado.
O valor é convertido de acordo com a tag definida em Frame.hpp que representa o tipo uint8_t.

@param frame Frame correspondente ao método sendo executado.
@returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.
*/
uint32_t Instruction::i2c(Frame* frame) {
    int32_t value = frame->operandStack.top().type_int;
    frame->operandStack.pop();

    Type res;
    res.tag = TAG_CHAR;
    res.type_char = (uint8_t)value;

    frame->operandStack.push(res);

    return ++frame->local_pc;
}

/**
Instrução l2i: Converte long para int.

Recupera o valor a ser convertido da pilha de operandos do método sendo executado.
O valor é convertido de acordo com a tag definida em Frame.hpp que representa o tipo int32_t.

@param frame Frame correspondente ao método sendo executado.
@returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.
*/
uint32_t Instruction::l2i(Frame * frame){
    long val1;
    val1 = frame->operandStack.top().type_long;
    frame->operandStack.pop();

    Type res;
    res.tag = TAG_INT;
    res.type_int = (int)val1;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

/**
Instrução l2f: Converte long para float.

Recupera o valor a ser convertido da pilha de operandos do método sendo executado.
O valor é convertido de acordo com a tag definida em Frame.hpp que representa o tipo float.

@param frame Frame correspondente ao método sendo executado.
@returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.
*/
uint32_t Instruction::l2f(Frame * frame){
    long val1;
    val1 = frame->operandStack.top().type_long;
    frame->operandStack.pop();

    Type res;
    res.tag = TAG_FLOAT;
    res.type_float = (float)val1;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

/**
Instrução l2d: Converte long para double.

Recupera o valor a ser convertido da pilha de operandos do método sendo executado.
O valor é convertido de acordo com a tag definida em Frame.hpp que representa o tipo double.

@param frame Frame correspondente ao método sendo executado.
@returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.
*/
uint32_t Instruction::l2d(Frame * frame){
    long val1;
    val1 = frame->operandStack.top().type_long;
    frame->operandStack.pop();

    Type res;
    res.tag = TAG_DOUBLE;
    res.type_double = (double)val1;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

/**
Instrução f2d: Converte float para double.

Recupera o valor a ser convertido da pilha de operandos do método sendo executado.
O valor é convertido de acordo com a tag definida em Frame.hpp que representa o tipo double.

@param frame Frame correspondente ao método sendo executado.
@returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.
*/
uint32_t Instruction::f2d(Frame * frame){
    float val1;
    val1 = frame->operandStack.top().type_float;
    frame->operandStack.pop();

    Type res;
    res.tag = TAG_DOUBLE;
    res.type_double = (double)val1;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

/**
Instrução f2i Converte float para int.

Recupera o valor a ser convertido da pilha de operandos do método sendo executado.
O valor é convertido de acordo com a tag definida em Frame.hpp que representa o tipo int32_t.

@param frame Frame correspondente ao método sendo executado.
@returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.
*/
uint32_t Instruction::f2i(Frame * frame){
    float val1;
    val1 = frame->operandStack.top().type_float;
    frame->operandStack.pop();

    Type res;
    res.tag = TAG_INT;
    res.type_int = (int32_t)val1;

    frame->operandStack.push(res);

    return ++frame->local_pc;
}


/**
Instrução f2l: Converte float para long.

Recupera o valor a ser convertido da pilha de operandos do método sendo executado.
O valor é convertido de acordo com a tag definida em Frame.hpp que representa o tipo int64_t.

@param frame Frame correspondente ao método sendo executado.
@returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.
*/
uint32_t Instruction::f2l(Frame * frame){
    float val1;
    val1 = frame->operandStack.top().type_float;

    frame->operandStack.pop();

    Type res;
    res.tag = TAG_LONG;
    res.type_long = (long)val1;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

/**
Instrução d2f: Converte double para float.

Recupera o valor a ser convertido da pilha de operandos do método sendo executado.
O valor é convertido de acordo com a tag definida em Frame.hpp que representa o tipo float.

@param frame Frame correspondente ao método sendo executado.
@returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.
*/
uint32_t Instruction::d2f(Frame * frame){
    double val1;
    val1 = frame->operandStack.top().type_double;
    frame->operandStack.pop();

    Type res;
    res.tag = TAG_FLOAT;
    res.type_float = (float)val1;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

/**
Instrução d2i: Converte double para int.

Recupera o valor a ser convertido da pilha de operandos do método sendo executado.
O valor é convertido de acordo com a tag definida em Frame.hpp que representa o tipo int32_t.

@param frame Frame correspondente ao método sendo executado.
@returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.
*/
uint32_t Instruction::d2i(Frame * frame){
    double val1;
    val1 = frame->operandStack.top().type_double;
    frame->operandStack.pop();

    Type res;
    res.tag = TAG_INT;
    res.type_int = (int32_t)val1;

    frame->operandStack.push(res);

    return ++frame->local_pc;
}

/**
Instrução d2l: Converte double para long.

Recupera o valor a ser convertido da pilha de operandos do método sendo executado.
O valor é convertido de acordo com a tag definida em Frame.hpp que representa o tipo int64_t.

@param frame Frame correspondente ao método sendo executado.
@returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.
*/
uint32_t Instruction::d2l(Frame * frame){
    double val1;
    val1 = frame->operandStack.top().type_double;
    frame->operandStack.pop();

    Type res;
    res.tag = TAG_LONG;
    res.type_long = (long)val1;;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}
