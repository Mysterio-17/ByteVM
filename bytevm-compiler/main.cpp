#include "compiler.h"
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <source_file>\n";
        return 1;
    }
    
    ByteVMCompiler compiler;
    string input_file(argv[1]);
    return compiler.run(input_file);
}
