#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

//sign extends a bitfield with given size
/* You may find implementing this function helpful */
int bitSigner(unsigned int field, unsigned int size) {
    /* YOUR CODE HERE */
    int value = field;
    value = ((value << (32 - size)) >> (32 - size));
    return value;
}

/* Remember that the offsets should return the offset in BYTES */
int get_branch_offset(Instruction instruction) {
    /* YOUR CODE HERE */
    int offset = 0x00000000;
    offset = offset | (0x0000001e & instruction.sbtype.imm5);
    offset = offset | (0x000007e0 & (instruction.sbtype.imm7 << 5));
    offset = offset | (0x00000800 & (instruction.sbtype.imm5 << 11));
    offset = offset | (0x00001000 & (instruction.sbtype.imm7 << 6));
    return bitSigner(offset, 13);
}

int get_jump_offset(Instruction instruction) {
    /* YOUR CODE HERE */
    int offset = 0x00000000;
    offset = offset | (0x000ff000 & (instruction.ujtype.imm << 12));
    offset = offset | (0x00000800 & (instruction.ujtype.imm << 3));
    offset = offset | (0x000007fe & (instruction.ujtype.imm >> 8));
    offset = offset | (0x00100000 & (instruction.ujtype.imm << 2));
    return bitSigner(offset, 21);
}

int get_store_offset(Instruction instruction) {
    /* YOUR CODE HERE */
    int offset = 0x00000000;
    offset = offset | (0x00000001f & instruction.stype.imm5);
    offset = offset | (0x000000fe0 & (instruction.stype.imm7 << 5));
    return bitSigner(offset, 12);
}

void handle_invalid_instruction(Instruction instruction) {
    printf("Invalid Instruction: 0x%08x\n", instruction.bits); 
}

void handle_invalid_read(Address address) {
    printf("Bad Read. Address: 0x%08x\n", address);
    exit(-1);
}

void handle_invalid_write(Address address) {
    printf("Bad Write. Address: 0x%08x\n", address);
    exit(-1);
}
