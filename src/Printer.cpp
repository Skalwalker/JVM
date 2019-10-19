#include "../include/Printer.hpp"

Printer::Printer() {

}

void Printer::manualHelloWorld(ClassFile classFile) {
    cout << hex << "0x" << classFile.getMagicNumber() << endl;
    cout << dec << classFile.getMinorVersion() << endl;
    cout << dec << classFile.getMajorVersion() << endl;
    cout << dec << classFile.getConstantPoolCount() << endl;
    cout << classFile.getConstantPool()[0].methodRefInfo.name_and_type_index << endl;
    cout << classFile.getConstantPool()[1].fieldRefInfo.name_and_type_index << endl;
    cout << classFile.getConstantPool()[2].stringInfo.string_index << endl;
    cout << classFile.getConstantPool()[3].methodRefInfo.name_and_type_index << endl;
    cout << classFile.getConstantPool()[4].classInfo.name_index << endl;
    cout << classFile.getConstantPool()[5].classInfo.name_index << endl;
    cout << classFile.getConstantPool()[6].utf8Info.length << endl;
    cout << classFile.getConstantPool()[6].utf8Info.bytes << endl;
    cout << classFile.getConstantPool()[7].utf8Info.length << endl;
    cout << classFile.getConstantPool()[7].utf8Info.bytes << endl;
    cout << classFile.getConstantPool()[8].utf8Info.length << endl;
    cout << classFile.getConstantPool()[8].utf8Info.bytes << endl;
    cout << classFile.getConstantPool()[9].utf8Info.length << endl;
    cout << classFile.getConstantPool()[9].utf8Info.bytes << endl;
    cout << classFile.getConstantPool()[10].utf8Info.length << endl;
    cout << classFile.getConstantPool()[10].utf8Info.bytes << endl;
    cout << classFile.getConstantPool()[11].utf8Info.length << endl;
    cout << classFile.getConstantPool()[11].utf8Info.bytes << endl;
    cout << classFile.getConstantPool()[12].utf8Info.length << endl;
    cout << classFile.getConstantPool()[12].utf8Info.bytes << endl;
    cout << classFile.getConstantPool()[13].utf8Info.length << endl;
    cout << classFile.getConstantPool()[13].utf8Info.bytes << endl;
    cout << classFile.getConstantPool()[14].nameAndTypeInfo.descriptor_index << endl;
    cout << classFile.getConstantPool()[15].classInfo.name_index << endl;
    cout << classFile.getConstantPool()[16].nameAndTypeInfo.descriptor_index << endl;
    cout << classFile.getConstantPool()[17].utf8Info.length << endl;
    cout << classFile.getConstantPool()[17].utf8Info.bytes << endl;
    cout << classFile.getConstantPool()[18].classInfo.name_index << endl;
    cout << classFile.getConstantPool()[19].nameAndTypeInfo.descriptor_index << endl;
    cout << classFile.getConstantPool()[20].utf8Info.length << endl;
    cout << classFile.getConstantPool()[20].utf8Info.bytes << endl;
    cout << classFile.getConstantPool()[21].utf8Info.length << endl;
    cout << classFile.getConstantPool()[21].utf8Info.bytes << endl;
    cout << classFile.getConstantPool()[22].utf8Info.length << endl;
    cout << classFile.getConstantPool()[22].utf8Info.bytes << endl;
    cout << classFile.getConstantPool()[23].utf8Info.length << endl;
    cout << classFile.getConstantPool()[23].utf8Info.bytes << endl;
    cout << classFile.getConstantPool()[24].utf8Info.length << endl;
    cout << classFile.getConstantPool()[24].utf8Info.bytes << endl;
    cout << classFile.getConstantPool()[25].utf8Info.length << endl;
    cout << classFile.getConstantPool()[25].utf8Info.bytes << endl;
    cout << classFile.getConstantPool()[26].utf8Info.length << endl;
    cout << classFile.getConstantPool()[26].utf8Info.bytes << endl;
    cout << classFile.getConstantPool()[27].utf8Info.length << endl;
    cout << classFile.getConstantPool()[27].utf8Info.bytes << endl;
    cout << hex << classFile.getAccessFlags() << endl;
    cout << classFile.getThisClass() << endl;
    cout << classFile.getSuperClass() << endl;
    cout << classFile.getInterfacesCount() << endl;
}