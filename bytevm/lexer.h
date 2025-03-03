#ifndef LEXER_H_
#define LEXER_H_

#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Lexer {
public:
    vector<int> get_prog(const string& filename);

private:
    string read_file(const string& filename);
    int get_opcode_num(const string& name);
    vector<string> tokenize(const string& content);
    vector<int> convert_to_int(const vector<string>& tokens);
    bool is_number(const string& str);
};

#endif
