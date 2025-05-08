#include <stdio.h>
#include <stdbool.h>

// Memory size
#define MEM_SIZE 256

// Opcodes
#define HALT 0
#define LOAD 1
#define STORE 2
#define ADD 3
#define SUB 4
#define JMP 5
#define JZ 6

// Memory and registers
int memory[MEM_SIZE] = {0};
int PC = 0; // Program Counter
int ACC = 0; // Accumulator

// Example program: memory[0] = LOAD 10, memory[1] = ADD 11, memory[2] = STORE 12, memory[3] = HALT
// memory[10] = 5, memory[11] = 7
void load_program() {
    printf("Starting program...\n");
    memory[0] = LOAD; memory[1] = 10;
    memory[2] = ADD;  memory[3] = 11;
    memory[4] = STORE; memory[5] = 12;
    memory[6] = HALT;
    memory[10] = 5;
    memory[11] = 7;
}

// Function to let the user input their own program
void input_program() {
    printf("Enter your program instructions (opcode operand). Enter -1 to finish.\n");
    int addr = 0;
    while (addr < MEM_SIZE) {
        int opcode, operand = 0;
        printf("[%d] Opcode: ", addr);
        if (scanf("%d", &opcode) != 1) break;
        if (opcode == -1) break;
        memory[addr++] = opcode;
        // Opcodes that require an operand
        if (opcode == LOAD || opcode == STORE || opcode == ADD || opcode == SUB || opcode == JMP || opcode == JZ) {
            printf("[%d] Operand: ", addr);
            if (scanf("%d", &operand) != 1) break;
            memory[addr++] = operand;
        }
    }
    // Optionally, fill the rest of memory with HALT
    if (addr < MEM_SIZE) memory[addr] = HALT;
}

// Main function
int main() {
    // Print the welcome message    
    printf("Von Neumann Computer\n");
    printf("1. Run example program\n");
    printf("2. Enter your own program\n");
    printf("Choose an option: ");
    scanf("%d", &choice);
    if (choice == 1) {
        load_program();
    } else {
        input_program();
    }
    bool running = true;
    PC = 0;
    ACC = 0;
    while (running) {
        int opcode = memory[PC++];
        switch (opcode) {
            case HALT:+
                // Halt execution of the program
                running = false;
                break;
            case LOAD: {
                // Load value from memory address into accumulator
                int addr = memory[PC++];
                ACC = memory[addr];
                break;
            }
            case STORE: {
                // Store value from accumulator into memory address
                int addr = memory[PC++];
                memory[addr] = ACC;
                break;
            }
            case ADD: {
                // Add value from memory address to accumulator
                int addr = memory[PC++];
                ACC += memory[addr];
                break;
            }
            case SUB: {
                // Subtract value from memory address from accumulator
                int addr = memory[PC++];
                ACC -= memory[addr];
                break;
            }
            case JMP: {
                // Jump to memory address
                int addr = memory[PC++];
                PC = addr;
                break;
            }
            case JZ: {
                // Jump to memory address if accumulator is zero
                int addr = memory[PC++];
                if (ACC == 0) PC = addr;
                break;
            }
            default:
                printf("Unknown opcode: %d\n", opcode);
                running = false;
                break;
        }
    }
    printf("Result stored at memory[12]: %d\n", memory[12]);
    return 0;
}
