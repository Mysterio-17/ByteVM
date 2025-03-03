#include "compiler.h"
#include <fstream>
#include <iostream>

using namespace std;

int ByteVMCompiler::run(const string& input_file) {
    ofstream outfile("test/out.bytevm");
    if (!outfile.is_open()) {
        cerr << "Error: Cannot create output file\n";
        return 1;
    }
    
    Lexer lex;
    vector<int> program = lex.get_prog(input_file);
    
    for (size_t i = 0; i < program.size(); ++i) {
        outfile << program[i];
        if (i < program.size() - 1) {
            outfile << " ";
        }
    }
    
    outfile.close();
    return 0;
}
