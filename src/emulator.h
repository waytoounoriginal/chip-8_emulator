#ifndef __EMULATOR__
#define __EMULATOR__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "types.h"
#include "stack.h"
#include "err.h"

#define MEM_SIZE 4096
#define MEM_START 0x200

#define PROGRAM_MEMORY (0xFFF - MEM_START)

#define SCREEN_WIDTH (64)
#define SCREEN_HEIGHT (32)
#define SCREEN_SIZE (SCREEN_WIDTH * SCREEN_HEIGHT)

#define FONT_MEM_SIZE 80
#define FONT_MEM_START_PTR (0x50)


typedef struct emulator {
    byte memory[MEM_SIZE];
    byte registers[16];

    unsigned short regIndex;
    unsigned short PC;
    unsigned short stack[16];

    byte SP;
    byte delayTimer;
    byte soundTimer;
    unsigned short opcode;  

    unsigned int video[SCREEN_SIZE];
    byte keypad[16];  

} Emulator_t;

extern Emulator_t __emulator;



// EMULATOR
#define V(vx) __emulator.registers[vx]

// REGISTERS
#define VX V(((__emulator.opcode & 0x0F00u) >> 8))
#define VY V(((__emulator.opcode & 0x00F0u) >> 4))

// SPECIAL REGISTERS
#define VF (__emulator.registers[0xF])
#define I (__emulator.regIndex)

// RANDOM BYTE
#define RAND_NO (rand() & 0x00FFu)


byte EMULATOR_init();
byte EMULATOR_loadROM(char const* filePath);
byte EMULATOR_cycle();

#endif