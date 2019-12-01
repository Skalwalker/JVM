/**
 * \file Instruction.hpp
 * \brief Declaração da Classe Instruction e seus respectivos métodos e atributos.
 *
 * \author Khalil Carsten, Renato Nobre, Roberta Costa, Johannes Peter, Guilherme Andreúce
 * \date $Date: 29/11/2019
*/

#ifndef INSTRUCTIONS_H_INCLUDED
#define INSTRUCTIONS_H_INCLUDED

#include <cstdint>
#include <string>
#include <math.h>
#include <tuple>
#include "../../execution/ExceptionThrower.hpp"
#include "../Frame.hpp"
#include "../../loader/ClassLoader.hpp"
#include "../../models/CPInfo.hpp"

#define CONSTANT_STRING 8
#define CONSTANT_INTEGER 3
#define CONSTANT_FLOAT 4
#define CONSTANT_LONG 5
#define CONSTANT_DOUBLE 6

#define T_BOOLEAN 4
#define T_CHAR 5
#define T_FLOAT 6
#define T_DOUBLE 7
#define T_BYTE 8
#define T_SHORT 9
#define T_INT 10
#define T_LONG 11

using namespace std;

/**
* Definição das instruções de acordo com a Java SE 8 Edition.
* São divididas nos tipos:
* -# Conversions: \n
* nop, aconst_null, iconst_m1, iconst_0, iconst_1, iconst_2, iconst_3, iconst_4, iconst_5, lconst_0,
* lconst_1, fconst_0, fconst_1, fconst_2, dconst_0, dconst_1, bipush, sipush, ldc, ldc_w, ldc2_w
* -# Loads: \n
* iload, lload, fload, dload, aload, iload_0, iload_1, iload_2, iload_3, lload_0, lload_1, lload_2,
* lload_3, fload_0, fload_1, fload_2, fload_3, dload_0, dload_1, dload_2, dload_3, aload_0, aload_1,
* aload_2, aload_3, iaload, laload, faload, daload, aaload, baload, caload, saload
* -# Stores: \n
* istore, lstore, fstore, dstore, astore, istore_0, istore_1, istore_2, istore_3, lstore_0, lstore_1,
* lstore_2, lstore_3, fstore_0, fstore_1, fstore_2, fstore_3, dstore_0, dstore_1, dstore_2, dstore_3, astore_0,
* astore_1, astore_2, astore_3, iastore, lastore, fastore, dastore, aastore, bastore, castore, sastore
* -# Stack: \n
* pop, pop2, dup, dup_x1, dup_x2, dup2, dup2_x1, dup2_x2, swap
* -# Math: \n
* iadd, ladd, fadd, dadd, isub, lsub, fsub, dsub, imul, lmul, fmul, dmul, idiv, ldiv, fdiv, ddiv, irem, lrem,
* frem, drem, ineg, lneg, fneg, dneg, ishl, lshl, ishr, lshr, iushr, lushr, iand, land, ior, lor, ixor, lxor, iinc
* -# Conversions: \n
* i2l, i2f, i2d, l2i, l2f, l2d, f2i, f2l, f2d, d2i, d2l, d2f, i2b, i2c, i2s
* -# Comparisons: \n
* lcmp, fcmpl, fcmpg, dcmpl, dcmpg, ifeq, ifne, iflt, ifge, ifgt, ifle, if_icmpeq, if_icmpne, if_icmplt, if_icmpge,
* if_icmpgt, if_icmple, if_acmpeq, if_acmpne
* -# References: \n
* getstatic, putstatic, getfield, putfield, invokevirtual, invokespecial, invokestatic, invokeinterface, invokedynamic,
* new, newarray, anewarray, arraylength, athrow, checkcast, instanceof, monitorenter, monitorexit
* -# Control: \n
* goto, jsr, ret, tableswitch, lookupswitch, ireturn, lreturn, freturn, dreturn, areturn, return
* -# Extended: \n
* wide, multianewarray, ifnull, ifnonnull, goto_w, jsr_w
* -# Reserved: \n
* breakpoint, impdep1, impdep2
*/
class Instruction {
public:
    string mnemonic;
    uint32_t bytecount;
    static ClassLoader * classLoader;
    uint32_t (*exec)(Frame*);
    Instruction(string);
    Instruction(string, uint32_t);
    Instruction();
    static tuple<string, string, string> methodInfoSplit(string);
    static tuple<string, string, string> fieldInfoSplit(string);
    static map<string, Type>* instantiateFields(ClassFile);

    static uint32_t monitorenter(Frame*);
    static uint32_t monitorexit(Frame*);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t getstatic(Frame*);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t ldc(Frame*);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t ldc2_w(Frame*);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t invokevirtual(Frame*);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t invokestatic(Frame*);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t invokespecial(Frame*);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */

    static uint32_t putfield(Frame*);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */

    static uint32_t returnfunc(Frame*);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t ireturn(Frame*);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t lreturn(Frame*);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t dreturn(Frame*);

    /**
    Instrução ladd: Soma longs.

    Recupera os valores a serem somados da pilha de operandos do método sendo executado.
    O resultado da soma é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t ladd(Frame*);

    /**
    Instrução lsub: Subtrai longs.

    Recupera os valores a serem somados da pilha de operandos do método sendo executado.
    O resultado da subtração é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t lsub(Frame*);

    /**
    Instrução lmul: Multiplica longs.

    Recupera os valores a serem multiplicados da pilha de operandos do método sendo executado.
    O resultado da multiplicação é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t lmul(Frame*);

    /**
    Instrução ldiv: Divide longs.

    Recupera os valores a serem divididos da pilha de operandos do método sendo executado.
    O resultado da divisão é empilhado na pilha de operandos. Checa se o divisor é 0.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t ldiv(Frame*);

    /**
    Instrução lneg: Torna número long negativo.

    Recupera o valor a ser trocado para o seu negativo da pilha de operandos do método sendo executado.
    O número negativo é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t lneg(Frame*);

    /**
    Instrução lrem: Resto de divisão de longs.

    Recupera os valores a serem divididos da pilha de operandos do método sendo executado.
    O resto da divisão (value1 - (value1 / value2) * value2) é empilhado na pilha de operandos. Checa se o divisor é 0.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t lrem(Frame*);

    /**
    Instrução lshl: Desloca s bits para esquerda de um valor long.

    Recupera o valor a ser deslocado e o valor de s bits (s = 5 últimos bits do valor recuperado) da pilha
    de operandos do método sendo executado. Para selecionar os últimos 5 bits do segundo valor
    (que deve ser inteiro), é utilizada a operação AND com a máscara 0x0000001F.
    O número deslocado é empilhado na pilha de operandos.
    A instrução lshl é equivalente à multiplicação por 2^s.


    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t lshl(Frame*);

    /**
    Instrução lshr: Desloca s bits para direita de um valor long.

    Recupera o valor a ser deslocado e o valor de s bits (s = 5 últimos bits do valor recuperado) da pilha
    de operandos do método sendo executado. Para selecionar os últimos 5 bits do segundo valor
    (que deve ser inteiro), é utilizada a operação AND com a máscara 0x0000001F.
    O número deslocado é empilhado na pilha de operandos.
    A instrução lshl é equivalente à multiplicação por 2^s.


    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t lshr(Frame*);

    /**
    Instrução land: Operação AND entre longs.

    Recupera os valores para operação (value1 AND value2) da pilha de operandos do método sendo executado.
    O resultado da operação é empilhado na pilha de operandos.


    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t land(Frame*);

    /**
    Instrução lor: Operação OR entre longs.

    Recupera os valores para operação (value1 OR value2) da pilha de operandos do método sendo executado.
    O resultado da operação é empilhado na pilha de operandos.


    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t lor(Frame*);

    /**
    Instrução lxor: Operação XOR entre longs.

    Recupera os valores para operação (value1 OR value2) da pilha de operandos do método sendo executado.
    O resultado da operação é empilhado na pilha de operandos.


    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t lxor(Frame*);

    /**
    Instrução iadd: Soma inteiros.

    Recupera os valores a serem somados da pilha de operandos do método sendo executado.
    O resultado da soma é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t iadd(Frame*);

    /**
    Instrução isub: Subtrai inteiros.

    Recupera os valores a serem somados da pilha de operandos do método sendo executado.
    O resultado da subtração é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t isub(Frame *);

    /**
    Instrução imul: Multiplica inteiros.

    Recupera os valores a serem multiplicados da pilha de operandos do método sendo executado.
    O resultado da multiplicação é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t imul(Frame *);

    /**
    Instrução idiv: Divide inteiros.

    Recupera os valores a serem divididos da pilha de operandos do método sendo executado.
    O resultado da divisão é empilhado na pilha de operandos. Checa se o divisor é 0.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t idiv(Frame *);

    /**
    Instrução irem: Resto de divisão de inteiros.

    Recupera os valores a serem divididos da pilha de operandos do método sendo executado.
    O resto da divisão (value1 - (value1 / value2) * value2) é empilhado na pilha de operandos. Checa se o divisor é 0.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t irem(Frame *);

    /**
    Instrução ineg: Torna número inteiro negativo.

    Recupera o valor a ser trocado para o seu negativo da pilha de operandos do método sendo executado.
    O número negativo é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t ineg(Frame *);

    /**
    Instrução ishl: Desloca s bits para esquerda de inteiro.

    Recupera o valor a ser deslocado e o valor de s bits (s = 5 últimos bits do valor recuperado) da pilha
    de operandos do método sendo executado. Para selecionar os últimos 5 bits do segundo valor, é utilizada
    a operação AND com a máscara 0x0000001F.
    O número deslocado é empilhado na pilha de operandos.
    A instrução ishl é equivalente à multiplicação por 2^s.


    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t ishl(Frame*);

    /**
    Instrução ishr: Desloca s bits para direita de inteiro.

    Recupera o valor a ser deslocado e o valor de s bits (s = 5 últimos bits do valor recuperado) da pilha
    de operandos do método sendo executado. Para selecionar os últimos 5 bits do segundo valor, é utilizada
    a operação AND com a máscara 0x0000001F.
    O número deslocado é empilhado na pilha de operandos.


    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t ishr(Frame*);

    /**
    Instrução uishl: Desloca s bits para esquerda de inteiro (Deslocamento lógico).

    Recupera o valor a ser deslocado e o valor de s bits (s = 5 últimos bits do valor recuperado) da pilha
    de operandos do método sendo executado. Para selecionar os últimos 5 bits do segundo valor, é utilizada
    a operação AND com a máscara 0x0000001F.
    O número deslocado é empilhado na pilha de operandos.


    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t iushr(Frame*);

    /**
    Instrução iand: Operação AND entre inteiros.

    Recupera os valores para operação (value1 AND value2) da pilha de operandos do método sendo executado.
    O resultado da operação é empilhado na pilha de operandos.


    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t iand(Frame*);

    /**
    Instrução ior: Operação OR entre inteiros.

    Recupera os valores para operação (value1 OR value2) da pilha de operandos do método sendo executado.
    O resultado da operação é empilhado na pilha de operandos.


    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t ior(Frame*);

    /**
    Instrução ixor: Operação XOR entre inteiros.

    Recupera os valores para operação (value1 XOR value2) da pilha de operandos do método sendo executado.
    O resultado da operação é empilhado na pilha de operandos.


    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t ixor(Frame*);

    /**
    Instrução iinc: Incrementa por uma constante uma variável local.

    Recupera o valor a ser incrementado (que deve ser um inteiro) do vetor de variáveis locais na posição index (que deve ser inteiro).
    Index é recuperado do atributo code de codeAttribute definido em AttributeInfo.cpp.
    O valor da constante (imm_const, que deve ser um inteiro) também recuperado do atributo code de codeAttribute.
    O resultado volta para o vetor de variáveis locais na posição index.


    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t iinc(Frame*);

    /**
    Instrução fadd: Soma floats.

    Recupera os valores a serem somados da pilha de operandos do método sendo executado.
    O resultado da soma é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t fadd(Frame *);

    /**
    Instrução fsub: Subtrai floats.

    Recupera os valores a serem somados da pilha de operandos do método sendo executado.
    O resultado da subtração é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t fsub(Frame *);

    /**
    Instrução fmul: Multiplica floats.

    Recupera os valores a serem multiplicados da pilha de operandos do método sendo executado.
    O resultado da multiplicação é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t fmul(Frame *);

    /**
    Instrução fdiv: Divide floats.

    Recupera os valores a serem divididos da pilha de operandos do método sendo executado.
    O resultado da divisão é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t fdiv(Frame *);

    /**
    Instrução frem: Resto de divisão de floats.

    Recupera os valores a serem divididos da pilha de operandos do método sendo executado.
    O resto da divisão é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t frem(Frame *);

    /**
    Instrução fneg: Torna número float negativo.

    Recupera o valor a ser trocado para o seu negativo da pilha de operandos do método sendo executado.
    O número negativo é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t fneg(Frame *);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t bipush(Frame*);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t sipush(Frame*);


    /**
    Instrução dadd: Soma doubles.

    Recupera os valores a serem somados da pilha de operandos do método sendo executado.
    O resultado da soma é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t dadd(Frame *);

    /**
    Instrução dsub: Subtrai doubles.

    Recupera os valores a serem somados da pilha de operandos do método sendo executado.
    O resultado da subtração é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t dsub(Frame *);

    /**
    Instrução dmul: Multiplica doubles.

    Recupera os valores a serem multiplicados da pilha de operandos do método sendo executado.
    O resultado da multiplicação é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t dmul(Frame *);

    /**
    Instrução ddiv: Divide doubles.

    Recupera os valores a serem divididos da pilha de operandos do método sendo executado.
    O resultado da divisão é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t ddiv(Frame *);

    /**
    Instrução drem: Resto de divisão de doubles.

    Recupera os valores a serem divididos da pilha de operandos do método sendo executado.
    O resto da divisão é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t drem(Frame *);

    /**
    Instrução dneg: Torna número double negativo.

    Recupera o valor a ser trocado para o seu negativo da pilha de operandos do método sendo executado.
    O número negativo é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t dneg(Frame *);


    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t fstore(Frame *);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t fstore_0(Frame *);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t fstore_1(Frame *);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t fstore_2(Frame *);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t fstore_3(Frame *);


    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t lstore(Frame *);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t lstore_0(Frame *);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t lstore_1(Frame *);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t lstore_2(Frame *);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t lstore_3(Frame *);


    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t istore(Frame *);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t istore_0(Frame *);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t istore_1(Frame *);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t istore_2(Frame *);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t istore_3(Frame *);


    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t dstore(Frame *);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t dstore_0(Frame *);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t dstore_1(Frame *);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t dstore_2(Frame *);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t dstore_3(Frame *);


    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t iastore(Frame *);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t dastore(Frame *);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t fastore(Frame *);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t castore(Frame *);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t sastore(Frame *);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t lastore(Frame *);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t bastore(Frame *);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t astore(Frame *);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t astore_0(Frame *);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t astore_1(Frame *);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t astore_2(Frame *);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t astore_3(Frame *);


    /**
    Instrução lload: Carrega um valor long.

    Recupera um elemento long do vetor de variáveis locais da posição indicada por index.
    Index é recuperado do atributo code de codeAttribute definido em AttributeInfo.cpp.
    O valor é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t lload(Frame *);

    /**
    Instrução lload_0: Carrega um valor long.

    Do grupo de instruções lload_<n>, recupera um elemento long do vetor de variáveis locais da posição
    indicada por n.
    O valor é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t lload_0(Frame *);

    /**
    Instrução lload_1: Carrega um valor long.

    Do grupo de instruções lload_<n>, recupera um elemento long do vetor de variáveis locais da posição
    indicada por n.
    O valor é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t lload_1(Frame *);

    /**
    Instrução lload_2: Carrega um valor long.

    Do grupo de instruções lload_<n>, recupera um elemento long do vetor de variáveis locais da posição
    indicada por n.
    O valor é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t lload_2(Frame *);

    /**
    Instrução lload_3: Carrega um valor long.

    Do grupo de instruções lload_<n>, recupera um elemento long do vetor de variáveis locais da posição
    indicada por n.
    O valor é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t lload_3(Frame *);


    /**
    Instrução aload_0: Carrega um valor do tipo referência.

    Do grupo de instruções aload_<n>, recupera um elemento do tipo referência do vetor de variáveis locais da posição
    indicada por n.
    O valor é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t aload_0(Frame *);

    /**
    Instrução aload_1: Carrega um valor do tipo referência.

    Do grupo de instruções aload_<n>, recupera um elemento do tipo referência do vetor de variáveis locais da posição
    indicada por n.
    O valor é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t aload_1(Frame *);

    /**
    Instrução aload_2: Carrega um valor do tipo referência.

    Do grupo de instruções aload_<n>, recupera um elemento do tipo referência do vetor de variáveis locais da posição
    indicada por n.
    O valor é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t aload_2(Frame *);

    /**
    Instrução aload_3: Carrega um valor do tipo referência.

    Do grupo de instruções aload_<n>, recupera um elemento do tipo referência do vetor de variáveis locais da posição
    indicada por n.
    O valor é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t aload_3(Frame *);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t iaload(Frame *);

    /**
    Instrução iaload: Carrega um valor do tipo inteiro de um array.

    Recupera um elemento do tipo inteiro de um array (que é do tipo referência). Tanto o index quanto  o array
    são recuperados da pilha de operandos.
    O elemento é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t faload(Frame *);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t laload(Frame *);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t daload(Frame *);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t baload(Frame *);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t caload(Frame *);



    /**
    Instrução fload: Carrega um valor float.

    Recupera um elemento float do vetor de variáveis locais da posição indicada por index.
    Index é recuperado do atributo code de codeAttribute definido em AttributeInfo.cpp.
    O valor é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t fload(Frame *);

    /**
    Instrução fload_0: Carrega um valor float.

    Do grupo de instruções fload_<n>, recupera um elemento float do vetor de variáveis locais da posição
    indicada por n.
    O valor é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t fload_0(Frame *);

    /**
    Instrução fload_1: Carrega um valor float.

    Do grupo de instruções fload_<n>, recupera um elemento float do vetor de variáveis locais da posição
    indicada por n.
    O valor é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t fload_1(Frame *);

    /**
    Instrução fload_2: Carrega um valor float.

    Do grupo de instruções fload_<n>, recupera um elemento float do vetor de variáveis locais da posição
    indicada por n.
    O valor é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t fload_2(Frame *);

    /**
    Instrução fload_3: Carrega um valor float.

    Do grupo de instruções fload_<n>, recupera um elemento float do vetor de variáveis locais da posição
    indicada por n.
    O valor é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t fload_3(Frame *);


    /**
    Instrução fload: Carrega um valor inteiro.

    Recupera um elemento inteiro do vetor de variáveis locais da posição indicada por index.
    Index é recuperado do atributo code de codeAttribute definido em AttributeInfo.cpp.
    O valor é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t iload(Frame *);

    /**
    Instrução iload_0: Carrega um valor inteiro.

    Do grupo de instruções iload_<n>, recupera um elemento inteiro do vetor de variáveis locais da posição
    indicada por n.
    O valor é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t iload_0(Frame *);

    /**
    Instrução iload_1: Carrega um valor inteiro.

    Do grupo de instruções iload_<n>, recupera um elemento inteiro do vetor de variáveis locais da posição
    indicada por n.
    O valor é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t iload_1(Frame *);

    /**
    Instrução iload_2: Carrega um valor inteiro.

    Do grupo de instruções iload_<n>, recupera um elemento inteiro do vetor de variáveis locais da posição
    indicada por n.
    O valor é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t iload_2(Frame *);

    /**
    Instrução iload_3: Carrega um valor inteiro.

    Do grupo de instruções iload_<n>, recupera um elemento inteiro do vetor de variáveis locais da posição
    indicada por n.
    O valor é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t iload_3(Frame *);


    /**
    Instrução dload: Carrega um valor double.

    Recupera um elemento double do vetor de variáveis locais da posição indicada por index.
    Index é recuperado do atributo code de codeAttribute definido em AttributeInfo.cpp.
    O valor é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t dload(Frame *);

    /**
    Instrução dload_0: Carrega um valor double.

    Do grupo de instruções dload_<n>, recupera um elemento double do vetor de variáveis locais da posição
    indicada por n.
    O valor é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t dload_0(Frame *);

    /**
    Instrução dload_1: Carrega um valor double.

    Do grupo de instruções dload_<n>, recupera um elemento double do vetor de variáveis locais da posição
    indicada por n.
    O valor é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t dload_1(Frame *);

    /**
    Instrução dload_2: Carrega um valor double.

    Do grupo de instruções dload_<n>, recupera um elemento double do vetor de variáveis locais da posição
    indicada por n.
    O valor é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t dload_2(Frame *);

    /**
    Instrução dload_3: Carrega um valor double.

    Do grupo de instruções dload_<n>, recupera um elemento double do vetor de variáveis locais da posição
    indicada por n.
    O valor é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t dload_3(Frame *);


    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t iconst_m1(Frame *);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t iconst_0(Frame *);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t iconst_1(Frame *);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t iconst_2(Frame *);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t iconst_3(Frame *);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t iconst_4(Frame *);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t iconst_5(Frame *);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t lconst_0(Frame *);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t lconst_1(Frame *);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t dconst_0(Frame *);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t dconst_1(Frame *);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t fconst_0(Frame *);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t fconst_1(Frame *);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t fconst_2(Frame *);


    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t lcmp(Frame*);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t ifle(Frame*);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t ifge(Frame*);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t ifeq(Frame*);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t ifne(Frame*);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t iflt(Frame*);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t ifgt(Frame*);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t fcmpl(Frame*);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t fcmpg(Frame*);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t dcmpl(Frame*);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t dcmpg(Frame*);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t if_icmpeq(Frame*);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t if_icmpne(Frame*);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t if_icmplt(Frame*);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t if_icmpge(Frame*);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t if_icmpgt(Frame*);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t if_icmple(Frame*);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t if_acmpeq(Frame*);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t if_acmpne(Frame*);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t goto_func(Frame *);


    /**
    Instrução f2d: Converte float para double.

    Recupera o valor a ser convertido da pilha de operandos do método sendo executado.
    O valor é convertido de acordo com a tag definida em Frame.hpp que representa o tipo double.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t f2d(Frame *);

    /**
    Instrução f2i Converte float para int.

    Recupera o valor a ser convertido da pilha de operandos do método sendo executado.
    O valor é convertido de acordo com a tag definida em Frame.hpp que representa o tipo int32_t.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t f2i(Frame *);

    /**
    Instrução f2l: Converte float para long.

    Recupera o valor a ser convertido da pilha de operandos do método sendo executado.
    O valor é convertido de acordo com a tag definida em Frame.hpp que representa o tipo int64_t.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t f2l(Frame *);

    /**
    Instrução d2f: Converte double para float.

    Recupera o valor a ser convertido da pilha de operandos do método sendo executado.
    O valor é convertido de acordo com a tag definida em Frame.hpp que representa o tipo float.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t d2f(Frame *);

    /**
    Instrução d2i: Converte double para int.

    Recupera o valor a ser convertido da pilha de operandos do método sendo executado.
    O valor é convertido de acordo com a tag definida em Frame.hpp que representa o tipo int32_t.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t d2i(Frame *);

    /**
    Instrução d2l: Converte double para long.

    Recupera o valor a ser convertido da pilha de operandos do método sendo executado.
    O valor é convertido de acordo com a tag definida em Frame.hpp que representa o tipo int64_t.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t d2l(Frame *);

    /**
    Instrução l2f: Converte long para float.

    Recupera o valor a ser convertido da pilha de operandos do método sendo executado.
    O valor é convertido de acordo com a tag definida em Frame.hpp que representa o tipo float.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t l2f(Frame *);

    /**
    Instrução l2i: Converte long para int.

    Recupera o valor a ser convertido da pilha de operandos do método sendo executado.
    O valor é convertido de acordo com a tag definida em Frame.hpp que representa o tipo int32_t.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t l2i(Frame *);

    /**
    Instrução l2d: Converte long para double.

    Recupera o valor a ser convertido da pilha de operandos do método sendo executado.
    O valor é convertido de acordo com a tag definida em Frame.hpp que representa o tipo double.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t l2d(Frame *);

    /**
     * \brief Converte int para double.
     *
     * Recupera o valor a ser convertido da pilha de
     * operandos do método sendo executado.
     * O valor é convertido de acordo com a tag
     * da struct Type que representa o tipo
     * double.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t i2d(Frame*);

    /**
    Instrução i2l: Converte int para long.

    Recupera o valor a ser convertido da pilha de operandos do método sendo executado.
    O valor é convertido de acordo com a tag definida em Frame.hpp que representa o tipo int64_t.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t i2l(Frame*);

    /**
     * \brief Converte int para float.
     *
     * Recupera o valor a ser convertido da pilha de
     * operandos do método sendo executado.
     * O valor é convertido de acordo com a tag
     * definida em Frame.hpp que representa o tipo
     * float.
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t i2f(Frame*);

    /**
    Instrução i2b: Converte int para byte.

    Recupera o valor a ser convertido da pilha de operandos do método sendo executado.
    O valor é convertido de acordo com a tag definida em Frame.hpp que representa o tipo int8_t.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t i2b(Frame*);

    /**
    Instrução i2s: Converte int para short.

    Recupera o valor a ser convertido da pilha de operandos do método sendo executado.
    O valor é convertido de acordo com a tag definida em Frame.hpp que representa o tipo int16_t.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t i2s(Frame*);

    /**
    Instrução i2c: Converte int para char.

    Recupera o valor a ser convertido da pilha de operandos do método sendo executado.
    O valor é convertido de acordo com a tag definida em Frame.hpp que representa o tipo uint8_t.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t i2c(Frame*);


    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t jsr(Frame *);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t ret(Frame *);


    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t newarray(Frame *);


    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t pop(Frame *);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t pop2(Frame *);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t dup(Frame *);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t dup2(Frame *);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t dup_x1(Frame *);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t dup_x2(Frame *);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t dup2_x1(Frame *);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t dup2_x2(Frame *);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t swap(Frame *);


    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t new_func(Frame*);


    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t ifnonnull(Frame*);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t ifnull(Frame*);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t goto_w(Frame*);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t jsr_w(Frame*);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t nop(Frame*);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t tableswitch(Frame*);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t lookupswitch(Frame*);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t aconst_null(Frame*);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t anewarray(Frame*);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t arraylength(Frame*);

    /**
    Instrução aaload: Carrega um valor do tipo referência de um array.

    Recupera um elemento do tipo referência de um array (que é do tipo referência). Tanto o index quanto  o array
    são recuperados da pilha de operandos.
    O elemento é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t aaload(Frame *);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t aastore(Frame *);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t multianewarray(Frame*);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t areturn(Frame *);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t freturn(Frame *);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t aload(Frame *);

    /**
     * \brief EETA
     *
     * \date Date: 29/11/2019
     */
    static vector<Type>* buildArray(vector<int32_t> dim, int index, char type);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t wide(Frame*);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t saload(Frame *);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    // static uint32_t putfield(Frame * );

};


#endif
