#include <stdio.h> // for stderr
#include <stdlib.h> // for exit()
#include "types.h"
#include "utils.h"

void print_rtype(char *, Instruction);
void print_itype_except_load(char *, Instruction, int);
void print_load(char *, Instruction);
void print_store(char *, Instruction);
void print_branch(char *, Instruction);
void write_rtype(Instruction);
void write_itype_except_load(Instruction); 
void write_load(Instruction);
void write_store(Instruction);
void write_branch(Instruction);
void write_lui(Instruction);
void write_jal(Instruction);
void write_ecall(Instruction);


void decode_instruction(Instruction instruction) {
    /* YOUR CODE HERE: COMPLETE THE SWITCH STATEMENTS */
    switch(instruction.opcode) { // What do we switch on?
        /* YOUR CODE HERE */
        case 0x33:
            write_rtype(instruction);
            break;

        case 0x03:
            write_load(instruction);
            break;

        case 0x13:
            write_itype_except_load(instruction);
            break;

        case 0x73:
            write_ecall(instruction);
            break;

        case 0x23:
            write_store(instruction);
            break;

        case 0x63:
            write_branch(instruction);
            break;

        case 0x37:
            write_lui(instruction);
            break;

        case 0x6f:
            write_jal(instruction);
            break;

    	default: // undefined opcode
            handle_invalid_instruction(instruction);
    	    break;
    }
}

void write_rtype(Instruction instruction) {
    char *name;
	switch(instruction.rtype.funct3) { // What do we switch on?
        /* YOUR CODE HERE */
        case 0x0:
            if (instruction.rtype.funct7 == 0x00) {
                name = "add";
            } else if (instruction.rtype.funct7 == 0x01) {
                name = "mul";
            } else {
                name = "sub";
            }
            break;

        case 0x1:
            if (instruction.rtype.funct7 == 0x00) {
                name = "sll";
            } else {
                name = "mulh";
            }
            break;

        case 0x2:
            name = "slt";
            break;

        case 0x4:
            if (instruction.rtype.funct7 == 0x00) {
                name = "xor";
            } else {
                name = "div";
            }
            break;

        case 0x5:
            if (instruction.rtype.funct7 == 0x00) {
                name = "srl";
            } else {
                name = "sra";
            }
            break;

        case 0x6:
            if (instruction.rtype.funct7 == 0x00) {
                name = "or";
            } else {
                name = "rem";
            }
            break;

        case 0x7:
            name = "and";
            break;

	    default:
            handle_invalid_instruction(instruction);
            break;
	}
    print_rtype(name, instruction);
}

void write_itype_except_load(Instruction instruction) {
    int shiftOp;
    shiftOp = -1;
    switch(instruction.itype.funct3) { // What do we switch on?
        /* YOUR CODE HERE */
        case 0x0:
            print_itype_except_load("addi", instruction, bitSigner(instruction.itype.imm, 12));
            break;

        case 0x1:
            print_itype_except_load("slli", instruction, bitSigner(instruction.itype.imm, 12));
            break;

        case 0x2:
            print_itype_except_load("slti", instruction, bitSigner(instruction.itype.imm, 12));
            break;

        case 0x4:
            print_itype_except_load("xori", instruction, bitSigner(instruction.itype.imm, 12));
            break;

        case 0x5:
            shiftOp = (instruction.itype.imm & 0x01f);
            if ((instruction.itype.imm & 0xfe0) == 0x00) {
                print_itype_except_load("srli", instruction, shiftOp);
            } else {
                print_itype_except_load("srai", instruction, shiftOp);
            }
            break;

        case 0x6:
            print_itype_except_load("ori", instruction, bitSigner(instruction.itype.imm, 12));
            break;

        case 0x7:
            print_itype_except_load("andi", instruction, bitSigner(instruction.itype.imm, 12));
            break;

        default:
            handle_invalid_instruction(instruction);
            break;
    }
}

void write_load(Instruction instruction) {
    switch(instruction.itype.funct3) { // What do we switch on?
        /* YOUR CODE HERE */
        case 0x0:
            print_load("lb", instruction);
            break;

        case 0x1:
            print_load("lh", instruction);
            break;

        case 0x2:
            print_load("lw", instruction);
            break;

        default:
            handle_invalid_instruction(instruction);
            break;
    }
}

void write_store(Instruction instruction) {
    switch(instruction.itype.funct3) { // What do we switch on?
        /* YOUR CODE HERE */
        case 0x0:
            print_store("sb", instruction);
            break;

        case 0x1:
            print_store("sh", instruction);
            break;

        case 0x2:
            print_store("sw", instruction);
            break;

        default:
            handle_invalid_instruction(instruction);
            break;
    }
}

void write_branch(Instruction instruction) {
    switch(instruction.itype.funct3) { // What do we switch on?
        /* YOUR CODE HERE */
        case 0x0:
            print_branch("beq", instruction);
            break;

        case 0x1:
            print_branch("bne", instruction);
            break;

        default:
            handle_invalid_instruction(instruction);
            break;
    }
}

/* For the writes, probably a good idea to take a look at utils.h */

void write_lui(Instruction instruction) {
    /* YOUR CODE HERE */
    printf(LUI_FORMAT, instruction.utype.rd, (sWord) instruction.utype.imm);
}

void write_jal(Instruction instruction) {
    /* YOUR CODE HERE */
    printf(JAL_FORMAT, instruction.ujtype.rd, get_jump_offset(instruction));
}

void write_ecall(Instruction instruction) {
    /* YOUR CODE HERE */
    printf(ECALL_FORMAT);
}

void print_rtype(char *name, Instruction instruction) {
    /* YOUR CODE HERE */
    printf(RTYPE_FORMAT, name, instruction.rtype.rd, instruction.rtype.rs1, instruction.rtype.rs2);
}

void print_itype_except_load(char *name, Instruction instruction, int imm) {
    /* YOUR CODE HERE */
    printf(ITYPE_FORMAT, name, instruction.itype.rd, instruction.itype.rs1, (sWord) imm);
}

void print_load(char *name, Instruction instruction) {
    /* YOUR CODE HERE */
    printf(MEM_FORMAT, name, instruction.itype.rd, (sWord) bitSigner(instruction.itype.imm, 12),
        instruction.itype.rs1);
}

void print_store(char *name, Instruction instruction) {
    /* YOUR CODE HERE */
    printf(MEM_FORMAT, name, instruction.stype.rs2, get_store_offset(instruction),
        instruction.stype.rs1);
}

void print_branch(char *name, Instruction instruction) {
    /* YOUR CODE HERE */
    printf(BRANCH_FORMAT, name, instruction.sbtype.rs1, instruction.sbtype.rs2,
        get_branch_offset(instruction));
}
