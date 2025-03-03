#include "bytevm.h"
#include "lexer.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

void ByteVM::run(int start_ip) {
    ip = start_ip;
    sp = -1;
    callsp = -1;
    
    while (ip < static_cast<int>(opcode.size())) {
        auto op = static_cast<Opcode>(opcode[ip++]);
        
        switch (op) {
            case Opcode::PUSH:
                stack[++sp] = opcode[ip++];
                break;
                
            case Opcode::POP:
                --sp;
                break;
                
            case Opcode::ADD: {
                int b = stack[sp--];
                int a = stack[sp--];
                stack[++sp] = a + b;
                break;
            }
            
            case Opcode::SUB: {
                int b = stack[sp--];
                int a = stack[sp--];
                stack[++sp] = a - b;
                break;
            }
            
            case Opcode::MUL: {
                int b = stack[sp--];
                int a = stack[sp--];
                stack[++sp] = a * b;
                break;
            }
            
            case Opcode::AND: {
                int b = stack[sp--];
                int a = stack[sp--];
                stack[++sp] = a & b;
                break;
            }
            
            case Opcode::OR: {
                int b = stack[sp--];
                int a = stack[sp--];
                stack[++sp] = a | b;
                break;
            }
            
            case Opcode::NOT: {
                int a = stack[sp--];
                stack[++sp] = !a;
                break;
            }
            
            case Opcode::LT: {
                int b = stack[sp--];
                int a = stack[sp--];
                stack[++sp] = (a < b) ? 1 : 0;
                break;
            }
            
            case Opcode::EQ: {
                int b = stack[sp--];
                int a = stack[sp--];
                stack[++sp] = (a == b) ? 1 : 0;
                break;
            }
            
            case Opcode::JMP:
                ip = opcode[ip];
                break;
                
            case Opcode::JZ: {
                int addr = opcode[ip++];
                if (stack[sp--] == 0) {
                    ip = addr;
                }
                break;
            }
            
            case Opcode::LOAD: {
                int offset = opcode[ip++];
                stack[++sp] = call_stack[callsp].local_memory[offset];
                break;
            }
            
            case Opcode::STORE: {
                int offset = opcode[ip++];
                call_stack[callsp].local_memory[offset] = stack[sp--];
                break;
            }
            
            case Opcode::CALL: {
                int addr = opcode[ip++];
                int nargs = opcode[ip++];
                int nlocals = opcode[ip++];
                ++callsp;
                init_stack_frame(call_stack[callsp], ip);
                for (int i = 0; i < nargs; i++) {
                    call_stack[callsp].local_memory[i] = stack[sp - nargs + i + 1];
                }
                sp -= nargs;
                ip = addr;
                break;
            }
            
            case Opcode::RET:
                ip = call_stack[callsp].return_ip;
                --callsp;
                break;
                
            case Opcode::PRINT:
                printf("%d\n", stack[sp--]);
                break;
                
            case Opcode::HALT:
                return;
                
            default:
                fprintf(stderr, "Invalid opcode: %d at ip=%d\n", 
                       static_cast<int>(op), ip - 1);
                exit(1);
        }
    }
}

void ByteVM::init_stack_frame(StackFrame& frame, int return_ip) {
    frame.return_ip = return_ip;
}

void ByteVM::parse(const string& filename) {
    Lexer lex;
    opcode = lex.get_prog(filename);
}

