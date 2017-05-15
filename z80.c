/* represents the z80 microcontroller that the game boy utilizes */

#include "z80.h"

void reset_z80( z80_t * z80 ){
	memset( z80->display, 0, 23040 );
	memset( z80->memory, 0, 65535 );
	memset( z80->registers, 0, 8 );
	z80->pc = 0x0;
	z80->sp = 0xFFFE;
}

void push_z80( z80_t * z80, uchar n){
	z80->memory[z80->sp] = n;
	z80->sp--;
}

uchar pop_z80( z80_t * z80 ){
	return z80->memory[z80->sp++];
}

int16_t combine_reg(z80_t * z80, int left, int right){
	return z80->registers[left] << 8 | z80->registers[right];
}

void jump_z80(z80_t * z80, int16_t nn){
	z80->pc = nn;
}

void call_z80(z80_t * z80, int16_t nn){
	int16_t addr;
	addr = z80->pc + 1;
	push_z80( z80, addr >> 8 );
	push_z80( z80, addr );
	jump_z80( z80, nn );
}

int run_z80( z80_t * z80 ){
	unsigned char opcode;
	int16_t nn;
	//todo - fetch opcode
	opcode = 0x0;

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
			nn = z80->memory[z80->pc+1] + (z80->memory[z80->pc+2] << 8);
			call_z80(z80, nn);
			return 12;
		}

		//RETURN
		case 0xC9:{//RET
			nn = pop_z80(z80) | (pop_z80(z80) << 8);
			jump_z80(z80, nn);
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

