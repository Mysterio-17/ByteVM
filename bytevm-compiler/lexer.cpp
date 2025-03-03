#include "lexer.h"
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <cctype>
#include <cstdlib>

using namespace std;

string Lexer::read_file(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Cannot open file " << filename << "\n";
        exit(1);
    }
    
    stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

int Lexer::get_opcode_num(const string& name) {
    static const unordered_map<string, int> opcodes = {
        {"PUSH",  0}, {"POP",   1}, {"ADD",   2}, {"SUB",   3},
        {"MUL",   4}, {"AND",   5}, {"OR",    6}, {"NOT",   7},
        {"LT",    8}, {"EQ",    9}, {"JMP",   10}, {"JZ",   11},
        {"LOAD",  12}, {"STORE", 13}, {"CALL", 14}, {"RET",  15},
        {"PRINT", 16}, {"HALT",  17}
    };
    
    auto it = opcodes.find(name);
    if (it != opcodes.end()) {
        return it->second;
    }
    
    cerr << "Error: Invalid opcode '" << name << "'\n";
    exit(1);
}

vector<string> Lexer::tokenize(const string& content) {
    vector<string> tokens;
    string token;
    
    for (char ch : content) {
        if (ch == ' ' || ch == '\n' || ch == '\t' || ch == '\r') {
            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
        } else {
            token += ch;
        }
    }
    
    if (!token.empty()) {
        tokens.push_back(token);
    }
    
    return tokens;
}

bool Lexer::is_number(const string& str) {
    if (str.empty()) return false;
    
    size_t start = 0;
    if (str[0] == '-' || str[0] == '+') {
        if (str.length() == 1) return false;
        start = 1;
    }
    
    for (size_t i = start; i < str.length(); ++i) {
        if (!isdigit(str[i])) return false;
    }
    
    return true;
}

vector<int> Lexer::convert_to_int(const vector<string>& tokens) {
    vector<int> result;
    result.reserve(tokens.size());
    
    for (const auto& token : tokens) {
        if (is_number(token)) {
            result.push_back(stoi(token));
        } else {
            result.push_back(get_opcode_num(token));
        }
    }
    
    return result;
}

vector<int> Lexer::get_prog(const string& filename) {
    string content = read_file(filename);
    vector<string> tokens = tokenize(content);
    return convert_to_int(tokens);
}
