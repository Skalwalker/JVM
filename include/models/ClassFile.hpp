/**
 * \file ClassFile.hpp
 * \brief Declaração da Classe ExceptionThrower e seus respectivos métodos e atributos.
 *
 * \author Khalil Carsten, Renato Nobre, Roberta Costa, Johannes Peter, Guilherme Andreúce
 * \date $Date: 29/11/2019
 */
#ifndef __CLASSFILE_H__
#define __CLASSFILE_H__

#include <cstdint>
#include <vector>
#include <fstream>
#include "CPInfo.hpp"
#include "AttributeInfo.hpp"
#include "FieldInfo.hpp"
#include "MethodInfo.hpp"
#include "../loader/ClassFileReader.hpp"

/** \file ClassFile.hpp
 * Definição dos campos de um arquivo .class.
 * O formato de um arquivo .class:
 *
 * ClassFile { \n
 * <pre>
 *      u4 magic;   // Magic number para checar a integridade do arquivo.
 *      u2 minor_version;   // Junto à major_version determina o intervalo de versões suportadas.
 *      u2 major_version;
 *      u2 constant_pool_count;   // Número de entradas na ConstantPool + 1.
 *      cp_info constant_pool[constant_pool_count-1];   // Tabela de estruturas representando strings, constantes, classes e nomes de interfaces, nomes de campos, e outras constantes.
 *      u2 access_flags;   // Máscara de flags usada para denotar permissão de acesso e propriedades da classe ou interface.
 *      u2 this_class;   // Index de referência na ConstantPool da própria classe do arquivo .class.
 *      u2 super_class;   // Zero ou index de referência na ConstantPool da super classe direta da classe do arquivo .class.
 *      u2 interfaces_count;   // Número de superinterfaces diretas da classe ou interface do arquivo .class.
 *      u2 interfaces[interfaces_count];   // Array de index de referência na ConstantPool da super interface direta da classe ou interface do arquivo .class
 *      u2 fields_count;   // Número de estruturas de field_info na tabela de campos.
 *      field_info fields[fields_count];   // Todos os campos, variáveis de classe e variáveis de instância, declaradas pela classe ou interface do arquivo .class.
 *      u2 methods_count;   // Número de estruturas de methods_info na tabela de métodos.
 *      method_info methods[methods_count];  // Todos os métodos declarados pela classe ou interface do arquivo .class.
 *      u2 attributes_count;   // Número de atributos na tabela de atributos da classe ou interface do arquivo .class.
 *      attribute_info attributes[attributes_count]; // Tabela de estruturas do tipo attribute_info.
 * </pre>
 * }
 *
 */


using namespace std;

#define typeof __typeof__

class ClassFile {
    private:
    uint32_t magicNumber;
    uint16_t minorVersion;
    uint16_t majorVersion;
    uint16_t constantPoolCount;
    vector<CPInfo> constantPool;
    uint16_t accessFlags;
    uint16_t thisClass;
    uint16_t superClass;
    uint16_t interfacesCount;
    vector<uint16_t> interfaces;
    uint16_t fieldsCount;
    vector<FieldInfo> fields;
    uint16_t methodsCount;
    vector<MethodInfo> methods;
    uint16_t attributesCount;
    vector<AttributeInfo> attributes;

    void setMagicNumber(FILE * fp);
    void setMajorVersion(FILE * fp);
    void setMinorVersion(FILE * fp);
    void setConstantPoolCount(FILE * fp);
    void setConstantPool(FILE * fp);
    void setAccessFlags(FILE * fp);
    void setThisClass(FILE * fp);
    void setSuperClass(FILE * fp);
    void setInterfacesCount(FILE * fp);
    void setInterfaces(FILE * fp);
    void setFieldsCount(FILE * fp);
    void setFields(FILE * fp);
    void setMethodsCount(FILE * fp);
    void setMethods(FILE * fp);
    void setAttributesCount(FILE * fp);
    void setAttributes(FILE * fp);
    public:
    ClassFile(FILE * fp);
    ClassFile();
    static const uint32_t MAGIC_NUMBER = 0xCAFEBABE;
    static const uint16_t ACC_PUBLIC = 0x0001;
    static const uint16_t ACC_FINAL = 0x0010;
    static const uint16_t ACC_SUPER = 0x0020;
    static const uint16_t ACC_INTERFACE = 0x0200;
    static const uint16_t ACC_ABSTRACT = 0x0400;
    static const uint16_t ACC_SYNTHETIC = 0x1000;
    static const uint16_t ACC_ANNOTATION = 0x2000;
    static const uint16_t ACC_ENUM = 0x4000;

    uint32_t getMagicNumber();
    uint16_t getMajorVersion();
    uint16_t getMinorVersion();
    uint16_t getConstantPoolCount();
    vector<CPInfo> getConstantPool();
    uint16_t getAccessFlags();
    uint16_t getThisClass();
    uint16_t getSuperClass();
    uint16_t getInterfacesCount();
    vector<uint16_t> getInterfaces();
    uint16_t getFieldsCount();
    vector<FieldInfo> getFields();
    uint16_t getMethodsCount();
    vector<MethodInfo> getMethods();
    uint16_t getAttributesCount();
    vector<AttributeInfo> getAttributes();
};

#endif
