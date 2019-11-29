/**
 * \file ExceptionThrower.hpp
 * \brief Declaração da Classe ExceptionThrower e seus respectivos métodos e atributos.
 *
 * \author Khalil Carsten, Renato Nobre, Roberta Costa, Johannes Peter, Guilherme Andreúce
 * \date $Date: 29/11/2019
 */

#ifndef EXCEPTION_THROWER_H_INCLUDED
#define EXCEPTION_THROWER_H_INCLUDED

#include <inttypes.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

/**
 * \class ExceptionThrower
 *
 * \brief Cuida do Tratamento de Exceções na Interpretação do Programa.
 *
 * Exceções podem ser geradas por instrucoes em caso de mal uso, ou por chamadas do programador, que nesse caso utilizam InstructionTables.
 *
 * \note Todas as Funções são estáticas, logo não é preciso fazer criação de objeto.
 *
 * \date $Date: 29/11/2019
 */
class ExceptionThrower {
public:
    /**
     * \brief Construtor vazio.
     *
     * \date $Date: 29/11/2019
     */
    ExceptionThrower();

    /**
     * \brief Gera uma exceção do tipo ArrayStoreException.
     *
     * \warning Chamar essa função implica no encerramento do programa.
     * \param index Index do vetor no qual o erro ocorre.
     * \throw ArrayStoreException Tipo do objeto não condiz com o objeto guardado pelo vetor.
     *
     * \date $Date: 29/11/2019
     */
    static void arrayStoreException(uint32_t index);

    /**
     * \brief Gera uma exceção do tipo ArrayIndexOutOfBoundsException.
     *
     * \warning Chamar essa função implica no encerramento do programa.
     * \param index Index do vetor no qual o erro ocorre.
     * \throw ArrayIndexOutOfBoundsException Acesso indevido ao indice do vetor.
     *
     * \date $Date: 29/11/2019
     */
    static void arrayIndexOutOfBounds(uint32_t index);

    /**
     * \brief Gera uma exceção do tipo NullPointerException.
     *
     * \warning Chamar essa função implica no encerramento do programa.
     * \throw NullPointerException Tentativa de acesso em vetor não incializado
     *
     * \date $Date: 29/11/2019
     */
    static void nullPointerException();

    /**
     * \brief Gera uma exceção do tipo ArithmeticException.
     *
     * \warning Chamar essa função implica no encerramento do programa.
     * \param type Tipo de excecao aritmetica que ocorre.
     * \throw ArithmeticException Tentativa de operação aritmética invalida.
     *
     * \date $Date: 29/11/2019
     */
    static void arithmeticException(uint32_t type);
};


#endif
