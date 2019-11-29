#include "../../../include/runtime/instructions/Instruction.hpp"

/** \file Math.cpp
 * Referente às instruções definidas em Instruction.hpp do tipo Math da Java SE 8 Edition.
 * Instruções do tipo Math realizam operações aritméticas de tipos definidos.
 */

/**
Instrução iadd: Soma inteiros.

Recupera os valores a serem somados da pilha de operandos do método sendo executado.
O resultado da soma é empilhado na pilha de operandos.

@param frame Frame correspondente ao método sendo executado.
@returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.
*/
uint32_t Instruction::iadd(Frame * frame) {
    int32_t val1, val2;
    Type res;
    val2 = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    val1 = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    res.tag = TAG_INT;
    res.type_int = val1 + val2;
    frame->operandStack.push(res);
    
    return ++frame->local_pc;
}

/**
Instrução isub: Subtrai inteiros.

Recupera os valores a serem somados da pilha de operandos do método sendo executado.
O resultado da subtração é empilhado na pilha de operandos.

@param frame Frame correspondente ao método sendo executado.
@returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.
*/
uint32_t Instruction::isub(Frame * frame) {
    int32_t val1, val2;
    Type res;
    val2 = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    val1 = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    res.tag = TAG_INT;
    res.type_int = val1 - val2;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

/**
Instrução imul: Multiplica inteiros.

Recupera os valores a serem multiplicados da pilha de operandos do método sendo executado.
O resultado da multiplicação é empilhado na pilha de operandos.

@param frame Frame correspondente ao método sendo executado.
@returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.
*/
uint32_t Instruction::imul(Frame * frame) {
    int32_t val1, val2;
    Type res;
    val2 = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    val1 = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    res.tag = TAG_INT;
    res.type_int = val1 * val2;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

/**
Instrução idiv: Divide inteiros.

Recupera os valores a serem divididos da pilha de operandos do método sendo executado.
O resultado da divisão é empilhado na pilha de operandos. Checa se o divisor é 0.

@param frame Frame correspondente ao método sendo executado.
@returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.
*/
uint32_t Instruction::idiv(Frame * frame) {
    int32_t val1, val2;
    Type res;
    val2 = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    val1 = frame->operandStack.top().type_int;
    frame->operandStack.pop();

    if(val2 == 0) {
        printf("TODO\n");
    } else {
        res.tag = TAG_INT;
        res.type_int = val1 / val2;
        frame->operandStack.push(res);
    }

    return ++frame->local_pc;
}

/**
Instrução irem: Resto de divisão de inteiros.

Recupera os valores a serem divididos da pilha de operandos do método sendo executado.
O resto da divisão (value1 - (value1 / value2) * value2) é empilhado na pilha de operandos. Checa se o divisor é 0.

@param frame Frame correspondente ao método sendo executado.
@returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.
*/
uint32_t Instruction::irem(Frame * frame) {
    int32_t val1, val2;
    Type res;
    val2 = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    val1 = frame->operandStack.top().type_int;
    frame->operandStack.pop();

    if(val2 == 0) {
        printf("TODO\n");
    } else {
        res.tag = TAG_INT;
        res.type_int = val1 % val2;
        frame->operandStack.push(res);
    }

    return ++frame->local_pc;
}

/**
Instrução ineg: Torna número inteiro negativo.

Recupera o valor a ser trocado para o seu negativo da pilha de operandos do método sendo executado.
O número negativo é empilhado na pilha de operandos.

@param frame Frame correspondente ao método sendo executado.
@returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.
*/
uint32_t Instruction::ineg(Frame * frame) {
    int32_t val1;
    Type res;
    val1 = frame->operandStack.top().type_int;
    frame->operandStack.top();
    res.tag = TAG_INT;
    res.type_int = -val1;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

/**
Instrução ishl: Desloca s bits para esquerda de inteiro.

Recupera o valor a ser deslocado e o valor de s bits (s = 5 últimos bits do valor recuperado) da pilha 
de operandos do método sendo executado. Para selecionar os últimos 5 bits do segundo valor, é utilizada
a operação AND com a máscara 0x0000001F.
O número deslocado é empilhado na pilha de operandos.
A instrução ishl é equivalente à multiplicação por 2^s.


@param frame Frame correspondente ao método sendo executado.
@returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.
*/
uint32_t Instruction::ishl(Frame * frame) {
    int32_t val1, val2;
    Type res;
    val2 = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    val1 = frame->operandStack.top().type_int;
    frame->operandStack.top();
    val2 = val2 & 0x0000001F;
    res.tag = TAG_INT;
    res.type_int = val1 << val2;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

/**
Instrução ishr: Desloca s bits para direita de inteiro.

Recupera o valor a ser deslocado e o valor de s bits (s = 5 últimos bits do valor recuperado) da pilha 
de operandos do método sendo executado. Para selecionar os últimos 5 bits do segundo valor, é utilizada
a operação AND com a máscara 0x0000001F.
O número deslocado é empilhado na pilha de operandos.


@param frame Frame correspondente ao método sendo executado.
@returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.
*/
uint32_t Instruction::ishr(Frame * frame) {
    int32_t val1, val2;
    Type res;
    val2 = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    val1 = frame->operandStack.top().type_int;
    frame->operandStack.top();
    val2 = val2 & 0x0000001F;
    res.tag = TAG_INT;
    res.type_int = val1 >> val2;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

/**
Instrução ishl: Desloca s bits para esquerda de inteiro (Deslocamento lógico).

Recupera o valor a ser deslocado e o valor de s bits (s = 5 últimos bits do valor recuperado) da pilha 
de operandos do método sendo executado. Para selecionar os últimos 5 bits do segundo valor, é utilizada
a operação AND com a máscara 0x0000001F.
O número deslocado é empilhado na pilha de operandos.


@param frame Frame correspondente ao método sendo executado.
@returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.
*/
uint32_t Instruction::iushr(Frame * frame) {
    int32_t val1, val2;
    Type res;
    val2 = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    val1 = frame->operandStack.top().type_int;
    frame->operandStack.top();
    val2 = val2 & 0x0000001F;
    res.tag = TAG_INT;
    res.type_int = val1 >> val2;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

/**
Instrução iand: Operação AND entre inteiros.

Recupera os valores para operação (value1 AND value2) da pilha de operandos do método sendo executado. 
O resultado da operação é empilhado na pilha de operandos.


@param frame Frame correspondente ao método sendo executado.
@returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.
*/
uint32_t Instruction::iand(Frame * frame) {
    int32_t val1, val2;
    Type res;
    val2 = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    val1 = frame->operandStack.top().type_int;
    frame->operandStack.top();
    res.tag = TAG_INT;
    res.type_int = val1 & val2;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

/**
Instrução ior: Operação OR entre inteiros.

Recupera os valores para operação (value1 OR value2) da pilha de operandos do método sendo executado. 
O resultado da operação é empilhado na pilha de operandos.


@param frame Frame correspondente ao método sendo executado.
@returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.
*/
uint32_t Instruction::ior(Frame * frame) {
    int32_t val1, val2;
    Type res;
    val2 = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    val1 = frame->operandStack.top().type_int;
    frame->operandStack.top();
    res.tag = TAG_INT;
    res.type_int = val1 | val2;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

/**
Instrução ixor: Operação XOR entre inteiros.

Recupera os valores para operação (value1 XOR value2) da pilha de operandos do método sendo executado. 
O resultado da operação é empilhado na pilha de operandos.


@param frame Frame correspondente ao método sendo executado.
@returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.
*/
uint32_t Instruction::ixor(Frame * frame) {
    int32_t val1, val2;
    Type res;
    val2 = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    val1 = frame->operandStack.top().type_int;
    frame->operandStack.top();
    res.tag = TAG_INT;
    res.type_int = val1 ^ val2;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

/**
Instrução ladd: Soma longs.

Recupera os valores a serem somados da pilha de operandos do método sendo executado.
O resultado da soma é empilhado na pilha de operandos.

@param frame Frame correspondente ao método sendo executado.
@returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.
*/
uint32_t Instruction::ladd(Frame * frame) {
    int64_t val1, val2;
    Type res;
    val2 = frame->operandStack.top().type_long;
    frame->operandStack.pop();
    val1 = frame->operandStack.top().type_long;
    frame->operandStack.pop();
    res.tag = TAG_LONG;
    res.type_long = val1 + val2;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

/**
Instrução lsub: Subtrai longs.

Recupera os valores a serem somados da pilha de operandos do método sendo executado.
O resultado da subtração é empilhado na pilha de operandos.

@param frame Frame correspondente ao método sendo executado.
@returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.
*/
uint32_t Instruction::lsub(Frame * frame) {
    int64_t val1, val2;
    Type res;
    val2 = frame->operandStack.top().type_long;
    frame->operandStack.pop();
    val1 = frame->operandStack.top().type_long;
    frame->operandStack.pop();
    res.tag = TAG_LONG;
    res.type_long = val1 - val2;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

/**
Instrução lmul: Multiplica longs.

Recupera os valores a serem multiplicados da pilha de operandos do método sendo executado.
O resultado da multiplicação é empilhado na pilha de operandos.

@param frame Frame correspondente ao método sendo executado.
@returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.
*/
uint32_t Instruction::lmul(Frame * frame) {
    int64_t val1, val2;
    Type res;
    val2 = frame->operandStack.top().type_long;
    frame->operandStack.pop();
    val1 = frame->operandStack.top().type_long;
    frame->operandStack.pop();
    res.tag = TAG_LONG;
    res.type_long = val1 * val2;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

/**
Instrução ldiv: Divide longs.

Recupera os valores a serem divididos da pilha de operandos do método sendo executado.
O resultado da divisão é empilhado na pilha de operandos. Checa se o divisor é 0.

@param frame Frame correspondente ao método sendo executado.
@returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.
*/
uint32_t Instruction::ldiv(Frame * frame) {
    int64_t val1, val2;
    Type res;
    val2 = frame->operandStack.top().type_long;
    frame->operandStack.pop();
    val1 = frame->operandStack.top().type_long;
    frame->operandStack.pop();

    if(val2 == 0) {
        printf("TODO\n");
    } else {
        res.tag = TAG_LONG;
        res.type_long = val1 / val2;
        frame->operandStack.push(res);
    }

    return ++frame->local_pc;
}

/**
Instrução lrem: Resto de divisão de longs.

Recupera os valores a serem divididos da pilha de operandos do método sendo executado.
O resto da divisão (value1 - (value1 / value2) * value2) é empilhado na pilha de operandos. Checa se o divisor é 0.

@param frame Frame correspondente ao método sendo executado.
@returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.
*/
uint32_t Instruction::lrem(Frame * frame) {
    int64_t val1, val2;
    Type res;
    val2 = frame->operandStack.top().type_long;
    frame->operandStack.pop();
    val1 = frame->operandStack.top().type_long;
    frame->operandStack.pop();

    if(val2 == 0) {
        printf("TODO\n");
    } else {
        res.tag = TAG_INT;
        res.type_long = val1 % val2;
        frame->operandStack.push(res);
    }

    return ++frame->local_pc;
}

/**
Instrução lneg: Torna número long negativo.

Recupera o valor a ser trocado para o seu negativo da pilha de operandos do método sendo executado.
O número negativo é empilhado na pilha de operandos.

@param frame Frame correspondente ao método sendo executado.
@returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.
*/
uint32_t Instruction::lneg(Frame * frame) {
    int64_t val1;
    Type res;
    val1 = frame->operandStack.top().type_long;
    frame->operandStack.top();
    res.tag = TAG_LONG;
    res.type_long = -val1;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

/**
Instrução land: Operação AND entre longs.

Recupera os valores para operação (value1 AND value2) da pilha de operandos do método sendo executado. 
O resultado da operação é empilhado na pilha de operandos.


@param frame Frame correspondente ao método sendo executado.
@returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.
*/
uint32_t Instruction::land(Frame * frame) {
    int64_t val1, val2;
    Type res;
    val2 = frame->operandStack.top().type_long;
    frame->operandStack.pop();
    val1 = frame->operandStack.top().type_long;
    frame->operandStack.top();
    res.tag = TAG_LONG;
    res.type_long = val1 & val2;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

/**
Instrução lshl: Desloca s bits para esquerda de um valor long.

Recupera o valor a ser deslocado e o valor de s bits (s = 5 últimos bits do valor recuperado) da pilha 
de operandos do método sendo executado. Para selecionar os últimos 5 bits do segundo valor 
(que deve ser inteiro), é utilizada a operação AND com a máscara 0x0000001F.
O número deslocado é empilhado na pilha de operandos.
A instrução lshl é equivalente à multiplicação por 2^s.


@param frame Frame correspondente ao método sendo executado.
@returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.
*/
uint32_t Instruction::lshl(Frame * frame) {
    int64_t val1, val2;
    Type res;
    val2 = frame->operandStack.top().type_long;
    frame->operandStack.pop();
    val1 = frame->operandStack.top().type_long;
    frame->operandStack.top();
    val2 = val2 & 0x0000003F;
    res.tag = TAG_LONG;
    res.type_long = val1 << val2;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

/**
Instrução lshr: Desloca s bits para direita de um valor long.

Recupera o valor a ser deslocado e o valor de s bits (s = 5 últimos bits do valor recuperado) da pilha 
de operandos do método sendo executado. Para selecionar os últimos 5 bits do segundo valor 
(que deve ser inteiro), é utilizada a operação AND com a máscara 0x0000001F.
O número deslocado é empilhado na pilha de operandos.
A instrução lshl é equivalente à multiplicação por 2^s.


@param frame Frame correspondente ao método sendo executado.
@returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.
*/
uint32_t Instruction::lshr(Frame * frame) {
    int64_t val1, val2;
    Type res;
    val2 = frame->operandStack.top().type_long;
    frame->operandStack.pop();
    val1 = frame->operandStack.top().type_long;
    frame->operandStack.top();
    val2 = val2 & 0x0000003F;
    res.tag = TAG_LONG;
    res.type_long = val1 >> val2;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

/**
Instrução lor: Operação OR entre longs.

Recupera os valores para operação (value1 OR value2) da pilha de operandos do método sendo executado. 
O resultado da operação é empilhado na pilha de operandos.


@param frame Frame correspondente ao método sendo executado.
@returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.
*/
uint32_t Instruction::lor(Frame * frame) {
    int64_t val1, val2;
    Type res;
    val2 = frame->operandStack.top().type_long;
    frame->operandStack.pop();
    val1 = frame->operandStack.top().type_long;
    frame->operandStack.top();
    res.tag = TAG_LONG;
    res.type_long = val1 | val2;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

/**
Instrução lor: Operação XOR entre longs.

Recupera os valores para operação (value1 OR value2) da pilha de operandos do método sendo executado. 
O resultado da operação é empilhado na pilha de operandos.


@param frame Frame correspondente ao método sendo executado.
@returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.
*/
uint32_t Instruction::lxor(Frame * frame) {
    int64_t val1, val2;
    Type res;
    val2 = frame->operandStack.top().type_long;
    frame->operandStack.pop();
    val1 = frame->operandStack.top().type_long;
    frame->operandStack.top();
    res.tag = TAG_LONG;
    res.type_long = val1 ^ val2;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

/**
Instrução iinc: Incrementa por uma constante uma variável local.

Recupera o valor a ser incrementado (que deve ser um inteiro) do vetor de variáveis locais na posição index (que deve ser inteiro).
O valor da constante (imm_const, que deve ser um inteiro) é recuperado do atributo code de codeAttribute.  
O resultado volta para o vetor de variáveis na posição index.


@param frame Frame correspondente ao método sendo executado.
@returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.
*/
uint32_t Instruction::iinc(Frame * frame) {
    uint8_t* bytecode = frame->codeAttribute.code;
    uint8_t index = bytecode[++frame->local_pc];
    int8_t imm_const = bytecode[++frame->local_pc];
    int32_t temp, sign_ext;

    sign_ext = imm_const;
    temp = frame->localVariables[index].type_int;
    temp += sign_ext;

    frame->localVariables[index].type_int = temp;

    return ++frame->local_pc;
}

/**
Instrução fadd: Soma floats.

Recupera os valores a serem somados da pilha de operandos do método sendo executado.
O resultado da soma é empilhado na pilha de operandos.

@param frame Frame correspondente ao método sendo executado.
@returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.
*/
uint32_t Instruction::fadd(Frame * frame) {
    float val1, val2;
    Type res;
    val2 = frame->operandStack.top().type_float;
    frame->operandStack.pop();
    val1 = frame->operandStack.top().type_float;
    frame->operandStack.pop();
    res.tag = TAG_FLOAT;
    res.type_float = val1 + val2;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

/**
Instrução fsub: Subtrai floats.

Recupera os valores a serem somados da pilha de operandos do método sendo executado.
O resultado da subtração é empilhado na pilha de operandos.

@param frame Frame correspondente ao método sendo executado.
@returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.
*/
uint32_t Instruction::fsub(Frame * frame) {
    float val1, val2;
    Type res;
    val2 = frame->operandStack.top().type_float;
    frame->operandStack.pop();
    val1 = frame->operandStack.top().type_float;
    frame->operandStack.pop();
    res.tag = TAG_FLOAT;
    res.type_float = val1 - val2;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

/**
Instrução fmul: Multiplica floats.

Recupera os valores a serem multiplicados da pilha de operandos do método sendo executado.
O resultado da multiplicação é empilhado na pilha de operandos.

@param frame Frame correspondente ao método sendo executado.
@returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.
*/
uint32_t Instruction::fmul(Frame * frame) {
    float val1, val2;
    Type res;
    val2 = frame->operandStack.top().type_float;
    frame->operandStack.pop();
    val1 = frame->operandStack.top().type_float;
    frame->operandStack.pop();
    res.tag = TAG_FLOAT;
    res.type_float = val1 * val2;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

/**
Instrução fdiv: Divide floats.

Recupera os valores a serem divididos da pilha de operandos do método sendo executado.
O resultado da divisão é empilhado na pilha de operandos.

@param frame Frame correspondente ao método sendo executado.
@returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.
*/
uint32_t Instruction::fdiv(Frame * frame) {
    float val1, val2;
    Type res;
    val2 = frame->operandStack.top().type_float;
    frame->operandStack.pop();
    val1 = frame->operandStack.top().type_float;
    frame->operandStack.pop();
    res.tag = TAG_FLOAT;
    res.type_float = val1 / val2;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

/**
Instrução frem: Resto de divisão de floats.

Recupera os valores a serem divididos da pilha de operandos do método sendo executado.
O resto da divisão é empilhado na pilha de operandos.

@param frame Frame correspondente ao método sendo executado.
@returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.
*/
uint32_t Instruction::frem(Frame * frame) {
    float val1, val2;
    Type res;
    val2 = frame->operandStack.top().type_float;
    frame->operandStack.pop();
    val1 = frame->operandStack.top().type_float;
    frame->operandStack.pop();
    res.tag = TAG_FLOAT;
    res.type_float = fmodf(val1, val2);
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

/**
Instrução fneg: Torna número float negativo.

Recupera o valor a ser trocado para o seu negativo da pilha de operandos do método sendo executado.
O número negativo é empilhado na pilha de operandos.

@param frame Frame correspondente ao método sendo executado.
@returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.
*/
uint32_t Instruction::fneg(Frame * frame) {
    float val1;
    Type res;
    val1 = frame->operandStack.top().type_float;
    frame->operandStack.pop();
    res.tag = TAG_FLOAT;
    res.type_float = -val1;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

/**
Instrução dadd: Soma doubles.

Recupera os valores a serem somados da pilha de operandos do método sendo executado.
O resultado da soma é empilhado na pilha de operandos.

@param frame Frame correspondente ao método sendo executado.
@returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.
*/
uint32_t Instruction::dadd(Frame * frame) {
    double val1, val2;
    Type res;
    val2 = frame->operandStack.top().type_double;
    frame->operandStack.pop();
    val1 = frame->operandStack.top().type_double;
    frame->operandStack.pop();
    res.tag = TAG_DOUBLE;
    res.type_double = val1 + val2;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

/**
Instrução dsub: Subtrai doubles.

Recupera os valores a serem somados da pilha de operandos do método sendo executado.
O resultado da subtração é empilhado na pilha de operandos.

@param frame Frame correspondente ao método sendo executado.
@returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.
*/
uint32_t Instruction::dsub(Frame * frame) {
    double val1, val2;
    Type res;
    val2 = frame->operandStack.top().type_double;
    frame->operandStack.pop();
    val1 = frame->operandStack.top().type_double;
    frame->operandStack.pop();
    res.tag = TAG_DOUBLE;
    res.type_double = val1 - val2;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

/**
Instrução dmul: Multiplica doubles.

Recupera os valores a serem multiplicados da pilha de operandos do método sendo executado.
O resultado da multiplicação é empilhado na pilha de operandos.

@param frame Frame correspondente ao método sendo executado.
@returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.
*/
uint32_t Instruction::dmul(Frame * frame) {
    double val1, val2;
    Type res;
    val2 = frame->operandStack.top().type_double;
    frame->operandStack.pop();
    val1 = frame->operandStack.top().type_double;
    frame->operandStack.pop();
    res.tag = TAG_DOUBLE;
    res.type_double = val1 * val2;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

/**
Instrução ddiv: Divide doubles.

Recupera os valores a serem divididos da pilha de operandos do método sendo executado.
O resultado da divisão é empilhado na pilha de operandos.

@param frame Frame correspondente ao método sendo executado.
@returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.
*/
uint32_t Instruction::ddiv(Frame * frame) {
    double val1, val2;
    Type res;
    val2 = frame->operandStack.top().type_double;
    frame->operandStack.pop();
    val1 = frame->operandStack.top().type_double;
    frame->operandStack.pop();
    res.tag = TAG_DOUBLE;
    res.type_double = val1 / val2;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

/**
Instrução drem: Resto de divisão de doubles.

Recupera os valores a serem divididos da pilha de operandos do método sendo executado.
O resto da divisão é empilhado na pilha de operandos.

@param frame Frame correspondente ao método sendo executado.
@returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.
*/
uint32_t Instruction::drem(Frame * frame) {
    double val1, val2;
    Type res;
    val2 = frame->operandStack.top().type_double;
    frame->operandStack.pop();
    val1 = frame->operandStack.top().type_double;
    frame->operandStack.pop();
    res.tag = TAG_DOUBLE;
    res.type_double = fmod(val1,val2);
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

/**
Instrução dneg: Torna número double negativo.

Recupera o valor a ser trocado para o seu negativo da pilha de operandos do método sendo executado.
O número negativo é empilhado na pilha de operandos.

@param frame Frame correspondente ao método sendo executado.
@returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.
*/
uint32_t Instruction::dneg(Frame * frame) {
    double val1;
    Type res;
    val1 = frame->operandStack.top().type_double;
    frame->operandStack.pop();
    res.tag = TAG_DOUBLE;
    res.type_double = -val1;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}
