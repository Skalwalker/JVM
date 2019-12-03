#include <iostream>
#include "../../include/models/ClassFile.hpp"
using namespace std;

/** \file ClassFile.cpp
 * Gets e Sets de todos os campos da estrutura do ClassFile: magicNumber, minorVersion, majorVersion,
 * constantPoolCount, constantPool, accessFlags, thisClass, superClass, interfacesCount, interfaces,
 * fieldsCount, fields, methodsCount, methods, attributesCount, attributes.
 *
 */


ClassFile::ClassFile() {}

// Constructor
ClassFile::ClassFile(FILE * fp) {
    this->setMagicNumber(fp);
    this->setMinorVersion(fp);
    this->setMajorVersion(fp);
    this->setConstantPoolCount(fp);
    this->setConstantPool(fp);
    this->setAccessFlags(fp);
    this->setThisClass(fp);
    this->setSuperClass(fp);
    this->setInterfacesCount(fp);
    this->setInterfaces(fp);
    this->setFieldsCount(fp);
    this->setFields(fp);
    this->setMethodsCount(fp);
    this->setMethods(fp);
    this->setAttributesCount(fp);
    this->setAttributes(fp);
}

/**
Seta o valor do magicNumber a partir da leitura do arquivo .class com a função readBytes definida em
ClassFileReader.hpp.
O número de bytes lidos é definido pelo tamanho do tipo da informação sendo lida, o magicnumber é do
tipo uint32_t.

@param fp Arquivo .class sendo lido.
*/
void ClassFile::setMagicNumber(FILE * fp) {
    ClassFileReader<typeof(magicNumber)> magic;
    magicNumber = magic.readBytes(fp);
}

/**
Seta o valor do minorVersion a partir da leitura do arquivo .class com a função readBytes definida em
ClassFileReader.hpp.
O número de bytes lidos é definido pelo tamanho do tipo da informação sendo lida, o minorVersion é do
tipo uint16_t.

@param fp Arquivo .class sendo lido.
*/
void ClassFile::setMinorVersion(FILE * fp) {
    ClassFileReader<typeof(minorVersion)> minor;
    minorVersion = minor.readBytes(fp);
}

/**
Seta o valor do majorVersion a partir da leitura do arquivo .class com a função readBytes definida em
ClassFileReader.hpp.
O número de bytes lidos é definido pelo tamanho do tipo da informação sendo lida, o majorVersion é do
tipo uint16_t.

@param fp Arquivo .class sendo lido.
*/
void ClassFile::setMajorVersion(FILE * fp) {
    ClassFileReader<typeof(majorVersion)> major;
    majorVersion = major.readBytes(fp);
}

/**
Seta o valor do constantPoolCount a partir da leitura do arquivo .class com a função readBytes definida em
ClassFileReader.hpp.
O número de bytes lidos é definido pelo tamanho do tipo da informação sendo lida, o constantPoolCount é do
tipo uint16_t.

@param fp Arquivo .class sendo lido.
*/
void ClassFile::setConstantPoolCount(FILE * fp) {
    ClassFileReader<typeof(constantPoolCount)> cpCount;
    constantPoolCount = cpCount.readBytes(fp);
}

/**
Seta os valores das estuturas (cp_info) que compõem a constantPool a partir da leitura do arquivo .class com a função readBytes definida em
ClassFileReader.hpp. Estrutura cp_info: \n
cp_info {
<pre>
u1 tag;
u1 info[]; // Os tipos de info são definidas em CPInfo.hpp
</pre>
} \n
Para o número de estruturas na constantPool, constantPoolCount, o número de bytes lidos para cada valor da
constantPool é uint8_t.

//TODO: @Khalil, pq a condição para tag 5 e 6?

@param fp Arquivo .class sendo lido.
*/
void ClassFile::setConstantPool(FILE * fp) {
    int cpCount = constantPoolCount;
    for (int cp = 0; cp < cpCount-1; cp++) {
        uint8_t tag = ClassFileReader<uint8_t>().readBytes(fp);
        CPInfo cpInfo(tag, fp);
        constantPool.push_back(cpInfo);
        if (tag == 5 || tag == 6){
          CPInfo cpInfo(0, fp);
          constantPool.push_back(cpInfo);
          cp++;
        }
    }
}

/**
Seta o valor do accessFlags a partir da leitura do arquivo .class com a função readBytes definida em
ClassFileReader.hpp.
O número de bytes lidos é definido pelo tamanho do tipo da informação sendo lida, a accessFlags é do
tipo uint16_t.

@param fp Arquivo .class sendo lido.
*/
void ClassFile::setAccessFlags(FILE * fp) {
    ClassFileReader<typeof(accessFlags)> flags;
    accessFlags = flags.readBytes(fp);
}

/**
Seta o valor do thisClass a partir da leitura do arquivo .class com a função readBytes definida em
ClassFileReader.hpp.
O número de bytes lidos é definido pelo tamanho do tipo da informação sendo lida, a thisClass é do
tipo uint16_t.

@param fp Arquivo .class sendo lido.
*/
void ClassFile::setThisClass(FILE * fp) {
    ClassFileReader<typeof(thisClass)> thisC;
    thisClass = thisC.readBytes(fp);
}

/**
Seta o valor do superClass a partir da leitura do arquivo .class com a função readBytes definida em
ClassFileReader.hpp.
O número de bytes lidos é definido pelo tamanho do tipo da informação sendo lida, a superClass é do
tipo uint16_t.

@param fp Arquivo .class sendo lido.
*/
void ClassFile::setSuperClass(FILE * fp) {
    ClassFileReader<typeof(superClass)> superC;
    superClass = superC.readBytes(fp);
}

/**
Seta o valor do interfacesCount a partir da leitura do arquivo .class com a função readBytes definida em
ClassFileReader.hpp.
O número de bytes lidos é definido pelo tamanho do tipo da informação sendo lida, a interfacesCount é do
tipo uint16_t.

@param fp Arquivo .class sendo lido.
*/
void ClassFile::setInterfacesCount(FILE * fp) {
    ClassFileReader<typeof(interfacesCount)> itCount;
    interfacesCount = itCount.readBytes(fp);
}

/**
Seta os valores do vetor interfaces a partir da leitura do arquivo .class com a função readBytes definida em
ClassFileReader.hpp.
O número de bytes lidos é definido pelo tamanho do tipo da informação sendo lida, cada elemento do vetor é do
tipo uint16_t.

@param fp Arquivo .class sendo lido.
*/
void ClassFile::setInterfaces(FILE * fp) {
    int iCount = interfacesCount;
    for (int i = 0; i < iCount; i++) {
        uint16_t interface = ClassFileReader<uint16_t>().readBytes(fp);
        interfaces.push_back(interface);
    }
}

/**
Seta o valor do fieldsCount a partir da leitura do arquivo .class com a função readBytes definida em
ClassFileReader.hpp.
O número de bytes lidos é definido pelo tamanho do tipo da informação sendo lida, a fieldsCount é do
tipo uint16_t.

@param fp Arquivo .class sendo lido.
*/
void ClassFile::setFieldsCount(FILE * fp) {
    ClassFileReader<typeof(fieldsCount)> f_count;
    fieldsCount = f_count.readBytes(fp);
}

/**
Seta os valores das estuturas (field_info) que compõem o fields a partir da leitura do arquivo .class com a função readBytes definida em
ClassFileReader.hpp. \n
field_info {
<pre>
 u2 access_flags;
 u2 name_index;
 u2 descriptor_index;
 u2 attributes_count;
 attribute_info attributes[attributes_count];
</pre>
}

@param fp Arquivo .class sendo lido.
*/
void ClassFile::setFields(FILE * fp) {
  int fCount = fieldsCount;
  for (int i = 0; i < fCount; i++) {
      vector<CPInfo> cp = getConstantPool();
      FieldInfo fieldInfo(cp, fp);
      fields.push_back(fieldInfo);
  }
}

/**
Seta o valor do methodsCount a partir da leitura do arquivo .class com a função readBytes definida em
ClassFileReader.hpp.
O número de bytes lidos é definido pelo tamanho do tipo da informação sendo lida, a methodsCount é do
tipo uint16_t.

@param fp Arquivo .class sendo lido.
*/
void ClassFile::setMethodsCount(FILE * fp) {
    ClassFileReader<typeof(methodsCount)> m_count;
    methodsCount = m_count.readBytes(fp);
}

/**
Seta os valores das estuturas (methods_info) que compõem o methods a partir da leitura do arquivo .class com a função readBytes definida em
ClassFileReader.hpp. \n
method_info {
<pre>
 u2 access_flags;
 u2 name_index;
 u2 descriptor_index;
 u2 attributes_count;
 attribute_info attributes[attributes_count];
</pre>
}

@param fp Arquivo .class sendo lido.
*/
void ClassFile::setMethods(FILE * fp) {
  int mCount = methodsCount;
  for (int i = 0; i < mCount; i++) {
      vector<CPInfo> cp = getConstantPool();
      MethodInfo methodInfo(cp, fp);
      methods.push_back(methodInfo);
  }
}

/**
Seta o valor do attributesCount a partir da leitura do arquivo .class com a função readBytes definida em
ClassFileReader.hpp.
O número de bytes lidos é definido pelo tamanho do tipo da informação sendo lida, a attributesCount é do
tipo uint16_t.

@param fp Arquivo .class sendo lido.
*/
void ClassFile::setAttributesCount(FILE * fp) {
    ClassFileReader<typeof(attributesCount)> a_count;
    attributesCount = a_count.readBytes(fp);
}

/**
Seta os valores das estuturas (attribute_info) que compõem o methods a partir da leitura do arquivo .class com a função readBytes definida em
ClassFileReader.hpp. \n
attribute_info {
<pre>
 u2 attribute_name_index;
 u4 attribute_length;
 u1 info[attribute_length];
</pre>
}

@param fp Arquivo .class sendo lido.
*/
void ClassFile::setAttributes(FILE * fp) {
    int attrCount = attributesCount;
    for (int i = 0; i < attrCount; i++) {
        vector<CPInfo> cp = getConstantPool();
        AttributeInfo attrInfo(cp, fp);
        attributes.push_back(attrInfo);
    }
}

uint32_t ClassFile::getMagicNumber() {
    return magicNumber;
}

uint16_t ClassFile::getMinorVersion() {
    return minorVersion;
}

uint16_t ClassFile::getMajorVersion() {
    return majorVersion;
}

uint16_t ClassFile::getConstantPoolCount() {
    return constantPoolCount;
}

vector<CPInfo> ClassFile::getConstantPool() {
    return constantPool;
}

uint16_t ClassFile::getAccessFlags() {
    return accessFlags;
}

uint16_t ClassFile::getThisClass() {
    return thisClass;
}

uint16_t ClassFile::getSuperClass() {
    return superClass;
}

uint16_t ClassFile::getInterfacesCount() {
    return interfacesCount;
}

vector<uint16_t> ClassFile::getInterfaces() {
    return interfaces;
}

uint16_t ClassFile::getFieldsCount() {
    return fieldsCount;
}

vector<FieldInfo> ClassFile::getFields() {
    return fields;
}

vector<FieldInfo*> ClassFile::getFieldsPointer() {
    vector<FieldInfo*> pointers;
    for(int i = 0; i < fieldsCount; i++) {
        pointers.push_back(&(fields[i]));
    }
    return pointers;
}

uint16_t ClassFile::getMethodsCount() {
    return methodsCount;
}

vector<MethodInfo> ClassFile::getMethods() {
    return methods;
}

uint16_t ClassFile::getAttributesCount(){
    return attributesCount;
}

vector<AttributeInfo> ClassFile::getAttributes(){
    return attributes;
}
