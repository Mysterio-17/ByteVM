# ByteVM

A lightweight stack-based virtual machine with 18 instructions, written in C++17. ByteVM provides a simple environment for understanding how virtual machines work and how instructions are executed.

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)

## Features

- Stack-based architecture with 1000-element stack
- 18 essential opcodes covering arithmetic, logic, control flow, and I/O
- Function calls with local memory support
- Bytecode compiler for assembly-like syntax
- Fast opcode lookup using hash maps

## Project Structure

```
bytevm/              - Virtual machine implementation
bytevm-compiler/     - Bytecode compiler
test/                - Example programs
```

## Building

Compile both the VM and compiler using g++:

```bash
g++ -std=c++17 -o bytevm-compiler/bin/Debug/bytevm-compiler bytevm-compiler/*.cpp
g++ -std=c++17 -o bytevm/bin/Debug/bytevm bytevm/*.cpp
```

## Usage

### Step 1: Write Assembly Code

Create a file with ByteVM assembly instructions (e.g., `program.asm`):

```assembly
PUSH 10
PUSH 5
ADD
PRINT
HALT
```

### Step 2: Compile to Bytecode

```bash
./bytevm-compiler/bin/Debug/bytevm-compiler program.asm
```

This generates `test/out.bytevm` containing the compiled bytecode.

### Step 3: Run the Bytecode

```bash
./bytevm/bin/Debug/bytevm test/out.bytevm
```

## Instruction Set

| Opcode | Value | Description |
|--------|-------|-------------|
| PUSH   | 0     | Push value onto stack |
| POP    | 1     | Pop value from stack |
| ADD    | 2     | Pop two values, push sum |
| SUB    | 3     | Pop two values, push difference |
| MUL    | 4     | Pop two values, push product |
| AND    | 5     | Bitwise AND of top two values |
| OR     | 6     | Bitwise OR of top two values |
| NOT    | 7     | Logical NOT of top value |
| LT     | 8     | Push 1 if second < top, else 0 |
| EQ     | 9     | Push 1 if second == top, else 0 |
| JMP    | 10    | Jump to instruction address |
| JZ     | 11    | Jump if top of stack is 0 |
| LOAD   | 12    | Load from local memory |
| STORE  | 13    | Store to local memory |
| CALL   | 14    | Call function |
| RET    | 15    | Return from function |
| PRINT  | 16    | Pop and print top value |
| HALT   | 17    | Stop execution |

## Examples

### Example 1: Basic Arithmetic

```assembly
PUSH 15
PUSH 7
SUB
PRINT
HALT
```

Output: `8`

### Example 2: Conditional Logic

```assembly
PUSH 5
PUSH 10
LT
PRINT
HALT
```

Output: `1` (true, because 5 < 10)

### Example 3: Conditional Jump

```assembly
PUSH 0
JZ 8
PUSH 999
PRINT
HALT
PUSH 42
PRINT
HALT
```

Output: `42` (jumps to instruction 8 when stack top is 0)

### Example 4: Multiple Operations

```assembly
PUSH 100
PUSH 50
ADD
PRINT
PUSH 10
PUSH 3
MUL
PRINT
PUSH 25
PUSH 5
SUB
PRINT
HALT
```

Output:
```
150
30
20
```

## How It Works

The VM operates on a simple fetch-decode-execute cycle:

1. **Fetch**: Read the opcode at the current instruction pointer
2. **Decode**: Determine which operation to perform
3. **Execute**: Perform the operation on the stack
4. **Repeat**: Move to the next instruction

The compiler tokenizes assembly source code and converts instruction names to their numeric opcodes, producing a space-separated bytecode file that the VM can execute.

## Technical Details

- **Stack Size**: 1000 integers
- **Call Stack**: 100 frames
- **Local Memory**: 100 integers per frame
- **Opcode Lookup**: O(1) using unordered_map
- **Language**: C++17

