/* represents the z80 microcontroller that the game boy utilizes */

#include "ops.h"
#include <stdlib.h>
#include <stdio.h>

void reset_z80( z80_t * z80 ){
	memset( z80->display, 0, 23040 );
	memset( z80->memory, 0, 65535 );
	memset( z80->registers, 0, 8 );
	z80->pc = 0x0;
	z80->sp = 0xFFFE;
}

void push_z80( z80_t * z80, char n){
	z80->memory[z80->sp] = n;
	z80->sp--;
}

unsigned char pop_z80( z80_t * z80 ){
	z80->sp++;
	return z80->memory[z80->sp];
}

int16_t combine_regs(z80_t * z80, int left, int right){
	return z80->registers[left] << 8 | z80->registers[right];
}

bool check_cc(z80_t * z80, cc cond){
	switch(cond){
		case NZ:
			return ((unsigned char)z80->registers[REG_F] >> FLAG_ZERO) == 0;
		case Z:
			return ((unsigned char)z80->registers[REG_F] >> FLAG_ZERO) == 1;
		case NC:
			return ((unsigned char)z80->registers[REG_F] >> FLAG_CARRY) == 0;
		case C:
			return ((unsigned char)z80->registers[REG_F] >> FLAG_CARRY) == 1;
		default:
			printf("Condition is not valid\n");
			exit(1);
	}

}

void jump_nn_z80(z80_t * z80, uint16_t nn){
	z80->pc = nn;
}

void jump_cc_z80(z80_t * z80, cc cond, uint16_t nn){
	if( check_cc(z80, cond) ){
		jump_nn_z80(z80, nn);
	}
}

void load_regs(z80_t * z80, int reg1, int reg2){
	z80->registers[reg1] = z80->registers[reg2];
}

void load_i(z80_t * z80, int reg, uint16_t immediate){
	z80->registers[reg] = immediate;
}

void add_regs(z80_t * z80, int reg1, int reg2){
	z80->registers[reg1] += z80->registers[reg2];
	z80->registers[REG_F] &= ~(1 << FLAG_SUB);
	if(z80->registers[reg1] == 0){
		z80->registers[REG_F] |= (1 << FLAG_ZERO);
	}
	if(z80->registers[reg1] > 15){
		z80->registers[REG_F] |= (1 < FLAG_HALF_CARRY);
	}
	if(z80->registers[reg1] > 255){
		z80->registers[REG_F] |= (1 << FLAG_CARRY);
	}
}

void add_i(z80_t * z80, int reg1, uint16_t immediate){
	z80->registers[reg1] += immediate;
	z80->registers[REG_F] &= ~(1 << FLAG_SUB);
	if(z80->registers[reg1] == 0){
		z80->registers[REG_F] |= (1 << FLAG_ZERO);
	}
	if(z80->registers[reg1] > 15){
		z80->registers[REG_F] |= (1 < FLAG_HALF_CARRY);
	}
	if(z80->registers[reg1] > 255){
		z80->registers[REG_F] |= (1 << FLAG_CARRY);
	}
}

void call_z80(z80_t * z80, uint16_t nn){
	int16_t addr;
	addr = z80->pc + 1;
	push_z80( z80, addr >> 8 );
	push_z80( z80, addr );
	jump_nn_z80( z80, nn );
}

unsigned char read_8bit_z80( z80_t * z80, uint16_t addr ){
	return z80->memory[addr];
}

uint16_t read_16bit_z80( z80_t * z80, uint16_t addr ){
	return z80->memory[addr] | (z80->memory[addr+1] << 8);
}

int run_z80( z80_t * z80 ){
	unsigned char instr;
	uint16_t operand;

	instr = z80->memory[z80->pc++];
	operand = 0;

	if(instructions[instr].operand_length == 0){
		((void(*)(void))instructions[instr].exec)();
	}
	else if(instructions[instr].operand_length == 1){
		operand = (uint16_t)read_8bit_z80(z80, z80->pc);
		((void(*)(unsigned char))instructions[instr].exec)((unsigned char)operand);
	}
	else if(instructions[instr].operand_length == 2){
		operand = read_16bit_z80(z80, z80->pc);
		((void(*)(uint16_t))instructions[instr].exec)(operand);
	}
	z80->pc += instructions[instr].operand_length;

	return instruction_ticks[instr];
}

void load_game( z80_t * z80, char * file ){
	FILE *fp;
	size_t read;

	//open file in read-only mode
	fp = fopen(file, "r");

	if(!fp){
		fprintf(stderr, "File %s could not be opened\n", file);
		exit(1);
	}
	
	read = fread(z80->memory, 1, 0x7FFF, fp);
	if(!read){
		fprintf(stderr, "File %s could not be read\n", file);
		exit(1);
	}

	fclose(fp);
}

void repaint_z80(z80_t * z80){}
void reset_draw_flag(z80_t * z80){}

