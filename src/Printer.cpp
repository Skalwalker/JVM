#include "../include/Printer.hpp"
#include <inttypes.h>

Printer::Printer(ClassFile classFile) : cls_file{ classFile }  {
    this->printGeneralInfo();
    this->printConstantPool();
    this->printInterfaces();
}

void Printer::printHeader(string sectionName) {
  cout << endl << "=================== " << sectionName;
  cout << " ===================" << endl << endl;
}

void Printer::printFooter(string sectionName) {
  cout << endl << "===================" << sectionName;
  cout << "===================" << endl << endl;
}

void Printer::printGeneralInfo() {
    this->printHeader("General Info");

    cout << "- Magic Number:           ";
    cout << hex << "0x" << this->cls_file.getMagicNumber() << endl;

    cout << "- Minor Version:          ";
    cout << dec << this->cls_file.getMinorVersion() << endl;

    cout << "- Major Version:          ";
    cout << dec << this->cls_file.getMajorVersion() << endl;

    cout << "- Constant Pool Count:    ";
    cout << dec << this->cls_file.getConstantPoolCount() << endl;

    cout << "- Access Flags:           ";
    cout << hex << this->cls_file.getAccessFlags() << endl;
    cout << "- This Class:             ";
    cout << this->cls_file.getThisClass() << endl;

    cout << "- Super Class:            ";
    cout << this->cls_file.getSuperClass() << endl;

    cout << "- Interfaces Count:       ";
    cout << this->cls_file.getInterfacesCount() << endl;

    cout << "- Fields Count:           ";
    cout << "- Methods Count:          ";
    cout << "- Attributes Count:       ";

    this->printFooter("");
}

void Printer::printCPBody(CPInfo cp) {
  uint8_t type = cp.tag;
  cout << "| " << endl;
  if (type == 1){
    // UTF8
      cout << "| Lenght of Bytes Array: " << cp.utf8Info.length << endl;
      cout << "| Lenght of The String: " << cp.utf8Info.length << endl;
      cout << "| String: " << cp.utf8Info.bytes << endl;
  } else if ((type == 3)||(type == 4)) {
    // Float or Integer
      if (type == 3) {
        cout << "| Bytes: " << cp.integerInfo.bytes << endl;
        cout << "| Integer: " << dec << cp.integerInfo.bytes << endl;
      } else {
        cout << "| Bytes: " << cp.floatInfo.bytes << endl;
        cout << "| Float: " << dec << cp.floatInfo.bytes << endl;
      }
  } else if ((type == 5)||(type == 6)) {
    // Long or double
    if (type == 5) {
      cout << "| High Bytes: " << cp.longInfo.high_bytes << endl;
      cout << "| Low Bytes: " << cp.longInfo.low_bytes << endl;
      cout << "| Long: num" << endl;
    } else {
      cout << "| High Bytes: " << cp.doubleInfo.high_bytes << endl;
      cout << "| Low Bytes: " << cp.doubleInfo.low_bytes << endl;
      cout << "| Double: " << endl;
    }
  } else if (type == 7){
    //Class
    cout << "| Class Name: " << cp.classInfo.name_index << endl;
  } else if (type == 8){
    //String
    cout << "| String: " << cp.stringInfo.string_index << endl;
  } else if ((type == 9)||(type == 10)||(type == 11)) {
    // FieldRef, MethodRef, Interface
    if (type == 9) {
      cout << "| Class Name: " << cp.fieldRefInfo.class_index<< endl;
      cout << "| Name and Type: " << cp.fieldRefInfo.name_and_type_index<< endl;
    } else if (type == 10) {
      cout << "| Class Name: " << cp.methodRefInfo.class_index<< endl;
      cout << "| Name and Type: " << cp.methodRefInfo.name_and_type_index<< endl;
    } else {
      cout << "| Class Name: " << cp.interfaceMethodRef.class_index<< endl;
      cout << "| Name and Type: " << cp.interfaceMethodRef.name_and_type_index<< endl;
    }
  } else if (type == 12){
    //NameAndType
    cout << "| Name: " << cp.nameAndTypeInfo.name_index << endl;
    cout << "| Descriptor: " << cp.nameAndTypeInfo.descriptor_index << endl;
  } else if (type == 15){
    //Method Handle
    cout << "| Reference Kind: " << cp.methodHandleInfo.reference_kind << endl;
    cout << "| Reference Index: " << cp.methodHandleInfo.reference_index << endl;
  } else if (type == 16){
    //Method Type
    cout << "| Descriptor Index: " << cp.methodTypeInfo.descriptor_index << endl;
  } else if (type == 18){
    //Invoke Dynamic
    cout << "| Bootstrap Method Atr: " << cp.invokeDynamicInfo.bootstrap_method_attr_index << endl;
    cout << "| Name and Type: " << cp.invokeDynamicInfo.name_and_type_index << endl;
  }
  cout << "| " << endl;
  cout << endl;
}

void Printer::printConstantPool(){
      vector<CPInfo> cp_vec;
      string title = " Constant Pool - [";
      title += to_string(this->cls_file.getConstantPoolCount());
      title += "] Items";
      this->printHeader(title);
      cp_vec = this->cls_file.getConstantPool();
      for(int i = 0; i < cp_vec.size(); i++){
        cout << "[" << dec << i+1 << "] Constant " << cp_vec[i].name << endl;
        this->printCPBody(cp_vec[i]);
      }
      this->printFooter("");
}

void Printer::printInterfaces(){
  string title = " Interfaces - [";
  title += to_string(this->cls_file.getInterfacesCount());
  title += "] Items";
  this->printHeader(title);

  vector<uint16_t> i_vec = this->cls_file.getInterfaces();
  for(int i=0;i < i_vec.size();i++) {
    cout << "[" << dec << i << "] Interface " << i_vec[i] << endl;
    cout << "| " << endl;
    cout << "| Interface: " << dec << i_vec[i] << endl;
    cout << "| " << endl << endl;
  }

  if (i_vec.size() == 0) {
    cout << "NENHUMA INTERFACE DISPONIVEL!" << endl;
  }

  this->printFooter("");
}
