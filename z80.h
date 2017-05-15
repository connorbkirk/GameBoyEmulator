#include "string.h"
#include "stdbool.h"
#include "stdint.h"

#define REG_A 0
#define REG_B 1
#define REG_C 2
#define REG_D 3
#define REG_E 4
#define REG_H 5
#define REG_L 6
#define REG_F 7
#define FLAG_ZERO 7
#define FLAG_SUB 5
#define FLAG_HALF_CARRY 5
#define FLAG_CARRY 4

typedef struct{
        uchar registers[8];
        uchar display[23040];
        uchar memory[65535];
        int16_t sp;
        int16_t pc;
        bool need_redraw;
} z80_t;

void reset_z80( z80_t * z80 );
int run_z80( z80_t * z80 );
void load_game( z80_t * z80, char * name );
void repaint_z80(z80_t * z80);
void reset_draw_flag(z80_t * z80);

