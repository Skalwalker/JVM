#include "../include/FieldInfo.hpp"

using namespace std;

FieldInfo::FieldInfo(vector<CPInfo> cp, FILE * fp) {
  ClassFileReader<uint16_t> twoBytes;
  ClassFileReader<uint32_t> fourBytes;

  this->access_flags = twoBytes.readBytes(fp);
  this->name_index =  twoBytes.readBytes(fp);
  this->descriptor_index =  twoBytes.readBytes(fp);
  this->attributes_count =  twoBytes.readBytes(fp);
  this->setAttributes(cp, fp);
  this->setAccessFlagsNames();
}

void FieldInfo::setAttributes(vector<CPInfo> cp, FILE * fp) {
    int attrCount = this->attributes_count;
    for (int attr = 0; attr < attrCount; attr++) {
        AttributeInfo attrInfo(cp, fp);
        attributes.push_back(attrInfo);
    }
}

void FieldInfo::setAccessFlagsNames() {
    string names;

    if (access_flags & ACC_PUBLIC) {
        names += "public ";
    }
    if (access_flags & ACC_PRIVATE) {
        names += "private ";
    }
    if (access_flags & ACC_PROTECTED) {
        names += "protected ";
    }
    if (access_flags & ACC_STATIC) {
        names += "static ";
    }
    if (access_flags & ACC_FINAL) {
        names += "final ";
    }
    if (access_flags & ACC_VOLATILE) {
        names += "volatile ";
    }
    if (access_flags & ACC_TRANSIENT) {
        names += "transient ";
    }
    if (access_flags & ACC_SYNTHETIC) {
        names += "synthetic ";
    }
    if (access_flags & ACC_ENUM) {
        names += "enum ";
    }
    access_flags_names = names;
}
