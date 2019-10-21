#include "../include/MethodInfo.hpp"

using namespace std;

MethodInfo::MethodInfo(vector<CPInfo> cp, FILE * fp) {
  ClassFileReader<uint16_t> twoBytes;
  ClassFileReader<uint32_t> fourBytes;

  this->access_flags = twoBytes.readBytes(fp);
  this->name_index =  twoBytes.readBytes(fp);
  this->descriptor_index =  twoBytes.readBytes(fp);
  this->attributes_count =  twoBytes.readBytes(fp);
  this->setAttributes(cp, fp);

  cout << "==============METHODS=================" << endl;
  cout << "Acess Flags: " << hex << access_flags << endl;
  cout << "Name Index: "  << dec << name_index << endl;
  cout << "descriptor_index: " << dec << descriptor_index << endl;
  cout << "atr_counts: " << dec << attributes_count << endl;

}

void MethodInfo::setAttributes(vector<CPInfo> cp, FILE * fp) {
    int attrCount = this->attributes_count;
    for (int attr = 0; attr < attrCount; attr++) {
        AttributeInfo attrInfo(cp, fp);
        attributes.push_back(attrInfo);
    }
}
