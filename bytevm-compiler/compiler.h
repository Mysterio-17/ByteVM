#ifndef BYTEVM_COMPILER_H_
#define BYTEVM_COMPILER_H_

#include <string>
#include "lexer.h"

using namespace std;

class ByteVMCompiler {
public:
    int run(const string& input_file);
};

#endif
