/**
 * \file ExceptionThrower.hpp
 * \brief Declaração da Classe ExecutionEngine e seus respectivos métodos e atributos.
 *
 * \author Khalil Carsten, Renato Nobre, Roberta Costa, Johannes Peter, Guilherme Andreúce
 * \date $Date: 29/11/2019
 */

#ifndef EXECUTION_ENGINE_H_INCLUDED
#define EXECUTION_ENGINE_H_INCLUDED

#include <string>
#include "../models/ClassFile.hpp"
#include "../runtime/MethodArea.hpp"
#include "../runtime/InstructionsManager.hpp"
#include "../runtime/Thread.hpp"
#include "../runtime/Frame.hpp"

/**
 * \class ExecutionEngine
 *
 * \brief Le, Interpreta e Executa as Instruções.
 *
 * \note Attempts at zen rarely work.
 * \todo
 * \throw
 * \bug
 * \attention
 * \param
 * \return
 * \retval
 *
 *
 * \date $Date: 29/11/2019
 */
class ExecutionEngine {
public:
    /**
     * Nome do .class que está a main
     */
    string mainClassFileName;

    /**
     * Gerenciador de Instruções para execução
     */
    InstructionsManager * instructionsManager;

    /**
     * Informações do método main segundo o .class
     */
    MethodInfo mainMethod;

    /**
     * Classe que onde fica guardado todos os métodos
     */
    MethodArea * methodArea;

    /**
     * \fn ExecutionEngine
     *
     * \brief Construtor da classe ExecutionEngine.
     *
     * Inicializa atributos da ExecutionEngine com os valores passados por parametros e chama o método findMainMethod().
     *
     * \param classFile Modelo do arquivo respectivo ao .class
     * \param methodArea Ponteiro para uma classe do tipo MethodArea que indica o arquivo .class carregado
     * \param instructionsManager* Ponteiro para uma classe do tipo InstructionsManager para gerenciar execução de instruções.
     *
     * \date $Date: 29/11/2019
     */
    ExecutionEngine(ClassFile*, MethodArea*, InstructionsManager*);

    /**
     * \fn findMainMethod
     *
     * \brief Encontra o método main do .class passado
     * como parametro na execução.
     * \return A função não retorna nenhum valor, mas pode terminar o programa caso não encontre o método.
     *
     * \date $Date: 29/11/2019
     */
    void findMainMethod();

    /**
     * \fn run
     *
     * \brief Realiza o processo de leitura, interpretação e execução das instruções.
     *
     * \date $Date: 29/11/2019
     */
    void run();
};

#endif
