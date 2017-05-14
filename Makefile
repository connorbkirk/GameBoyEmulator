CFLAGS := gcc -Wall -g

compile: main.c z80.c
	$(CFLAGS) main.c z80.c -o gb

clean:
	rm gb

