CC=gcc
SRC=src/*.c
FLAGS=-Wall
LINKER_FLAGS=-L./libs/SDL2 -lmingw32 -lSDL2main -lSDL2

clean:
	rm -f chip8-emulator
	rm -f src/*.o

all: 
	$(CC) -o chip8-emulator $(SRC) $(FLAGS) $(LINKER_FLAGS)

