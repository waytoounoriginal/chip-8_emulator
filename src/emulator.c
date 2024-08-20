#include "emulator.h"
#include "instructions.h"

Emulator_t __emulator = {};

static byte __loadFont() {

    const byte chip8Font[FONT_MEM_SIZE] =
    {
        0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
        0x20, 0x60, 0x20, 0x20, 0x70, // 1
        0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
        0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
        0x90, 0x90, 0xF0, 0x10, 0x10, // 4
        0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
        0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
        0xF0, 0x10, 0x20, 0x40, 0x40, // 7
        0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
        0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
        0xF0, 0x90, 0xF0, 0x90, 0x90, // A
        0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
        0xF0, 0x80, 0x80, 0x80, 0xF0, // C
        0xE0, 0x90, 0x90, 0x90, 0xE0, // D
        0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
        0xF0, 0x80, 0xF0, 0x80, 0x80  // F
    };


    // load into emulator
    for(int i = 0; i < FONT_MEM_SIZE; i++) {
        __emulator.memory[FONT_MEM_START_PTR + i] = chip8Font[i];
    }

    return EMULATOR__SUCCESS;
}

byte EMULATOR_init() {
    //  Setup the randomness
    srand(time(NULL));


    //  We should load the font
    __loadFont(__emulator);

    __emulator.delayTimer = 0;
    __emulator.soundTimer = 0;

    // Init the instructions
    INSTRUCTIONS_init();

    __emulator.PC = MEM_START;
    __emulator.SP = 0;
}

byte EMULATOR_loadROM(char const* filePath) {
    FILE* fp = fopen(filePath, "rb");
    
    if(fp == NULL) return EMULATOR__FILE_NOT_FOUND;

    // Get file size
    fseek(fp, 0L, SEEK_END);
    int sz = ftell(fp);

    if(sz >= PROGRAM_MEMORY) {
        fclose(fp);
        return EMULATOR__FILE_TOO_BIG;
    }

    rewind(fp);

    // Read the file into a buffer
    byte _buffer[PROGRAM_MEMORY] = {};
    fread(_buffer, sizeof(*_buffer), sz, fp);

    // Free the file
    fclose(fp);

    // Load the program into memory
    for(int i = 0; i < sz; i++) {
        __emulator.memory[MEM_START + i] = _buffer[i];
        printf("memory: 0x%04x\tcode: 0x%04x\n", (MEM_START + i), _buffer[i]);
    }

    printf("Loaded ROM ===================\n");

    return EMULATOR__SUCCESS;
}

static void __debugText() {

    printf("PC:\t0x%03x\n", __emulator.PC);
    printf("SP:\t%d\n", __emulator.SP);
    printf("PC MEM:\t0x%02x\n", __emulator.memory[__emulator.PC]);
    printf("PC + 1 MEM:\t0x%02x\n", __emulator.memory[__emulator.PC + 1]);
    printf("OPCODE:\t0x%04x\n", __emulator.opcode);

    printf("\n====================\n");

    //  Print the stack
    printf("STACK:\t");
    for(int i = 0; i < __emulator.SP; i++) {
        printf("| 0x%04x | ", __emulator.stack[i]);
    }
    printf("\n====================\n");

    printf("I:\t0x%04x\n", __emulator.regIndex);
    // Register dump
    for(int i = 0; i < 16; i++) {
        printf("V%d:\t0x%02x\n", i, __emulator.registers[i]);
    }

    printf("\n====================\n\n");


}

byte EMULATOR_cycle() {
    //  We are taking 2 bytes at a time
    __emulator.opcode = (__emulator.memory[__emulator.PC] << 8) | __emulator.memory[__emulator.PC + 1];
    
    //  __debugText();

    //  Incrementing
    __emulator.PC += 2;

    //  Execute
    (*funcTable[(__emulator.opcode & 0xF000u) >> 12])();


    if(__emulator.delayTimer > 0) --__emulator.delayTimer;
    if(__emulator.soundTimer > 0) --__emulator.soundTimer;

    // Check PC. We will emulate throwing ability
    if(__emulator.PC < 0x200) {
        return EMULATOR__INVALID_PC;
    }

    return EMULATOR__SUCCESS;
}