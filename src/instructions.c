#include "instructions.h"
#include "emulator.h"

void (*funcTable[0xE + 1])(void);
void (*funcTable__8[0xE + 1])(void);
void (*funcTable__ZERO[0xE + 1])(void);
void (*funcTable__E[0xE + 1])(void);
void (*funcTable__F[0x65 + 1])(void);



void OP_0NNN(void) {

    short addr = __emulator.opcode & 0x0FFFu;
    __emulator.PC = addr;
}

void OP_00E0(void) {

    // memset
    for(int i = 0; i < SCREEN_SIZE; i++)
        __emulator.video[i] = 0;
}

void OP_00EE(void) {
    //  POP
    __emulator.PC = __emulator.stack[--__emulator.SP];
}

void OP_1NNN(void) {
    short addr = __emulator.opcode & 0x0FFFu;
    __emulator.PC = addr;
}

void OP_2NNN(void) {
    short addr = __emulator.opcode & 0x0FFFu;

    //  PUSH
    __emulator.stack[__emulator.SP++] = __emulator.PC;
    
    __emulator.PC = addr;
}

void OP_3XKK(void) {
    byte KK = __emulator.opcode & 0x00FFu;

    if(VX == KK) __emulator.PC += 2;
}

void OP_4XKK(void) {
    byte KK = __emulator.opcode & 0x00FFu;

    if(VX != KK) __emulator.PC += 2;
}

void OP_5XY0(void) {

    if(VX == VY) __emulator.PC += 2;
}

void OP_6XKK(void) {
    byte KK = __emulator.opcode & 0x00FFu;

    VX = KK;
}

void OP_7XKK(void) {
    byte KK = __emulator.opcode & 0x00FFu;

    VX += KK;
}

void OP_8XY0(void) {

    VX = VY;
}

void OP_8XY1(void) {

    VX |= VY;
}

void OP_8XY2(void) {

    VX &= VY;
}

void OP_8XY3(void) {

    VX ^= VY;
}

void OP_8XY4(void) {

    VX += VY;

    if(VX & 0x0F00u) {
        VF = 1;
        VX &= 0x00FFu;
    } else {
        VF = 0;
    }
}

void OP_8XY5(void) {
    if(VX > VY) {
        VF = 1;
    } else {
        VF = 0;
    }

    VX -= VY;
}

void OP_8XY6(void) {
    VF = (VX & 0x1u);
    VX >>= 1;
}

void OP_8XY7(void) {
    VF = VY > VX ? 1 : 0;
    VX = VY - VX;
}

void OP_8XYE(void) {
    VF = (VX & 0x1u);
    VX <<= 1;
}

void OP_9XY0(void) {
    if(VX != VY) __emulator.PC += 2;
}

void OP_ANNN(void) {
    I = __emulator.opcode & 0x0FFFu;
}

void OP_BNNN(void) {
    short addr = __emulator.opcode & 0x0FFFu;
    __emulator.PC = V(0) + addr;
}

void OP_CXKK(void) {
    byte KK = __emulator.opcode & 0x00FFu;

    VX = (KK & RAND_NO);
}

//  WTF? Thanks tutorial
void OP_DXYN(void) {
    //  Coordonates are (Vx, Vy)
    
    //  Read N bytes from the addres of I
    byte n = __emulator.opcode & 0x000Fu;

    //  We will draw at the same time
    byte x = VX % SCREEN_WIDTH;
    byte y = VY % SCREEN_HEIGHT;

    VF = 0;

    for(int i = 0; i < n; i++) {

        byte spriteByte = __emulator.memory[I + i];

        for(int col = 0; col < 8; col++) {
            byte spritePixel = spriteByte & (0x80u >> col);
            unsigned int* screenPixel = &__emulator.video[(y + i) * SCREEN_WIDTH + (x + col)];

            if(spritePixel) {
                //  Collision
                if(*screenPixel == 0xFFFFFFFFu)
                    VF = 1;

                //  Xor with the sprite pixel
                *screenPixel ^= 0xFFFFFFFFu;
            }
        }
    }
}

void OP_EX9E(void) {
    byte key = VX;

    if(__emulator.keypad[key]) __emulator.PC += 2;
}

void OP_EXA1(void) {
    byte key = VX;

    if(!__emulator.keypad[key]) __emulator.PC += 2;
}

void OP_FX07(void) {
    VX = __emulator.delayTimer;
}

void OP_FX0A(void) {
    for(int i = 0x0; i < 0xF; i++) {
        if(__emulator.keypad[i]) {
            VX = i;
            break;
        }
    }
}

void OP_FX15(void) {
    __emulator.delayTimer = VX;
}

void OP_FX18(void) {
    __emulator.soundTimer = VX;
}

void OP_FX1E(void) {
    I += VX;
}

void OP_FX29(void) {
    //  A sprite is 5 bytes long
    I = FONT_MEM_START_PTR + (5 * VX);
}

void OP_FX33(void) {
    byte value = VX;

    __emulator.memory[I] = value / 100;
    __emulator.memory[I + 1] = (value & 100) / 10;
    __emulator.memory[I + 2] = value % 10;
}

void OP_FX55(void) {
    byte vx = ((__emulator.opcode & 0x0F00u) >> 8);

    for(int i = 0; i <= vx; i++) {
        __emulator.memory[I + i] = V(i);
    }
}

void OP_FX65(void) {
    byte vx = ((__emulator.opcode & 0x0F00u) >> 8);

    for(int i = 0; i <= vx; i++) {
        V(i) = __emulator.memory[I + i];
    }
}

void OP_NULL(void) {
    //  Do nothing
}

//  Helper functions
static void __table0(void) {
    (*funcTable__ZERO[__emulator.opcode & 0x000Fu])();
}

static void __table8(void) {
    (*funcTable__8[__emulator.opcode & 0x000Fu])();
}

static void __tableE(void) {
    (*funcTable__E[__emulator.opcode & 0x000Fu])();
}

static void __tableF(void) {
    (*funcTable__F[__emulator.opcode & 0x00FFu])();
}

void INSTRUCTIONS_init(void) {
    //  Set everything to null
    for(int i = 0; i < 0xF + 1; i++) {
        funcTable[i] = OP_NULL;
        funcTable__8[i] = OP_NULL;
        funcTable__ZERO[i] = OP_NULL;
        funcTable__E[i] = OP_NULL;
    }

    // Set the F table
    for(int i = 0; i < 0x65 + 1; i++) {
        funcTable__F[i] = OP_NULL;
    }



    //  The unique funcs first
    funcTable[0x0] = __table0;
    funcTable[0x1] = OP_1NNN;
    funcTable[0x2] = OP_2NNN;
    funcTable[0x3] = OP_3XKK;
    funcTable[0x4] = OP_4XKK;
    funcTable[0x5] = OP_5XY0;
    funcTable[0x6] = OP_6XKK;
    funcTable[0x7] = OP_7XKK;
    funcTable[0x8] = __table8;
    funcTable[0x9] = OP_9XY0;
    funcTable[0xA] = OP_ANNN;
    funcTable[0xB] = OP_BNNN;
    funcTable[0xC] = OP_CXKK;
    funcTable[0xD] = OP_DXYN;
    funcTable[0xE] = __tableE;

    //  The 8 table
    funcTable__8[0x0] = OP_8XY0;
    funcTable__8[0x1] = OP_8XY1;
    funcTable__8[0x2] = OP_8XY2;
    funcTable__8[0x3] = OP_8XY3;
    funcTable__8[0x4] = OP_8XY4;
    funcTable__8[0x5] = OP_8XY5;
    funcTable__8[0x6] = OP_8XY6;
    funcTable__8[0x7] = OP_8XY7;
    funcTable__8[0xE] = OP_8XYE;

    //  The E table
    funcTable__E[0x1] = OP_EXA1;
    funcTable__E[0xE] = OP_EX9E;

    //  The F table
    funcTable__F[0x07] = OP_FX07;
    funcTable__F[0x0A] = OP_FX0A;
    funcTable__F[0x15] = OP_FX15;
    funcTable__F[0x18] = OP_FX18;
    funcTable__F[0x1E] = OP_FX1E;
    funcTable__F[0x29] = OP_FX29;
    funcTable__F[0x33] = OP_FX33;
    funcTable__F[0x55] = OP_FX55;
    funcTable__F[0x65] = OP_FX65;

    //  The 0 table
    funcTable__ZERO[0x0] = OP_00E0;
    funcTable__ZERO[0xE] = OP_00EE;
}