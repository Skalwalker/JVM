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
}

void FieldInfo::setAttributes(vector<CPInfo> cp, FILE * fp) {
    int attrCount = this->attributes_count;
    for (int attr = 0; attr < attrCount; attr++) {
        AttributeInfo attrInfo(cp, fp);
        attributes.push_back(attrInfo);
    }
}
