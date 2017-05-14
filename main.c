#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include "z80.h"

#define BILLION 1000000000L

z80_t * z80;

int timespec_subtract(struct timespec * result, struct timespec * t2,
	struct timespec * t1){
	/* subtracts t1 from t2 and stores the value in result */
	long int diff = (t2->tv_nsec + BILLION * t2->tv_sec) - 
		(t1->tv_nsec + BILLION * t1->tv_sec);
	result->tv_sec = diff % BILLION;
	result->tv_nsec = diff / BILLION; 
	
	return (diff < 0);
}

void run(){
	struct timespec ts_begin, ts_end, ts_diff;
	int cycles_used;
	double sleep_time;

	while(1){
		clock_gettime(CLOCK_REALTIME, &ts_begin);
		cycles_used = run_z80( z80 );	
		clock_gettime(CLOCK_REALTIME, &ts_end);
		timespec_subtract(&ts_diff, &ts_end, &ts_begin);

		if(z80->need_redraw){
			repaint_z80(z80);
			reset_draw_flag(z80);
		}

		sleep_time = cycles_used * 23.84 - ts_diff.tv_nsec;
		if( sleep_time > 0 ){	
			sleep(sleep_time);
		}
	}
}

int main(int argv, char ** argc){
	z80 = (z80_t *)malloc(sizeof(z80_t));
	reset_z80(z80);
	load_game(z80, "./tetris.gb");
	run();
}
