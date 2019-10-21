#include "../include/Printer.hpp"
#include <inttypes.h>

Printer::Printer(ClassFile classFile) : cls_file{ classFile }  {
    this->printGeneralInfo();
    this->printConstantPool();
    this->printInterfaces();
    this->printFields();
    this->printMethods();
    this->printAttributes(false, std::vector<AttributeInfo>());
}

void Printer::printHeader(string sectionName) {
  cout << endl << "=================== " << sectionName;
  cout << " ===================" << endl << endl;
}

void Printer::printFooter(string sectionName) {
  cout << endl << "===================";
  for(int i = 0; i < sectionName.length()+2;i++) {
    cout << "=";
  }
  cout << "===================" << endl << endl;
}

string Printer::flagDescription(uint16_t flag) {
  switch (flag) {
    case ClassFile::ACC_PUBLIC:
        return "public";
    case ClassFile::ACC_FINAL:
        return "final";
    case ClassFile::ACC_SUPER:
        return "super";
    case ClassFile::ACC_INTERFACE:
        return "interface";
    case ClassFile::ACC_ABSTRACT:
        return "abstract";
    case ClassFile::ACC_SYNTHETIC:
        return "synthetic";
    case ClassFile::ACC_ANNOTATION:
        return "annotation";
    case ClassFile::ACC_ENUM:
        return "enum";
    default:
        return "";
  }
}

string Printer::majorVersionValue(uint16_t version) {
  switch (version) {
    case 46:
      return "1.2";
    case 47:
      return "1.3";
    case 48:
      return "1.4";
    case 49:
      return "5";
    case 50:
      return "6";
    case 51:
      return "7";
    case 52:
      return "8";
    case 53:
      return "9";
    case 54:
      return "10";
    case 55:
      return "11";
    case 56:
      return "12";
    case 57:
      return "13";
    case 58:
      return "14";
    default:
      return "";
    }
}

string Printer::printCPString(uint16_t cp_num) {
  return " mock string";
}

void Printer::printGeneralInfo() {
    this->printHeader("General Info");

    cout << "- Magic Number:           ";
    cout << hex << "0x" << this->cls_file.getMagicNumber() << endl;

    cout << "- Minor Version:          ";
    cout << dec << this->cls_file.getMinorVersion() << endl;

    uint16_t value = this->cls_file.getMajorVersion();
    cout << "- Major Version:          ";
    cout << dec << value;
    cout << " [" << this->majorVersionValue(value) << "]" << endl;

    cout << "- Constant Pool Count:    ";
    cout << dec << this->cls_file.getConstantPoolCount() << endl;

    uint16_t flag = this->cls_file.getAccessFlags();
    cout << "- Access Flags:           ";
    cout << "0x" << setfill('0') << setw(4) << hex << flag;
    cout << " [" << this->flagDescription(flag) << "]" << endl;

    cout << "- This Class:             ";
    uint16_t cp_index = this->cls_file.getThisClass();
    cout << "cp_info #" << cp_index << endl;

    cp_index = this->cls_file.getSuperClass();
    cout << "- Super Class:            ";
    cout << "cp_info #" << cp_index << endl;

    cout << "- Interfaces Count:       ";
    cout << dec << this->cls_file.getInterfacesCount() << endl;

    cout << "- Fields Count:           ";
    cout << dec << this->cls_file.getFieldsCount() << endl;

    cout << "- Methods Count:          ";
    cout << dec << this->cls_file.getMethodsCount() << endl;

    cout << "- Attributes Count:       ";
    cout << dec << this->cls_file.getAttributesCount() << endl;

    // this->printFooter("General Info");
}

void Printer::printCPBody(CPInfo cp) {
  uint8_t type = cp.tag;
  uint16_t cp_id;
  cout << "| " << endl;
  if (type == 1){
    // UTF8
      cout << "| Lenght of Bytes Array: " << cp.utf8Info.length << endl;
      cout << "| Lenght of The String: " << cp.utf8Info.length << endl;
      cout << "| String: " << cp.utf8Info.bytes << endl;
  } else if ((type == 3)||(type == 4)) {
    // Float or Integer
      if (type == 3) {
        cout << "| Bytes: " << "0x";
        cout << setfill('0') << setw(8) << hex << cp.integerInfo.bytes << endl;
        cout << "| Integer: " << dec << cp.integerInfo.bytes << endl;
      } else {
        cout << "| Bytes: " << "0x";
        cout << setfill('0') << setw(8) << hex << cp.floatInfo.bytes << endl;
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
      cout << "| Double: num" << endl;
    }
  } else if (type == 7){
    //Class
    cp_id = cp.classInfo.name_index;
    cout << "| Class Name: cp_info #" << dec << cp_id;
    cout << printCPString(cp_id) << endl;
  } else if (type == 8){
    //String
    cp_id = cp.stringInfo.string_index;
    cout << "| String: " << dec << cp_id;
    cout << printCPString(cp_id) << endl;
  } else if ((type == 9)||(type == 10)||(type == 11)) {
    if (type == 9) {
      //FieldRef
      cp_id = cp.fieldRefInfo.class_index;
      cout << "| Class Name: cp_info #" << dec << cp_id;
      cout << printCPString(cp_id) << endl;

      cp_id = cp.fieldRefInfo.name_and_type_index;
      cout << "| Name and Type: cp_info #" << dec << cp_id;
      cout << printCPString(cp_id) << endl;

    } else if (type == 10) {
      //MethodRef
      cp_id = cp.methodRefInfo.class_index;
      cout << "| Class Name: cp_info #" << dec << cp_id;
      cout << printCPString(cp_id) << endl;

      cp_id = cp.methodRefInfo.name_and_type_index;
      cout << "| Name and Type: cp_info #" << dec << cp_id;
      cout << printCPString(cp_id) << endl;

    } else {
      //Interface
      cp_id = cp.interfaceMethodRef.class_index;
      cout << "| Class Name: cp_info" << dec << cp_id;
      cout << printCPString(cp_id) << endl;

      cp_id = cp.interfaceMethodRef.name_and_type_index;
      cout << "| Name and Type: cp_info" << dec << cp_id;
      cout << printCPString(cp_id) << endl;

    }
  } else if (type == 12){
    //NameAndType
    cp_id = cp.nameAndTypeInfo.name_index;
    cout << "| Name: cp_info #" << dec << cp_id;
    cout << printCPString(cp_id) << endl;

    cp_id = cp.nameAndTypeInfo.descriptor_index;
    cout << "| Descriptor: cp_info #" << dec << cp_id;
    cout << printCPString(cp_id) << endl;

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
  // cout << "| " << endl;
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
      // this->printFooter(title);
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
    cout << "| Interface: " << dec << i_vec[i] << endl << endl;
    // cout << "| " << endl << endl;
  }

  if (i_vec.size() == 0) {
    cout << "| NENHUMA INTERFACE DISPONIVEL!" << endl;
  }

  // this->printFooter(title);
}

void Printer::printFields() {
  vector<FieldInfo> field_vec;
  uint16_t field_count = this->cls_file.getFieldsCount();
  string title = " Fields - [";
  title += to_string(field_count);
  title += "] Items";
  this->printHeader(title);

  for(int i=0;i < field_vec.size();i++) {
    cout << "[" << dec << i << "] Field " << endl;
    cout << "| " << endl;
    cout << "| Name: " << dec << field_vec[i].name_index << endl;
    cout << "| Descriptor: " << dec << field_vec[i].descriptor_index << endl;
    cout << "| Access Flags: " << dec << field_vec[i].access_flags << endl;
    cout << "| Attributes Count: " << dec << field_vec[i].attributes_count << endl << endl;
    // cout << "| " << endl << endl;
  }

  if (field_vec.size() == 0) {
    cout << "| NENHUM FIELD DISPONIVEL!" << endl;
  }

  // this->printFooter(title);
}

void Printer::printMethods() {
  vector<MethodInfo> method_vec;
  uint16_t method_count = this->cls_file.getMethodsCount();
  string title = " Methods - [";
  title += to_string(method_count);
  title += "] Items";
  this->printHeader(title);
  method_vec = cls_file.getMethods();

  for(int i=0;i < method_count;i++) {
    cout << "[" << dec << i << "] Method " << endl;
    cout << "| " << endl;
    cout << "| Name: " << dec << method_vec[i].name_index << endl;
    cout << "| Descriptor: " << dec << method_vec[i].descriptor_index << endl;
    cout << "| Access Flags: " << dec << method_vec[i].access_flags << endl;
    cout << "| Attributes Count: " << dec << method_vec[i].attributes_count << endl;
    cout << "| Attributes: " << endl;
    this->printAttributes(true, method_vec[i].attributes);
    cout << endl;
  }

  if (method_vec.size() == 0) {
    cout << "| NENHUM METHOD DISPONIVEL!" << endl;
  }
}

void Printer::printAttributes(bool inside_type, std::vector<AttributeInfo> vec) {
  vector<AttributeInfo> attr_vec;
  uint16_t attr_cont;
  string starter = "";

  if (inside_type == false) {
     string title = " Attributes - [";
     title += to_string(attr_cont);
     title += "] Items";
     this->printHeader(title);
     attr_vec = this->cls_file.getAttributes();
     attr_cont = this->cls_file.getAttributesCount();
  } else {
     attr_vec = vec;
     attr_cont = attr_vec.size();
     starter = "\t";
  }

  for(int i=0;i < attr_cont;i++) {
    cout << starter << "[" << i << "] Attribute ";
    cout << attr_vec[i].attributeName << endl;
    cout << starter << "| " << endl;
    cout << starter << "| Attribute Name Index: ";
    cout << dec << attr_vec[i].attributeNameIndex << endl;
    cout << starter << "| Attribute Length: ";
    cout << dec << attr_vec[i].attributeLength << endl << endl;
  }

  if (attr_cont == 0) {
    cout << "| NENHUM ATRIBUTO DISPONIVEL!" << endl;
  }
}
