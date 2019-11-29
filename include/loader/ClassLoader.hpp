/**
 * \file ClassLoader.hpp
 * \brief Declaração da Classe ClassLoader e seus respectivos métodos e atributos.
 *
 * \author Khalil Carsten, Renato Nobre, Roberta Costa, Johannes Peter, Guilherme Andreúce
 * \date $Date: 29/11/2019
 */
#ifndef __CLASSLOADER_H_INCLUDED__
#define __CLASSLOADER_H_INCLUDED__

#include "../models/ClassFile.hpp"
#include "../runtime/MethodArea.hpp"

class ClassLoader {
public:
    MethodArea * methodArea;
    ClassLoader();
    ClassLoader(int);
    ClassFile loadClassFile(ClassFile);
};

#endif
