#include "../../include/models/MethodInfo.hpp"

using namespace std;

MethodInfo::MethodInfo() {

}

MethodInfo::MethodInfo(vector<CPInfo> cp, FILE * fp) {
  ClassFileReader<uint16_t> twoBytes;
  ClassFileReader<uint32_t> fourBytes;

  this->access_flags = twoBytes.readBytes(fp);
  this->name_index = twoBytes.readBytes(fp);
  this->name = cp[this->name_index-1].getInfo(cp);
  this->descriptor_index =  twoBytes.readBytes(fp);
  this->attributes_count =  twoBytes.readBytes(fp);
  this->setAttributes(cp, fp);
  this->setAccessFlagsNames();

}

void MethodInfo::setAttributes(vector<CPInfo> cp, FILE * fp) {
    int attrCount = this->attributes_count;
    for (int attr = 0; attr < attrCount; attr++) {
        AttributeInfo attrInfo(cp, fp);
        attributes.push_back(attrInfo);
    }
}

void MethodInfo::setAccessFlagsNames() {
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
    if (access_flags & ACC_BRIDGE) {
        names += "bridge ";
    }
    if (access_flags & ACC_VARARGS) {
        names += "varargs ";
    }
    if (access_flags & ACC_NATIVE) {
        names += "native ";
    }
    if (access_flags & ACC_ABSTRACT) {
        names += "abstract ";
    }
    if (access_flags & ACC_STRICT) {
        names += "strict ";
    }
    if (access_flags & ACC_SYNTHETIC) {
        names += "synthetic ";
    }
    access_flags_names = names;
}
