#include <iostream>
#include <string>
#include "bytevm.h"

using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <bytecode_file>\n";
        return 1;
    }
    
    string filename(argv[1]);
    ByteVM vm;
    vm.parse(filename);
    vm.run(0);
    
    return 0;
}
