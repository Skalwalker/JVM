#include "../../include/runtime/InstructionsManager.hpp"

InstructionsManager::InstructionsManager() {
    string line;
    ifstream myfile ("external_data/opcode_mnemonics.txt");

    string opcode_name, opcode_numb;
    uint32_t bytecount;
    uint8_t numb;
    while (myfile >> opcode_name >> opcode_numb >> bytecount) {
        numb = stoi(opcode_numb, nullptr, 16);
        opcode[numb] = Instruction(opcode_name, bytecount);
    }

    this->instructionByName("getstatic")->second.exec = Instruction::getstatic;
    this->instructionByName("ldc")->second.exec = Instruction::ldc;
    this->instructionByName("ldc2_w")->second.exec = Instruction::ldc2_w;
    this->instructionByName("invokevirtual")->second.exec = Instruction::invokevirtual;
    this->instructionByName("return")->second.exec = Instruction::returnfunc;
    this->instructionByName("ladd")->second.exec = Instruction::ladd;
    this->instructionByName("lsub")->second.exec = Instruction::lsub;
    this->instructionByName("lmul")->second.exec = Instruction::lmul;
    this->instructionByName("ldiv")->second.exec = Instruction::ldiv;
    this->instructionByName("lrem")->second.exec = Instruction::lrem;
    this->instructionByName("lneg")->second.exec = Instruction::lneg;
    this->instructionByName("lshl")->second.exec = Instruction::lshl;
    this->instructionByName("lshr")->second.exec = Instruction::lshr;
    this->instructionByName("land")->second.exec = Instruction::land;
    this->instructionByName("lor")->second.exec = Instruction::lor;
    this->instructionByName("lxor")->second.exec = Instruction::lxor;
    this->instructionByName("iadd")->second.exec = Instruction::iadd;
    this->instructionByName("isub")->second.exec = Instruction::isub;
    this->instructionByName("imul")->second.exec = Instruction::imul;
    this->instructionByName("idiv")->second.exec = Instruction::idiv;
    this->instructionByName("irem")->second.exec = Instruction::irem;
    this->instructionByName("ineg")->second.exec = Instruction::ineg;
    this->instructionByName("ishl")->second.exec = Instruction::ishl;
    this->instructionByName("ishr")->second.exec = Instruction::ishr;
    this->instructionByName("iushr")->second.exec = Instruction::iushr;
    this->instructionByName("iand")->second.exec = Instruction::iand;
    this->instructionByName("ior")->second.exec = Instruction::ior;
    this->instructionByName("ixor")->second.exec = Instruction::ixor;
    this->instructionByName("fadd")->second.exec = Instruction::fadd;
    this->instructionByName("fsub")->second.exec = Instruction::fsub;
    this->instructionByName("fmul")->second.exec = Instruction::fmul;
    this->instructionByName("fdiv")->second.exec = Instruction::fdiv;
    this->instructionByName("frem")->second.exec = Instruction::frem;
    this->instructionByName("fneg")->second.exec = Instruction::fneg;

    this->instructionByName("iinc")->second.exec = Instruction::iinc;

    this->instructionByName("dadd")->second.exec = Instruction::dadd;
    this->instructionByName("dsub")->second.exec = Instruction::dsub;
    this->instructionByName("dmul")->second.exec = Instruction::dmul;
    this->instructionByName("ddiv")->second.exec = Instruction::ddiv;
    this->instructionByName("drem")->second.exec = Instruction::drem;
    this->instructionByName("dneg")->second.exec = Instruction::dneg;


    this->instructionByName("bipush")->second.exec = Instruction::bipush;
    this->instructionByName("lstore")->second.exec = Instruction::lstore;
    this->instructionByName("lstore_0")->second.exec = Instruction::lstore_0;
    this->instructionByName("lstore_1")->second.exec = Instruction::lstore_1;
    this->instructionByName("lstore_2")->second.exec = Instruction::lstore_2;
    this->instructionByName("lstore_3")->second.exec = Instruction::lstore_3;
    this->instructionByName("istore")->second.exec = Instruction::istore;
    this->instructionByName("istore_0")->second.exec = Instruction::istore_0;
    this->instructionByName("istore_1")->second.exec = Instruction::istore_1;
    this->instructionByName("istore_2")->second.exec = Instruction::istore_2;
    this->instructionByName("istore_3")->second.exec = Instruction::istore_3;
    this->instructionByName("fstore")->second.exec = Instruction::fstore;
    this->instructionByName("fstore_0")->second.exec = Instruction::fstore_0;
    this->instructionByName("fstore_1")->second.exec = Instruction::fstore_1;
    this->instructionByName("fstore_2")->second.exec = Instruction::fstore_2;
    this->instructionByName("fstore_3")->second.exec = Instruction::fstore_3;
    this->instructionByName("dstore")->second.exec = Instruction::dstore;
    this->instructionByName("dstore_0")->second.exec = Instruction::dstore_0;
    this->instructionByName("dstore_1")->second.exec = Instruction::dstore_1;
    this->instructionByName("dstore_2")->second.exec = Instruction::dstore_2;
    this->instructionByName("dstore_3")->second.exec = Instruction::dstore_3;
    this->instructionByName("lload")->second.exec = Instruction::lload;
    this->instructionByName("lload_0")->second.exec = Instruction::lload_0;
    this->instructionByName("lload_1")->second.exec = Instruction::lload_1;
    this->instructionByName("lload_2")->second.exec = Instruction::lload_2;
    this->instructionByName("lload_3")->second.exec = Instruction::lload_3;
    this->instructionByName("iload")->second.exec = Instruction::iload;
    this->instructionByName("iload_0")->second.exec = Instruction::iload_0;
    this->instructionByName("iload_1")->second.exec = Instruction::iload_1;
    this->instructionByName("iload_2")->second.exec = Instruction::iload_2;
    this->instructionByName("iload_3")->second.exec = Instruction::iload_3;

    this->instructionByName("fload")->second.exec = Instruction::fload;
    this->instructionByName("fload_0")->second.exec = Instruction::fload_0;
    this->instructionByName("fload_1")->second.exec = Instruction::fload_1;
    this->instructionByName("fload_2")->second.exec = Instruction::fload_2;
    this->instructionByName("fload_3")->second.exec = Instruction::fload_3;
    this->instructionByName("dload")->second.exec = Instruction::dload;
    this->instructionByName("dload_0")->second.exec = Instruction::dload_0;
    this->instructionByName("dload_1")->second.exec = Instruction::dload_1;
    this->instructionByName("dload_2")->second.exec = Instruction::dload_2;
    this->instructionByName("dload_3")->second.exec = Instruction::dload_3;

    this->instructionByName("lcmp")->second.exec = Instruction::lcmp;
    this->instructionByName("ifeq")->second.exec = Instruction::ifeq;
    this->instructionByName("ifne")->second.exec = Instruction::ifne;
    this->instructionByName("iflt")->second.exec = Instruction::iflt;
    this->instructionByName("ifle")->second.exec = Instruction::ifle;
    this->instructionByName("ifgt")->second.exec = Instruction::ifgt;
    this->instructionByName("ifge")->second.exec = Instruction::ifge;
    this->instructionByName("fcmpl")->second.exec = Instruction::fcmpl;
    this->instructionByName("fcmpg")->second.exec = Instruction::fcmpg;
    this->instructionByName("dcmpl")->second.exec = Instruction::dcmpl;
    this->instructionByName("dcmpg")->second.exec = Instruction::dcmpg;

    this->instructionByName("iconst_m1")->second.exec = Instruction::iconst_m1;
    this->instructionByName("iconst_0")->second.exec = Instruction::iconst_0;
    this->instructionByName("iconst_1")->second.exec = Instruction::iconst_1;
    this->instructionByName("iconst_2")->second.exec = Instruction::iconst_2;
    this->instructionByName("iconst_3")->second.exec = Instruction::iconst_3;
    this->instructionByName("iconst_4")->second.exec = Instruction::iconst_4;
    this->instructionByName("iconst_5")->second.exec = Instruction::iconst_5;
    this->instructionByName("lconst_0")->second.exec = Instruction::lconst_0;
    this->instructionByName("lconst_1")->second.exec = Instruction::lconst_1;
    this->instructionByName("dconst_0")->second.exec = Instruction::dconst_0;
    this->instructionByName("dconst_1")->second.exec = Instruction::dconst_1;
    this->instructionByName("fconst_0")->second.exec = Instruction::fconst_0;
    this->instructionByName("fconst_1")->second.exec = Instruction::fconst_1;

    this->instructionByName("if_icmpeq")->second.exec = Instruction::if_icmpeq;
    this->instructionByName("if_icmpne")->second.exec = Instruction::if_icmpne;
    this->instructionByName("if_icmplt")->second.exec = Instruction::if_icmplt;
    this->instructionByName("if_icmpge")->second.exec = Instruction::if_icmpge;
    this->instructionByName("if_icmpgt")->second.exec = Instruction::if_icmpgt;
    this->instructionByName("if_icmple")->second.exec = Instruction::if_icmple;
    this->instructionByName("if_acmpeq")->second.exec = Instruction::if_acmpeq;
    this->instructionByName("if_acmpne")->second.exec = Instruction::if_acmpne;

    this->instructionByName("goto")->second.exec = Instruction::goto_func;

}

pair<uint8_t, Instruction>* InstructionsManager::instructionByName(string name) {
    map<uint8_t, Instruction>::iterator it;
    for(it = opcode.begin(); it != opcode.end(); it++) {
        if (it->second.mnemonic.compare(name) == 0) {
            return reinterpret_cast<pair<uint8_t, Instruction>*>(&(*it));
        }
    }
    return nullptr;
}
