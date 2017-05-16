/* represents the z80 microcontroller that the game boy utilizes */

#include "z80.h"
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

int run_z80( z80_t * z80 ){
	unsigned char opcode;
	uint16_t nn;
	char n;
	//todo - fetch opcode
	opcode = z80->memory[z80->pc];

	switch(opcode){

		//PUSH
		case 0xF5:{//PUSH AF
			push_z80( z80, z80->registers[REG_A] );
			push_z80( z80, z80->registers[REG_F] );
			z80->pc++;
			return 16;
		}
		case 0xC5:{//PUSH BC
			push_z80( z80, z80->registers[REG_B] );
			push_z80( z80, z80->registers[REG_C] );
			z80->pc++;
			return 16;
		}
		case 0xD5:{//PUSH DE
			push_z80( z80, z80->registers[REG_D] );
			push_z80( z80, z80->registers[REG_E] );
			z80->pc++;
			return 16;
		}
		case 0xE5:{//PUSH HL
			push_z80( z80, z80->registers[REG_H] );
			push_z80( z80, z80->registers[REG_L] );
			z80->pc++;
			return 16;
		}

		//POP
		case 0xF1:{//POP AF
			z80->registers[REG_F] = pop_z80( z80 );
			z80->registers[REG_A] = pop_z80( z80 );
			z80->pc++;
			return 12;
		}
		case 0xC1:{//POP BC
			z80->registers[REG_C] = pop_z80( z80 );
			z80->registers[REG_B] = pop_z80( z80 );
			z80->pc++;
			return 12;
		}
		case 0xD1:{//POP DE
			z80->registers[REG_E] = pop_z80( z80 );
			z80->registers[REG_D] = pop_z80( z80 );
			z80->pc++;
			return 12;
		}
		case 0xE1:{//POP HL
			z80->registers[REG_L] = pop_z80( z80 );
			z80->registers[REG_H] = pop_z80( z80 );
			z80->pc++;
			return 12;
		}

		//CALL
		case 0xCD:{//CALL nn
			nn = z80->memory[z80->pc+1] | (z80->memory[z80->pc+2] << 8);
			call_z80(z80, nn);
			return 12;
		}

		//JMP
		case 0xC3:{//JMP nn
			nn = z80->memory[z80->pc+1] | (z80->memory[z80->pc+2] << 8);
			jump_nn_z80(z80, nn);
			return 12;
			
		}
		case 0xC2:{//JMP NZ, nn
			nn = z80->memory[z80->pc+1] | (z80->memory[z80->pc+2] << 8);
			jump_cc_z80(z80, NZ, nn);
			return 12;
		}
		case 0xCA:{//JMP Z, nn
			nn = z80->memory[z80->pc+1] | (z80->memory[z80->pc+2] << 8);
			jump_cc_z80(z80, Z, nn);
			return 12;
		}
		case 0xD2:{//JMP NC, nn
			nn = z80->memory[z80->pc+1] | (z80->memory[z80->pc+2] << 8);
			jump_cc_z80(z80, NC, nn);
			return 12;
		}
		case 0xDA:{//JMP C, nn
			nn = z80->memory[z80->pc+1] | (z80->memory[z80->pc+2] << 8);
			jump_cc_z80(z80, C, nn);
			return 12;
		}
		case 0xE9:{//JMP HL
			nn = combine_regs(z80, REG_H, REG_L);
			jump_nn_z80(z80, nn);
			return 4;
		}
		case 0x18:{//JR n
			n = z80->memory[z80->pc + 1];	
			nn = z80->pc + n;
			jump_nn_z80(z80, nn);
			return 8;
		}

		//LOAD
		//LD nn, n
		case 0x06:{//LD B, n
			n = z80->memory[z80->pc + 1];
			load_i(z80, REG_B, n);
			return 8;
		}
		case 0x0E:{//LD C, n
			n = z80->memory[z80->pc + 1];
			load_i(z80, REG_C, n);
			return 8;
		}
		case 0x16:{//LD D, n
			n = z80->memory[z80->pc + 1];
			load_i(z80, REG_D, n);
			return 8;
		}
		case 0x1E:{//LD E, n
			n = z80->memory[z80->pc + 1];
			load_i(z80, REG_E, n);
			return 8;
		}
		case 0x26:{//LD H, n
			n = z80->memory[z80->pc + 1];
			load_i(z80, REG_H, n);
			return 8;
		}
		case 0x2E:{//LD L, n
			n = z80->memory[z80->pc + 1];
			load_i(z80, REG_L, n);
			return 8;
		}
		//LD r1, r2
		case 0x7F:{//LD A, A 
			load_regs(z80, REG_A, REG_A);
			return 4;
		}
		case 0x78:{//LD A, B 
			load_regs(z80, REG_A, REG_B);
			return 4;
		}
		case 0x79:{//LD A, C 
			load_regs(z80, REG_A, REG_C);
			return 4;
		}
		case 0x7A:{//LD A, D 
			load_regs(z80, REG_A, REG_D);
			return 4;
		}
		case 0x7B:{//LD A, E 
			load_regs(z80, REG_A, REG_E);
			return 4;
		}
		case 0x7C:{//LD A, H 
			load_regs(z80, REG_A, REG_H);
			return 4;
		}
		case 0x7D:{//LD A, L 
			load_regs(z80, REG_A, REG_L);
			return 4;
		}
		case 0x7E:{//LD A, HL
			load_i(z80, REG_A, combine_regs(z80, REG_H, REG_L));
			return 8;
		}
		

		//ADD
		case 0x80:{//ADD A, B
			add_regs(z80, REG_A, REG_B);
			return 4;
		}
		case 0x81:{//ADD A, C
			add_regs(z80, REG_A, REG_C);
			return 4;
		}
		case 0x82:{//ADD A, D
			add_regs(z80, REG_A, REG_D);
			return 4;
		}
		case 0x83:{//ADD A, E
			add_regs(z80, REG_A, REG_E);
			return 4;
		}
		case 0x84:{//ADD A, H
			add_regs(z80, REG_A, REG_H);
			return 4;
		}
		case 0x85:{//ADD A, L
			add_regs(z80, REG_A, REG_L);
			return 4;
		}
		case 0x86:{//ADD A, HL
			add_i(z80, REG_A, combine_regs(z80, REG_H, REG_L));
			return 8;
		}
		case 0x87:{//ADD A, A
			add_regs(z80, REG_A, REG_A);
			return 4;
		}

		//RETURN
		case 0xC9:{//RET
			nn = pop_z80(z80) | (pop_z80(z80) << 8);
			jump_nn_z80(z80, nn);
			return 8;
		}
		
		default:
			return 4;
	}
}

void load_game( z80_t * z80, char * name ){
}
void repaint_z80(z80_t * z80){}
void reset_draw_flag(z80_t * z80){}

