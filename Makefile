CFLAGS := gcc -Wall -g

compile: main.c z80.c ops.c
	$(CFLAGS) main.c z80.c ops.c -o gb

clean:
	rm gb

