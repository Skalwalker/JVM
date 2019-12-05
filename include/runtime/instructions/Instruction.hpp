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
    static map<string, Type>* instantiateFields(ClassFile*);

    static uint32_t monitorenter(Frame*);
    static uint32_t monitorexit(Frame*);
    static uint32_t ldc_w(Frame*);

    /**
     * \brief Instrução getstatic: Inicia classe ou interface indicada por field.
     *
     * Recupera dois valores do atributo code de codeAttribute que são concatenados para indicar um index
     * na constant pool do .class sendo executado. Checa se o item da posição indicada por index é uma
     * referência simbólica para um field válido, carregando a classe correspondente com o classLoader.
     * O valor field da classe ou interface é empilhada na pilha de operandos.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t getstatic(Frame*);

    /**
     * \brief Instrução ldc: Empilha item da constant pool na pilha de operandos.
     *
     * Recupera o valor index de code do codeAttribute que indica posição da constant pool do .class
     * sendo executado. O elemento indicado por index deve ser uma constante do tipo int, float ou
     * reference. Se tipo int ou float, o valor é empilhado na pilha de operandos. Se tipo reference,
     * empilha a string literal indicada por reference na pilha de operandos.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t ldc(Frame*);

    /**
     * \brief Instrução ldc2_w: Empilha item (long ou double) da constant pool na pilha de operandos.
     *
     * Recupera dois valores de code do codeAttribute, que são concatenados para formar um index. O index
     * indica uma posição da constant pool do .class sendo executado. O elemento indicado por index deve
     * ser uma constante do tipo long ou double.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t ldc2_w(Frame*);

    /**
     * \brief Instrução invokevirtual: Invoca método de um objeto (de instância).
     *
     * Recupera dois valores de code do codeAttribute, que são concatenados para formar um index. O index
     * indica uma posição da constant pool do .class sendo executado. O elemento indicado por index deve
     * ser uma referência simbólica para um método, que fornece o nome, o descritor do método e a referência
     * para sua classe. O método com o nome e descritor correspondente deve ser encontrado na MethodArea.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t invokevirtual(Frame*);

    /**
     * \brief Instrução invokestatic: Invoca método estático de uma classe.
     *
     * Recupera dois valores de code do codeAttribute, que são concatenados para formar um index. O index
     * indica uma posição da constant pool do .class sendo executado. O elemento indicado por index deve
     * ser uma referência para um método, que fornece o nome, o descritor do método e a referência
     * para sua classe. O método deve ser estático.  O método com o nome e descritor correspondente deve ser
     * encontrado na MethodArea.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t invokestatic(Frame*);

    /**
     * \brief Instrução invokespecial: Invoca métodos de instância de inicialização, privados ou de uma superclasse.
     *
     * Recupera dois valores de code do codeAttribute, que são concatenados para formar um index. O index
     * indica uma posição da constant pool do .class sendo executado. O elemento indicado por index deve
     * ser uma referência para um método, que fornece o nome, o descritor do método e a referência
     * para sua classe. O método com o nome e descritor correspondente deve ser encontrado na MethodArea.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t invokespecial(Frame*);

    /**
     * \brief Instrução putfield: Define field em um objeto.
     *
     * Recupera dois valores de code do codeAttribute, que são concatenados para formar um index. O index
     * indica uma posição da constant pool do .class sendo executado. O elemento indicado por index deve
     * ser uma referência simbólica para um field que fornece o nome, o descritor do field e a referência
     * para sua classe.
     * Recupera da pilha de operandos value, que deve de um tipo compatível tipo do descritor do field, e
     * recupera também a referência ao objeto e o define com o valor value.
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

    static uint32_t putstatic(Frame*);

    /**
     * \brief
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */

    static uint32_t getfield(Frame*);

    /**
     * \brief Instrução return: De um método, retorna void.
     *
     * Retorna para o invocador do método, ou seja, retorna ao frame do invocador.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */

    static uint32_t returnfunc(Frame*);

    /**
     * \brief Instrução ireturn: De um método, retorna int.
     *
     * Recupera o valor inteiro value a ser retornado da pilha de operandos do método sendo executado. Desempilha um
     * frame da JVMStack, retornando assim ao ambiente do invocador do método. Value é empilhado na pilha de
     * operando do método sendo executado.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t ireturn(Frame*);

    /**
     * \brief Instrução lreturn: De um método, retorna long.
     *
     * Recupera o valor long value a ser retornado da pilha de operandos do método sendo executado. Desempilha um
     * frame da JVMStack, retornando assim ao ambiente do invocador do método. Value é empilhado na pilha de
     * operando do método sendo executado.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t lreturn(Frame*);

    /**
     * \brief Instrução dreturn: De um método, retorna double.
     *
     * Recupera o valor double value a ser retornado da pilha de operandos do método sendo executado. Desempilha um
     * frame da JVMStack, retornando assim ao ambiente do invocador do método. Value é empilhado na pilha de
     * operando do método sendo executado.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t dreturn(Frame*);

    /**
    \brief Instrução ladd: Soma longs.

    Recupera os valores a serem somados da pilha de operandos do método sendo executado.
    O resultado da soma é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t ladd(Frame*);

    /**
    \brief Instrução lsub: Subtrai longs.

    Recupera os valores a serem somados da pilha de operandos do método sendo executado.
    O resultado da subtração é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t lsub(Frame*);

    /**
    \brief Instrução lmul: Multiplica longs.

    Recupera os valores a serem multiplicados da pilha de operandos do método sendo executado.
    O resultado da multiplicação é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t lmul(Frame*);

    /**
    \brief Instrução ldiv: Divide longs.

    Recupera os valores a serem divididos da pilha de operandos do método sendo executado.
    O resultado da divisão é empilhado na pilha de operandos. Checa se o divisor é 0.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t ldiv(Frame*);

    /**
    \brief Instrução lneg: Torna número long negativo.

    Recupera o valor a ser trocado para o seu negativo da pilha de operandos do método sendo executado.
    O número negativo é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t lneg(Frame*);

    /**
    \brief Instrução lrem: Resto de divisão de longs.

    Recupera os valores a serem divididos da pilha de operandos do método sendo executado.
    O resto da divisão (value1 - (value1 / value2) * value2) é empilhado na pilha de operandos. Checa se o divisor é 0.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t lrem(Frame*);

    /**
    \brief Instrução lshl: Desloca s bits para esquerda de um valor long.

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
    \brief Instrução lshr: Desloca s bits para direita de um valor long.

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
    \brief Instrução land: Operação AND entre longs.

    Recupera os valores para operação (value1 AND value2) da pilha de operandos do método sendo executado.
    O resultado da operação é empilhado na pilha de operandos.


    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t land(Frame*);

    /**
    \brief Instrução lor: Operação OR entre longs.

    Recupera os valores para operação (value1 OR value2) da pilha de operandos do método sendo executado.
    O resultado da operação é empilhado na pilha de operandos.


    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t lor(Frame*);

    /**
    \brief Instrução lxor: Operação XOR entre longs.

    Recupera os valores para operação (value1 OR value2) da pilha de operandos do método sendo executado.
    O resultado da operação é empilhado na pilha de operandos.


    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t lxor(Frame*);

    /**
    \brief Instrução iadd: Soma inteiros.

    Recupera os valores a serem somados da pilha de operandos do método sendo executado.
    O resultado da soma é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t iadd(Frame*);

    /**
    \brief Instrução isub: Subtrai inteiros.

    Recupera os valores a serem somados da pilha de operandos do método sendo executado.
    O resultado da subtração é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t isub(Frame *);

    /**
    \brief Instrução imul: Multiplica inteiros.

    Recupera os valores a serem multiplicados da pilha de operandos do método sendo executado.
    O resultado da multiplicação é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t imul(Frame *);

    /**
    \brief Instrução idiv: Divide inteiros.

    Recupera os valores a serem divididos da pilha de operandos do método sendo executado.
    O resultado da divisão é empilhado na pilha de operandos. Checa se o divisor é 0.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t idiv(Frame *);

    /**
    \brief Instrução irem: Resto de divisão de inteiros.

    Recupera os valores a serem divididos da pilha de operandos do método sendo executado.
    O resto da divisão (value1 - (value1 / value2) * value2) é empilhado na pilha de operandos. Checa se o divisor é 0.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t irem(Frame *);

    /**
    \brief Instrução ineg: Torna número inteiro negativo.

    Recupera o valor a ser trocado para o seu negativo da pilha de operandos do método sendo executado.
    O número negativo é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t ineg(Frame *);

    /**
    \brief Instrução ishl: Desloca s bits para esquerda de inteiro.

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
    \brief Instrução ishr: Desloca s bits para direita de inteiro.

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
    \brief Instrução uishl: Desloca s bits para esquerda de inteiro (Deslocamento lógico).

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
    \brief Instrução iand: Operação AND entre inteiros.

    Recupera os valores para operação (value1 AND value2) da pilha de operandos do método sendo executado.
    O resultado da operação é empilhado na pilha de operandos.


    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t iand(Frame*);

    /**
    \brief Instrução ior: Operação OR entre inteiros.

    Recupera os valores para operação (value1 OR value2) da pilha de operandos do método sendo executado.
    O resultado da operação é empilhado na pilha de operandos.


    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t ior(Frame*);

    /**
    \brief Instrução ixor: Operação XOR entre inteiros.

    Recupera os valores para operação (value1 XOR value2) da pilha de operandos do método sendo executado.
    O resultado da operação é empilhado na pilha de operandos.


    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t ixor(Frame*);

    /**
    \brief Instrução iinc: Incrementa por uma constante uma variável local.

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
    \brief Instrução fadd: Soma floats.

    Recupera os valores a serem somados da pilha de operandos do método sendo executado.
    O resultado da soma é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t fadd(Frame *);

    /**
    \brief Instrução fsub: Subtrai floats.

    Recupera os valores a serem somados da pilha de operandos do método sendo executado.
    O resultado da subtração é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t fsub(Frame *);

    /**
    \brief Instrução fmul: Multiplica floats.

    Recupera os valores a serem multiplicados da pilha de operandos do método sendo executado.
    O resultado da multiplicação é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t fmul(Frame *);

    /**
    \brief Instrução fdiv: Divide floats.

    Recupera os valores a serem divididos da pilha de operandos do método sendo executado.
    O resultado da divisão é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t fdiv(Frame *);

    /**
    \brief Instrução frem: Resto de divisão de floats.

    Recupera os valores a serem divididos da pilha de operandos do método sendo executado.
    O resto da divisão é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t frem(Frame *);

    /**
    \brief Instrução fneg: Torna número float negativo.

    Recupera o valor a ser trocado para o seu negativo da pilha de operandos do método sendo executado.
    O número negativo é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t fneg(Frame *);

    /**
     * \brief Instrução bipush: Empilha byte.
     *
     * Recupera valor (byte) do atributo code de codeAttribute. Empilha o valor na pilha de operandos.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t bipush(Frame*);

    /**
     * \brief Instrução sipush: Empilha short.
     *
     * Recupera dois valores (byte) do atributo code de codeAttribute. Os valores são concatenados para
     * formar um valor do tipo short. Empilha o valor short na pilha de operandos.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t sipush(Frame*);


    /**
    \brief Instrução dadd: Soma doubles.

    Recupera os valores a serem somados da pilha de operandos do método sendo executado.
    O resultado da soma é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t dadd(Frame *);

    /**
    \brief Instrução dsub: Subtrai doubles.

    Recupera os valores a serem somados da pilha de operandos do método sendo executado.
    O resultado da subtração é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t dsub(Frame *);

    /**
    \brief Instrução dmul: Multiplica doubles.

    Recupera os valores a serem multiplicados da pilha de operandos do método sendo executado.
    O resultado da multiplicação é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t dmul(Frame *);

    /**
    \brief Instrução ddiv: Divide doubles.

    Recupera os valores a serem divididos da pilha de operandos do método sendo executado.
    O resultado da divisão é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t ddiv(Frame *);

    /**
    \brief Instrução drem: Resto de divisão de doubles.

    Recupera os valores a serem divididos da pilha de operandos do método sendo executado.
    O resto da divisão é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t drem(Frame *);

    /**
    \brief Instrução dneg: Torna número double negativo.

    Recupera o valor a ser trocado para o seu negativo da pilha de operandos do método sendo executado.
    O número negativo é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t dneg(Frame *);


    /**
     * \brief Instrução fstore: Guarda float no vetor de variáveis locais.
     *
     * Recupera do atributo code de codeAttribute o valor index. Recupera da pilha de operandos o valor
     * value do tipo float. Guarda value no vetor de variáveis locais na posição indicada por index.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t fstore(Frame *);

    /**
     * \brief Instrução fstore_0: Guarda float no vetor de variáveis locais na posição 0.
     *
     * Do grupo de instruções fstore_<n>, recupera o valor do tipo float da pilha de operandos e guarda no vetor de
     * variáveis locais da posição indicada por n.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t fstore_0(Frame *);

    /**
     * \brief Instrução fstore_1: Guarda float no vetor de variáveis locais na posição 1.
     *
     * Do grupo de instruções fstore_<n>, recupera o valor do tipo float da pilha de operandos e guarda no vetor de
     * variáveis locais da posição indicada por n.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t fstore_1(Frame *);

    /**
     * \brief Instrução fstore_2: Guarda float no vetor de variáveis locais na posição 2.
     *
     * Do grupo de instruções fstore_<n>, recupera o valor do tipo float da pilha de operandos e guarda no vetor de
     * variáveis locais da posição indicada por n.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t fstore_2(Frame *);

    /**
     * \brief Instrução fstore_3: Guarda float no vetor de variáveis locais na posição 3.
     *
     * Do grupo de instruções fstore_<n>, recupera o valor do tipo float da pilha de operandos e guarda no vetor de
     * variáveis locais da posição indicada por n.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t fstore_3(Frame *);


    /**
     * \brief Instrução lstore: Guarda long no vetor de variáveis locais.
     *
     * Recupera do atributo code de codeAttribute o valor index. Recupera da pilha de operandos o valor
     * value do tipo long. Guarda value no vetor de variáveis locais na posição indicada por index.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t lstore(Frame *);

    /**
     * \brief Instrução lstore_0: Guarda long no vetor de variáveis locais na posição 0.
     *
     * Do grupo de instruções lstore_<n>, recupera o valor do tipo long da pilha de operandos e guarda no vetor de
     * variáveis locais da posição indicada por n.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t lstore_0(Frame *);

    /**
     * \brief Instrução lstore_1: Guarda long no vetor de variáveis locais na posição 1.
     *
     * Do grupo de instruções lstore_<n>, recupera o valor do tipo long da pilha de operandos e guarda no vetor de
     * variáveis locais da posição indicada por n.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t lstore_1(Frame *);

    /**
     * \brief Instrução lstore_2: Guarda long no vetor de variáveis locais na posição 2.
     *
     * Do grupo de instruções lstore_<n>, recupera o valor do tipo long da pilha de operandos e guarda no vetor de
     * variáveis locais da posição indicada por n.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t lstore_2(Frame *);

    /**
     * \brief Instrução lstore_3: Guarda long no vetor de variáveis locais na posição 3.
     *
     * Do grupo de instruções lstore_<n>, recupera o valor do tipo long da pilha de operandos e guarda no vetor de
     * variáveis locais da posição indicada por n.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t lstore_3(Frame *);


    /**
     * \brief Instrução istore: Guarda int no vetor de variáveis locais.
     *
     * Recupera do atributo code de codeAttribute o valor index. Recupera da pilha de operandos o valor
     * value do tipo int. Guarda value no vetor de variáveis locais na posição indicada por index.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t istore(Frame *);

    /**
     * \brief Instrução istore_0: Guarda inteiro no vetor de variáveis locais na posição 0.
     *
     * Do grupo de instruções istore_<n>, recupera o valor do tipo inteiro da pilha de operandos e guarda no vetor de
     * variáveis locais da posição indicada por n.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t istore_0(Frame *);

    /**
     * \brief Instrução istore_1: Guarda inteiro no vetor de variáveis locais na posição 1.
     *
     * Do grupo de instruções istore_<n>, recupera o valor do tipo inteiro da pilha de operandos e guarda no vetor de
     * variáveis locais da posição indicada por n.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t istore_1(Frame *);

    /**
     * \brief Instrução istore_2: Guarda inteiro no vetor de variáveis locais na posição 2.
     *
     * Do grupo de instruções istore_<n>, recupera o valor do tipo inteiro da pilha de operandos e guarda no vetor de
     * variáveis locais da posição indicada por n.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t istore_2(Frame *);

    /**
     * \brief Instrução istore_3: Guarda inteiro no vetor de variáveis locais na posição 3.
     *
     * Do grupo de instruções istore_<n>, recupera o valor do tipo inteiro da pilha de operandos e guarda no vetor de
     * variáveis locais da posição indicada por n.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t istore_3(Frame *);


    /**
     * \brief Instrução dstore: Guarda double no vetor de variáveis locais.
     *
     * Recupera do atributo code de codeAttribute o valor index. Recupera da pilha de operandos o valor
     * value do tipo double. Guarda value no vetor de variáveis locais na posição indicada por index.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t dstore(Frame *);

    /**
     * \brief Instrução dstore_0: Guarda double no vetor de variáveis locais na posição 0.
     *
     * Do grupo de instruções dstore_<n>, recupera o valor do tipo double da pilha de operandos e guarda no vetor de
     * variáveis locais da posição indicada por n.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t dstore_0(Frame *);

    /**
     * \brief Instrução dstore_1: Guarda double no vetor de variáveis locais na posição 1.
     *
     * Do grupo de instruções dstore_<n>, recupera o valor do tipo double da pilha de operandos e guarda no vetor de
     * variáveis locais da posição indicada por n.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t dstore_1(Frame *);

    /**
     * \brief Instrução dstore_2: Guarda double no vetor de variáveis locais na posição 2.
     *
     * Do grupo de instruções dstore_<n>, recupera o valor do tipo double da pilha de operandos e guarda no vetor de
     * variáveis locais da posição indicada por n.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t dstore_2(Frame *);

    /**
     * \brief Instrução dstore_3: Guarda double no vetor de variáveis locais na posição 3.
     *
     * Do grupo de instruções dstore_<n>, recupera o valor do tipo double da pilha de operandos e guarda no vetor de
     * variáveis locais da posição indicada por n.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t dstore_3(Frame *);


    /**
     * \brief Instrução iastore: Guarda inteiro em um array de inteiros.
     *
     * Recupera o valor inteiro a ser empilhado, a referência para o array de inteiros e o index da
     * pilha de operandos. Checa se o array indicado pela referência existe e se a posição do array
     * indicada por index é válida e guarda o valor no array na posição index.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t iastore(Frame *);

    /**
     * \brief Instrução dastore: Guarda double em um array de doubles.
     *
     * Recupera o valor double a ser empilhado, a referência para o array de doubles e o index da
     * pilha de operandos. Checa se o array indicado pela referência existe e se a posição do array
     * indicada por index é válida e guarda o valor no array na posição index.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t dastore(Frame *);

    /**
     * \brief Instrução fastore: Guarda float em um array de floats.
     *
     * Recupera o valor float a ser empilhado, a referência para o array de doubles e o index da
     * pilha de operandos. Checa se o array indicado pela referência existe e se a posição do array
     * indicada por index é válida e guarda o valor no array na posição index.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t fastore(Frame *);

    /**
     * \brief Instrução castore: Guarda char em um array de chars.
     *
     * Recupera o valor char a ser empilhado, a referência para o array de chars e o index da
     * pilha de operandos. Checa se o array indicado pela referência existe e se a posição do array
     * indicada por index é válida e guarda o valor no array na posição index.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t castore(Frame *);

    /**
     * \brief Instrução sastore: Guarda short em um array de shorts.
     *
     * Recupera o valor short a ser empilhado, a referência para o array de shorts e o index da
     * pilha de operandos. Checa se o array indicado pela referência existe e se a posição do array
     * indicada por index é válida e guarda o valor no array na posição index.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t sastore(Frame *);

    /**
     * \brief Instrução lastore: Guarda long em um array de longs.
     *
     * Recupera o valor long a ser empilhado, a referência para o array de longs e o index da
     * pilha de operandos. Checa se o array indicado pela referência existe e se a posição do array
     * indicada por index é válida e guarda o valor no array na posição index.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t lastore(Frame *);

    /**
     * \brief Instrução bastore: Guarda byte ou boolean em um array de bytes ou booleans.
     *
     * Recupera o valor byte ou boolean a ser empilhado, a referência para o array de bytes ou booleans
     * e o index da pilha de operandos. Checa se o array indicado pela referência existe e se a posição
     * do array indicada por index é válida e guarda o valor no array na posição index.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t bastore(Frame *);

    /**
     * \brief Instrução astore: Guarda reference no vetor de variáveis locais.
     *
     * Recupera o valor reference a ser empilhado e o index da pilha de operandos. Guarda o valor no
     * vetor de variáveis locais na posição indicada por index.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t astore(Frame *);

    /**
     * \brief Instrução astore_0: Guarda reference no vetor de variáveis locais na posição 0.
     *
     * Do grupo de instruções astore_<n>, recupera o valor do tipo reference da pilha de operandos e guarda no vetor de
     * variáveis locais da posição indicada por n.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t astore_0(Frame *);

    /**
     * \brief Instrução astore_1: Guarda reference no vetor de variáveis locais na posição 1.
     *
     * Do grupo de instruções astore_<n>, recupera o valor do tipo reference da pilha de operandos e guarda no vetor de
     * variáveis locais da posição indicada por n.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t astore_1(Frame *);

    /**
     * \brief Instrução astore_2: Guarda reference no vetor de variáveis locais na posição 2.
     *
     * Do grupo de instruções astore_<n>, recupera o valor do tipo reference da pilha de operandos e guarda no vetor de
     * variáveis locais da posição indicada por n.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t astore_2(Frame *);

    /**
     * \brief Instrução astore_3: Guarda reference no vetor de variáveis locais na posição 3.
     *
     * Do grupo de instruções astore_<n>, recupera o valor do tipo reference da pilha de operandos e guarda no vetor de
     * variáveis locais da posição indicada por n.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t astore_3(Frame *);


    /**
    \brief Instrução lload: Carrega um valor long.

    Recupera um elemento long do vetor de variáveis locais da posição indicada por index.
    Index é recuperado do atributo code de codeAttribute definido em AttributeInfo.cpp.
    O valor é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t lload(Frame *);

    /**
    \brief Instrução lload_0: Carrega um valor long.

    Do grupo de instruções lload_<n>, recupera um elemento long do vetor de variáveis locais da posição
    indicada por n.
    O valor é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t lload_0(Frame *);

    /**
    \brief Instrução lload_1: Carrega um valor long.

    Do grupo de instruções lload_<n>, recupera um elemento long do vetor de variáveis locais da posição
    indicada por n.
    O valor é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t lload_1(Frame *);

    /**
    \brief Instrução lload_2: Carrega um valor long.

    Do grupo de instruções lload_<n>, recupera um elemento long do vetor de variáveis locais da posição
    indicada por n.
    O valor é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t lload_2(Frame *);

    /**
    \brief Instrução lload_3: Carrega um valor long.

    Do grupo de instruções lload_<n>, recupera um elemento long do vetor de variáveis locais da posição
    indicada por n.
    O valor é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t lload_3(Frame *);


    /**
    \brief Instrução aload_0: Carrega um valor do tipo referência.

    Do grupo de instruções aload_<n>, recupera um elemento do tipo referência do vetor de variáveis locais da posição
    indicada por n.
    O valor é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t aload_0(Frame *);

    /**
    \brief Instrução aload_1: Carrega um valor do tipo referência.

    Do grupo de instruções aload_<n>, recupera um elemento do tipo referência do vetor de variáveis locais da posição
    indicada por n.
    O valor é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t aload_1(Frame *);

    /**
    \brief Instrução aload_2: Carrega um valor do tipo referência.

    Do grupo de instruções aload_<n>, recupera um elemento do tipo referência do vetor de variáveis locais da posição
    indicada por n.
    O valor é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t aload_2(Frame *);

    /**
    \brief Instrução aload_3: Carrega um valor do tipo referência.

    Do grupo de instruções aload_<n>, recupera um elemento do tipo referência do vetor de variáveis locais da posição
    indicada por n.
    O valor é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t aload_3(Frame *);

    /**
     * \brief Instrução iaload: Carrega um valor do tipo inteiro de um array.
     *
     * Recupera a referência para o array de inteiros e o index da pilha de operandos. Checa se o array indicado pela
     * referência existe e se a posição do array indicada por index é válida. Recupera o elemento da posição index do
     * array e empilha na pilha de operandos.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t iaload(Frame *);

    /**
    \brief Instrução faload: Carrega um valor do tipo float de um array.

    Recupera a referência para o array de floats e o index da pilha de operandos. Checa se o array indicado pela
    referência existe e se a posição do array indicada por index é válida. Recupera o elemento da posição index do
    array e empilha na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t faload(Frame *);

    /**
     * \brief Instrução laload: Carrega um valor do tipo long de um array.
     *
     * Recupera a referência para o array de long e o index da pilha de operandos. Checa se o array indicado pela
     * referência existe e se a posição do array indicada por index é válida. Recupera o elemento da posição index do
     * array e empilha na pilha de operandos.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t laload(Frame *);

    /**
     * \brief Instrução daload: Carrega um valor do tipo double de um array.
     *
     * Recupera a referência para o array de double e o index da pilha de operandos. Checa se o array indicado pela
     * referência existe e se a posição do array indicada por index é válida. Recupera o elemento da posição index do
     * array e empilha na pilha de operandos.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t daload(Frame *);

    /**
     * \brief Instrução baload: Carrega um valor do tipo byte ou boolean de um array.
     *
     * Recupera a referência para o array de bytes ou booleans e o index da pilha de operandos. Checa se o array indicado pela
     * referência existe e se a posição do array indicada por index é válida. Recupera o elemento da posição index do
     * array e empilha na pilha de operandos.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t baload(Frame *);

    /**
     * \brief Instrução caload: Carrega um valor do tipo char de um array.
     *
     * Recupera a referência para o array de char e o index da pilha de operandos. Checa se o array indicado pela
     * referência existe e se a posição do array indicada por index é válida. Recupera o elemento da posição index do
     * array e empilha na pilha de operandos.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t caload(Frame *);



    /**
    \brief Instrução fload: Carrega um valor float.

    Recupera um elemento float do vetor de variáveis locais da posição indicada por index.
    Index é recuperado do atributo code de codeAttribute definido em AttributeInfo.cpp.
    O valor é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t fload(Frame *);

    /**
    \brief Instrução fload_0: Carrega um valor float.

    Do grupo de instruções fload_<n>, recupera um elemento float do vetor de variáveis locais da posição
    indicada por n.
    O valor é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t fload_0(Frame *);

    /**
    \brief Instrução fload_1: Carrega um valor float.

    Do grupo de instruções fload_<n>, recupera um elemento float do vetor de variáveis locais da posição
    indicada por n.
    O valor é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t fload_1(Frame *);

    /**
    \brief Instrução fload_2: Carrega um valor float.

    Do grupo de instruções fload_<n>, recupera um elemento float do vetor de variáveis locais da posição
    indicada por n.
    O valor é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t fload_2(Frame *);

    /**
    \brief Instrução fload_3: Carrega um valor float.

    Do grupo de instruções fload_<n>, recupera um elemento float do vetor de variáveis locais da posição
    indicada por n.
    O valor é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t fload_3(Frame *);


    /**
    \brief Instrução fload: Carrega um valor inteiro.

    Recupera um elemento inteiro do vetor de variáveis locais da posição indicada por index.
    Index é recuperado do atributo code de codeAttribute definido em AttributeInfo.cpp.
    O valor é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t iload(Frame *);

    /**
    \brief Instrução iload_0: Carrega um valor inteiro.

    Do grupo de instruções iload_<n>, recupera um elemento inteiro do vetor de variáveis locais da posição
    indicada por n.
    O valor é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t iload_0(Frame *);

    /**
    \brief Instrução iload_1: Carrega um valor inteiro.

    Do grupo de instruções iload_<n>, recupera um elemento inteiro do vetor de variáveis locais da posição
    indicada por n.
    O valor é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t iload_1(Frame *);

    /**
    \brief Instrução iload_2: Carrega um valor inteiro.

    Do grupo de instruções iload_<n>, recupera um elemento inteiro do vetor de variáveis locais da posição
    indicada por n.
    O valor é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t iload_2(Frame *);

    /**
    \brief Instrução iload_3: Carrega um valor inteiro.

    Do grupo de instruções iload_<n>, recupera um elemento inteiro do vetor de variáveis locais da posição
    indicada por n.
    O valor é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t iload_3(Frame *);


    /**
    \brief Instrução dload: Carrega um valor double.

    Recupera um elemento double do vetor de variáveis locais da posição indicada por index.
    Index é recuperado do atributo code de codeAttribute definido em AttributeInfo.cpp.
    O valor é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t dload(Frame *);

    /**
    \brief Instrução dload_0: Carrega um valor double.

    Do grupo de instruções dload_<n>, recupera um elemento double do vetor de variáveis locais da posição
    indicada por n.
    O valor é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t dload_0(Frame *);

    /**
    \brief Instrução dload_1: Carrega um valor double.

    Do grupo de instruções dload_<n>, recupera um elemento double do vetor de variáveis locais da posição
    indicada por n.
    O valor é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t dload_1(Frame *);

    /**
    \brief Instrução dload_2: Carrega um valor double.

    Do grupo de instruções dload_<n>, recupera um elemento double do vetor de variáveis locais da posição
    indicada por n.
    O valor é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t dload_2(Frame *);

    /**
    \brief Instrução dload_3: Carrega um valor double.

    Do grupo de instruções dload_<n>, recupera um elemento double do vetor de variáveis locais da posição
    indicada por n.
    O valor é empilhado na pilha de operandos.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t dload_3(Frame *);


    /**
     * \brief Instrução iconst_m1: Empilha o valor constante -1.
     *
     * Empilha na pilha de operandos -1.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t iconst_m1(Frame *);

    /**
     * \brief Instrução iconst_0: Empilha o valor constante 0.
     *
     * Do grupo de instruções iconst_<n>, empilha na pilha de operandos o valor <n>.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t iconst_0(Frame *);

    /**
     * \brief Instrução iconst_1: Empilha o valor inteiro constante 1.
     *
     * Do grupo de instruções iconst_<n>, empilha na pilha de operandos o valor <n>.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t iconst_1(Frame *);

    /**
     * \brief Instrução iconst_2: Empilha o valor inteiro constante 2.
     *
     * Do grupo de instruções iconst_<n>, empilha na pilha de operandos o valor <n>.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t iconst_2(Frame *);

    /**
     * \brief Instrução iconst_3: Empilha o valor inteiro constante 3.
     *
     * Do grupo de instruções iconst_<n>, empilha na pilha de operandos o valor <n>.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t iconst_3(Frame *);

    /**
     * \brief Instrução iconst_4: Empilha o valor inteiro constante 4.
     *
     * Do grupo de instruções iconst_<n>, empilha na pilha de operandos o valor <n>.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t iconst_4(Frame *);

    /**
     * \brief Instrução iconst_5: Empilha o valor inteiro constante 5.
     *
     * Do grupo de instruções iconst_<n>, empilha na pilha de operandos o valor <n>.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t iconst_5(Frame *);

    /**
     * \brief Instrução lconst_0: Empilha o valor long constante 0.
     *
     * Do grupo de instruções lconst_<n>, empilha na pilha de operandos o valor <n>.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t lconst_0(Frame *);

    /**
     * \brief Instrução lconst_1: Empilha o valor long constante 1.
     *
     * Do grupo de instruções lconst_<n>, empilha na pilha de operandos o valor <n>.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t lconst_1(Frame *);

    /**
     * \brief Instrução dconst_0: Empilha o valor double constante 0.
     *
     * Do grupo de instruções dconst_<n>, empilha na pilha de operandos o valor <n>.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t dconst_0(Frame *);

    /**
     * \brief Instrução dconst_1: Empilha o valor double constante 1.
     *
     * Do grupo de instruções dconst_<n>, empilha na pilha de operandos o valor <n>.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t dconst_1(Frame *);

    /**
     * \brief Instrução fconst_0: Empilha o valor float constante 0.
     *
     * Do grupo de instruções fconst_<n>, empilha na pilha de operandos o valor <n>.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t fconst_0(Frame *);

    /**
     * \brief Instrução fconst_1: Empilha o valor float constante 1.
     *
     * Do grupo de instruções fconst_<n>, empilha na pilha de operandos o valor <n>.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t fconst_1(Frame *);

    /**
     * \brief Instrução fconst_2: Empilha o valor float constante 2.
     *
     * Do grupo de instruções fconst_<n>, empilha na pilha de operandos o valor <n>.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t fconst_2(Frame *);


    /**
     * \brief Instrução lcmp: Compara valores do tipo long.
     *
     * Recupera dois valores, val1 e val2, da pilha de operandos e realiza uma comparação considerando o sinal.
     * Empilha na pilha de operandos o valor 1, se val1 > val2, 0, se val1 = val2 e -1, se val1 < val2.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t lcmp(Frame*);

    /**
     * \brief Instrução ifle: Branch se valor menor ou igual a zero.
     *
     * Recupera valor value do tipo inteiro da pilha de operandos. Recupera dois valores de do atributo code de
     * codeAttribute, que são concatenados para formar o offset que indica o endereço a ser seguido caso a comparação
     * seja satisfeita.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t ifle(Frame*);

    /**
     * \brief Instrução ifge: Branch se valor maior ou igual a zero.
     *
     * Recupera valor value do tipo inteiro da pilha de operandos. Recupera dois valores de do atributo code de
     * codeAttribute, que são concatenados para formar o offset que indica o endereço a ser seguido caso a comparação
     * seja satisfeita.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t ifge(Frame*);

    /**
     * \brief Instrução ifeq: Branch se valor igual a zero.
     *
     * Recupera valor value do tipo inteiro da pilha de operandos. Recupera dois valores de do atributo code de
     * codeAttribute, que são concatenados para formar o offset que indica o endereço a ser seguido caso a comparação
     * seja satisfeita.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t ifeq(Frame*);

    /**
     * \brief Instrução ifne: Branch se valor diferente a zero.
     *
     * Recupera valor value do tipo inteiro da pilha de operandos. Recupera dois valores de do atributo code de
     * codeAttribute, que são concatenados para formar o offset que indica o endereço a ser seguido caso a comparação
     * seja satisfeita.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t ifne(Frame*);

    /**
     * \brief Instrução iflt: Branch se valor menor que zero.
     *
     * Recupera valor value do tipo inteiro da pilha de operandos. Recupera dois valores de do atributo code de
     * codeAttribute, que são concatenados para formar o offset que indica o endereço a ser seguido caso a comparação
     * seja satisfeita.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t iflt(Frame*);

    /**
     * \brief Instrução ifgt: Branch se valor maior que zero.
     *
     * Recupera valor value do tipo inteiro da pilha de operandos. Recupera dois valores de do atributo code de
     * codeAttribute, que são concatenados para formar o offset que indica o endereço a ser seguido caso a comparação
     * seja satisfeita.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t ifgt(Frame*);

    /**
     * \brief Instrução fcmpl: Compara valores do tipo float.
     *
     * Recupera dois valores, val1 e val2, da pilha de operandos e realiza comparação.
     * Empilha na pilha de operandos o valor 1, se val1 > val2, 0, se val1 = val2 e -1, se val1 < val2 ou
     * se algum dos valores for NaN.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t fcmpl(Frame*);

    /**
     * \brief Instrução fcmpg: Compara valores do tipo float.
     *
     * Recupera dois valores, val1 e val2, da pilha de operandos e realiza comparação.
     * Empilha na pilha de operandos o valor 1, se val1 > val2 ou se algum dos valores for NaN, 0, se
     * val1 = val2 e -1, se val1 < val2.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t fcmpg(Frame*);

    /**
     * \brief Instrução dcmpl: Compara valores do tipo double.
     *
     * Recupera dois valores, val1 e val2, da pilha de operandos e realiza comparação.
     * Empilha na pilha de operandos o valor 1, se val1 > val2, 0, se val1 = val2 e -1, se val1 < val2 ou
     * se algum dos valores for NaN.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t dcmpl(Frame*);

    /**
     * \brief Instrução dcmpg: Compara valores do tipo double.
     *
     * Recupera dois valores, val1 e val2, da pilha de operandos e realiza comparação.
     * Empilha na pilha de operandos o valor 1, se val1 > val2 ou se algum dos valores for NaN, 0, se
     * val1 = val2 e -1, se val1 < val2.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t dcmpg(Frame*);

    /**
     * \brief Instrução if_icmpeq: Branch se valores iguais.
     *
     * Recupera dois valores do tipo inteiro da pilha de operandos. Recupera dois valores de do atributo code de
     * codeAttribute, que são concatenados para formar o offset que indica o endereço a ser seguido caso a comparação
     * seja satisfeita.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t if_icmpeq(Frame*);

    /**
     * \brief Instrução if_icmpne: Branch se valores diferentes.
     *
     * Recupera dois valores do tipo inteiro da pilha de operandos. Recupera dois valores de do atributo code de
     * codeAttribute, que são concatenados para formar o offset que indica o endereço a ser seguido caso a comparação
     * seja satisfeita.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t if_icmpne(Frame*);

    /**
     * \brief Instrução if_icmplt: Branch se valor1 menor que valor2.
     *
     * Recupera dois valores do tipo inteiro da pilha de operandos. Recupera dois valores de do atributo code de
     * codeAttribute, que são concatenados para formar o offset que indica o endereço a ser seguido caso a comparação
     * seja satisfeita.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t if_icmplt(Frame*);

    /**
     * \brief Instrução if_icmpge: Branch se valor1 menor ou igual a valor2.
     *
     * Recupera dois valores do tipo inteiro da pilha de operandos. Recupera dois valores de do atributo code de
     * codeAttribute, que são concatenados para formar o offset que indica o endereço a ser seguido caso a comparação
     * seja satisfeita.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t if_icmpge(Frame*);

    /**
     * \brief Instrução if_icmpgt: Branch se valor1 maior que valor2.
     *
     * Recupera dois valores do tipo inteiro da pilha de operandos. Recupera dois valores de do atributo code de
     * codeAttribute, que são concatenados para formar o offset que indica o endereço a ser seguido caso a comparação
     * seja satisfeita.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t if_icmpgt(Frame*);

    /**
     * \brief Instrução if_icmple: Branch se valor1 maior ou igual a valor2.
     *
     * Recupera dois valores do tipo inteiro da pilha de operandos. Recupera dois valores de do atributo code de
     * codeAttribute, que são concatenados para formar o offset que indica o endereço a ser seguido caso a comparação
     * seja satisfeita.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t if_icmple(Frame*);

    /**
     * \brief Instrução if_acmpeq: Branch se valor1 igual a valor2.
     *
     * Recupera dois valores do tipo reference da pilha de operandos. Recupera dois valores de do atributo code de
     * codeAttribute, que são concatenados para formar o offset que indica o endereço a ser seguido caso a comparação
     * seja satisfeita.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t if_acmpeq(Frame*);

    /**
     * \brief Instrução if_acmpne: Branch se valor1 diferente de valor2.
     *
     * Recupera dois valores do tipo reference da pilha de operandos. Recupera dois valores de do atributo code de
     * codeAttribute, que são concatenados para formar o offset que indica o endereço a ser seguido caso a comparação
     * seja satisfeita.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t if_acmpne(Frame*);

    /**
     * \brief Instrução if_goto: Branch.
     *
     * Recupera dois valores de do atributo code de codeAttribute, que são concatenados para formar o offset que indica
     * o endereço a ser seguido.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t goto_func(Frame *);


    /**
    \brief Instrução f2d: Converte float para double.

    Recupera o valor a ser convertido da pilha de operandos do método sendo executado.
    O valor é convertido de acordo com a tag definida em Frame.hpp que representa o tipo double.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t f2d(Frame *);

    /**
    \brief Instrução f2i Converte float para int.

    Recupera o valor a ser convertido da pilha de operandos do método sendo executado.
    O valor é convertido de acordo com a tag definida em Frame.hpp que representa o tipo int32_t.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t f2i(Frame *);

    /**
    \brief Instrução f2l: Converte float para long.

    Recupera o valor a ser convertido da pilha de operandos do método sendo executado.
    O valor é convertido de acordo com a tag definida em Frame.hpp que representa o tipo int64_t.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t f2l(Frame *);

    /**
    \brief Instrução d2f: Converte double para float.

    Recupera o valor a ser convertido da pilha de operandos do método sendo executado.
    O valor é convertido de acordo com a tag definida em Frame.hpp que representa o tipo float.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t d2f(Frame *);

    /**
    \brief Instrução d2i: Converte double para int.

    Recupera o valor a ser convertido da pilha de operandos do método sendo executado.
    O valor é convertido de acordo com a tag definida em Frame.hpp que representa o tipo int32_t.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t d2i(Frame *);

    /**
    \brief Instrução d2l: Converte double para long.

    Recupera o valor a ser convertido da pilha de operandos do método sendo executado.
    O valor é convertido de acordo com a tag definida em Frame.hpp que representa o tipo int64_t.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t d2l(Frame *);

    /**
    \brief Instrução l2f: Converte long para float.

    Recupera o valor a ser convertido da pilha de operandos do método sendo executado.
    O valor é convertido de acordo com a tag definida em Frame.hpp que representa o tipo float.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t l2f(Frame *);

    /**
    \brief Instrução l2i: Converte long para int.

    Recupera o valor a ser convertido da pilha de operandos do método sendo executado.
    O valor é convertido de acordo com a tag definida em Frame.hpp que representa o tipo int32_t.

    @param frame Frame correspondente ao método sendo executado.
    @returns Atualização do valor de PC para o próximo Frame que contém o próximo método a ser executado.

    @date Date: 29/11/2019
    */
    static uint32_t l2i(Frame *);

    /**
    \brief Instrução l2d: Converte long para double.

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
    \brief Instrução i2l: Converte int para long.

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
     * \brief Instrução jsr: Pula para subrotina
     *
     * O valor do opcode da instrução imediatamente após a jsr é empilhada na pilha de operandos.
     * Recupera dois valores do atributo code de codeAttribute que são concatenados para gerar um offset
     * de 16 bits. O endereço da próxima instrução executada passada para pc_local é (offset -2)
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t jsr(Frame *);

    /**
     * \brief Instruction ret: Retorna de subrotina.
     *
     * Recupera do atributo code de codeAtributte o valor index. O elemento na posição index do vetor
     * de variáveis deve ser do tipo returnAddress, que indica o próximo endereço a ser seguido.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t ret(Frame *);


    /**
     * \brief Instrução newarray: Cria novo array.
     *
     * Recupera da pilha de operandos o valor count do tipo int que indica o número de elementos do
     * array a ser criado. Cria o array e inicializa os elementos com os valores deafult.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t newarray(Frame *);


    /**
     * \brief Instrução pop: Desempilha da pilha de operandos.
     *
     * O valor deve ser categoria 1.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t pop(Frame *);

    /**
     * \brief Instrução pop2: Desempilha duas vezes da pilha de operandos.
     *
     * Os valores deve ser categoria 1.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t pop2(Frame *);

    /**
     * \brief Instrução dup: Duplica o valor topo da pilha de operandos.
     *
     * O valor deve ser categoria 1.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t dup(Frame *);

    /**
     * \brief Instrução dup2: Duplica um ou dois valores do topo da pilha de operandos.
     *
     * O valor deve ser categoria 2.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t dup2(Frame *);

    /**
     * \brief Instrução dup_x1: Duplica o valor topo da pilha de operandos.
     *
     * O valor deve ser categoria 1. Empilha os valores pilha.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t dup_x1(Frame *);

    /**
     * \brief Instrução dup_x2: Duplica o valor topo da pilha de operandos.
     *
     * Empilha dois ou três valores do topo da pilha.
     * Se o segundo valor duplicado for de categoria 2, somente dois valores empilhados.
     * Se for de caterogia 1, três valores são empilhados.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t dup_x2(Frame *);

    /**
     * \brief Instrução dup2_x1: Duplica um ou dois valores do topo da pilha de operandos.
     *
     * Empilha dois ou três valores do topo da pilha.
     * Se o segundo valor duplicado for de categoria 2, somente dois valores são empilhados.
     * Se for de caterogia 1, três valores são empilhados.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t dup2_x1(Frame *);

    /**
     * \brief Instrução dup2_x2: Duplica um ou dois valores do topo da pilha de operandos.
     *
     * Empilha dois, três ou quatro valores na base da pilha.
     * Se todos os valores forem de categoria 1, empilha os 4 valores da pilha.
     * Se value1 for de categoria 2, empilha os 3 valores da pilha.
     * Se value3 for de categoria 2, empilha os 2 valores da pilha.
     * Se value1 e value2 for de categoria 2, empilha 1 valor da pilha.
     *
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t dup2_x2(Frame *);

    /**
     * \brief Instrução swap: Troca dos dois valores do topo da pilha.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t swap(Frame *);


    /**
     * \brief Instrução new: Cria um novo objeto.
     *
     * Recupera dois valores de code do codeAttribute, que são concatenados para formar um index. O index
     * indica uma posição da constant pool do .class sendo executado. O elemento indicado por index deve
     * ser uma referência simbólica para uma classe. A referência para o objeto criado é empilhado na pilha
     *  de operandos.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t new_func(Frame*);


    /**
     * \brief Instrução ifnonnull: Branch se reference não é null.
     *
     * Recupera valor value do tipo reference da pilha de operandos. Recupera dois valores de do atributo code de
     * codeAttribute, que são concatenados para formar o offset que indica o endereço a ser seguido caso a comparação
     * seja satisfeita.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t ifnonnull(Frame*);

    /**
     * \brief Instrução ifnull: Branch se reference é null.
     *
     * Recupera valor value do tipo reference da pilha de operandos. Recupera dois valores de do atributo code de
     * codeAttribute, que são concatenados para formar o offset que indica o endereço a ser seguido caso a comparação
     * seja satisfeita.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t ifnull(Frame*);

    /**
     * \brief Instrução goto_w: Instrução goto com index de 32 bits.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t goto_w(Frame*);

    /**
     * \brief Instrução jsr_w: Instrução jsr com index de 32 bits.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t jsr_w(Frame*);

    /**
     * \brief Instrução nop: Nenhuma ação.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t nop(Frame*);

    /**
     * \brief Instrução tableswitch: Acessa tabela de saltos e salta.
     *
     *
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
     * \brief Guarda reference em um array de references.
     *
     * Recupera o valor referemce a ser empilhado, a referência para o array de inteiros e o index da
     * pilha de operandos. Checa se o array indicado pela referência existe e se a posição do array
     * indicada por index é válida e guarda o valor no array na posição index.
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
     * \brief Instrução areturn: De um método, retorna tipo reference.
     *
     * Recupera o valor do tipo reference value a ser retornado da pilha de operandos do método sendo executado. Desempilha um
     * frame da JVMStack, retornando assim ao ambiente do invocador do método. Value é empilhado na pilha de
     * operando do método sendo executado.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t areturn(Frame *);

    /**
     * \brief Instrução freturn: De um método, retorna float.
     *
     * Recupera o valor flobt value a ser retornado da pilha de operandos do método sendo executado. Desempilha um
     * frame da JVMStack, retornando assim ao ambiente do invocador do método. Value é empilhado na pilha de
     * operando do método sendo executado.
     *
     * \param frame Frame sendo executado na ExecutionEngine.
     * \return Inteiro uint32_t indicando qual o contador de programa da proxima instrucao.
     *
     * \date Date: 29/11/2019
     */
    static uint32_t freturn(Frame *);

    /**
     * \brief Insrução aload: Carrega um valor do tipo reference.

     *  Recupera um elemento do tipo reference do vetor de variáveis locais da posição indicada por index.
     *  Index é recuperado do atributo code de codeAttribute definido em AttributeInfo.cpp.
     *  O valor é empilhado na pilha de operandos.
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

    static uint32_t athrow(Frame*);
    static uint32_t instanceof(Frame*);
    static uint32_t checkcast(Frame*);
    static uint32_t invokedynamic(Frame*);
    static uint32_t invokeinterface(Frame*);
};


#endif
