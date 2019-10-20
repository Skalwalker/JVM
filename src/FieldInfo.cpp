#include "../include/FieldInfo.hpp"

using namespace std;

FieldInfo::FieldInfo(FILE * fp) {
  ClassFileReader<uint16_t> twoBytes;
  ClassFileReader<uint32_t> fourBytes;

  this->access_flags = twoBytes.readBytes(fp);
  this->name_index =  twoBytes.readBytes(fp);
  this->descriptor_index =  twoBytes.readBytes(fp);
  this->attributes_count =  twoBytes.readBytes(fp);

   cout << "Acess Flags: " << hex << access_flags << endl;
   cout << "Name Index: "  << dec << name_index << endl;
   cout << "descriptor_index: " << dec << descriptor_index << endl;
   cout << "atr_counts: " << dec << attributes_count << endl;
}
