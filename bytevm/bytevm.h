#ifndef BYTEVM_H_
#define BYTEVM_H_

#include <vector>
#include <string>
#include <array>
#include <cstdint>

using namespace std;

constexpr size_t DEFAULT_STACK_SIZE = 1000;
constexpr size_t DEFAULT_STACK_FRAME_SIZE = 100;
constexpr size_t DEFAULT_LOCAL_MEMORY = 100;

enum class Opcode : uint8_t {
    PUSH = 0, POP = 1, ADD = 2, SUB = 3, MUL = 4, AND = 5,
    OR = 6, NOT = 7, LT = 8, EQ = 9, JMP = 10, JZ = 11,
    LOAD = 12, STORE = 13, CALL = 14, RET = 15, PRINT = 16, HALT = 17
};

struct StackFrame {
    int return_ip;
    array<int, DEFAULT_LOCAL_MEMORY> local_memory;
    
    StackFrame() : return_ip(0), local_memory{} {}
};

class ByteVM {
public:
    ByteVM() : ip(0), sp(-1), callsp(-1) {}
    
    void run(int start_ip);
    void parse(const string& filename);

private:
    int ip;
    int sp;
    int callsp;
    vector<int> opcode;
    array<int, DEFAULT_STACK_SIZE> stack;
    array<StackFrame, DEFAULT_STACK_FRAME_SIZE> call_stack;
    
    void init_stack_frame(StackFrame& frame, int return_ip);
};

#endif
