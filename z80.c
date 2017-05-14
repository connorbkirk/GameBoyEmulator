/* represents the z80 microcontroller that the game boy utilizes */

#include "z80.h"

void reset_z80( z80_t * z80 ){
	memset( z80->display, 0, 23040 );
	memset( z80->memory, 0, 65535 );
	memset( z80->registers, 0, 8 );
	z80->pc = 0x0;
	z80->sp = 0xFFFE;
}

int run_z80( z80_t * z80 ){
	return 4;
}

void load_game( z80_t * z80, char * name ){
}
void repaint_z80(z80_t * z80){}
void reset_draw_flag(z80_t * z80){}

