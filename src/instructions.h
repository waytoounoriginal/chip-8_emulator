#ifndef __EMULATOR_INSTRUCTIONS__
#define __EMULATOR_INSTRUCTIONS__

/*
Jump to a machine code routine at nnn.

This instruction is only used on the old computers on which Chip-8 was originally implemented. It is ignored by modern interpreters.
*/
void OP_0NNN(void) __attribute__((deprecated("Instruction used only by old machines")));

/*
Clear the display.
*/
void OP_00E0(void);

/*
Return from a subroutine.

The interpreter sets the program counter to the address at the top of the stack, then subtracts 1 from the stack pointer.
*/
void OP_00EE(void);

/*
Jump to location nnn.

The interpreter sets the program counter to nnn.
*/
void OP_1NNN(void);

/*
Call subroutine at nnn.

The interpreter increments the stack pointer, then puts the current PC on the top of the stack. The PC is then set to nnn.
*/
void OP_2NNN(void);

/*
Skip next instruction if Vx = kk.

The interpreter compares register Vx to kk, and if they are equal, increments the program counter by 2.
*/
void OP_3XKK(void);

/*
Skip next instruction if Vx != kk.

The interpreter compares register Vx to kk, and if they are not equal, increments the program counter by 2.
*/
void OP_4XKK(void);

/*
Skip next instruction if Vx = Vy.

The interpreter compares register Vx to register Vy, and if they are equal, increments the program counter by 2.
*/
void OP_5XY0(void);

/*
Set Vx = kk.

The interpreter puts the value kk into register Vx.
*/
void OP_6XKK(void);

/*
Set Vx = Vx + kk.

Adds the value kk to the value of register Vx, then stores the result in Vx.
*/
void OP_7XKK(void);

/*
Set Vx = Vy.

Stores the value of register Vy in register Vx.
*/
void OP_8XY0(void);

/*
Set Vx = Vx OR Vy.

Performs a bitwise OR on the values of Vx and Vy, then stores the result in Vx. A bitwise OR compares the corrseponding bits from two values, and if either bit is 1, then the same bit in the result is also 1. Otherwise, it is 0.
*/
void OP_8XY1(void);

/*
Set Vx = Vx AND Vy.

Performs a bitwise AND on the values of Vx and Vy, then stores the result in Vx. A bitwise AND compares the corrseponding bits from two values, and if both bits are 1, then the same bit in the result is also 1. Otherwise, it is 0.
*/
void OP_8XY2(void);

/*
Set Vx = Vx XOR Vy.

Performs a bitwise exclusive OR on the values of Vx and Vy, then stores the result in Vx. An exclusive OR compares the corrseponding bits from two values, and if the bits are not both the same, then the corresponding bit in the result is set to 1. Otherwise, it is 0.
*/
void OP_8XY3(void);

/*
Set Vx = Vx + Vy, set VF = carry.

The values of Vx and Vy are added together. If the result is greater than 8 bits (i.e., > 255,) VF is set to 1, otherwise 0. Only the lowest 8 bits of the result are kept, and stored in Vx.
*/
void OP_8XY4(void);

/*
Set Vx = Vx - Vy, set VF = NOT borrow.

If Vx > Vy, then VF is set to 1, otherwise 0. Then Vy is subtracted from Vx, and the results stored in Vx.
*/
void OP_8XY5(void);

/*
Set Vx = Vx SHR 1.

If the least-significant bit of Vx is 1, then VF is set to 1, otherwise 0. Then Vx is divided by 2.
*/
void OP_8XY6(void);

/*
Set Vx = Vy - Vx, set VF = NOT borrow.

If Vy > Vx, then VF is set to 1, otherwise 0. Then Vx is subtracted from Vy, and the results stored in Vx.
*/
void OP_8XY7(void);

/*
Set Vx = Vx SHL 1.

If the most-significant bit of Vx is 1, then VF is set to 1, otherwise to 0. Then Vx is multiplied by 2.
*/
void OP_8XYE(void);

/*
Skip next instruction if Vx != Vy.

The values of Vx and Vy are compared, and if they are not equal, the program counter is increased by 2.
*/
void OP_9XY0(void);

/*
Set I = nnn.

The value of register I is set to nnn.
*/
void OP_ANNN(void);

/*
Jump to location nnn + V0.

The program counter is set to nnn plus the value of V0.
*/
void OP_BNNN(void);

/*
Set Vx = random byte AND kk.

The interpreter generates a random number from 0 to 255, which is then ANDed with the value kk. The results are stored in Vx. See instruction 8xy2 for more information on AND.
*/
void OP_CXKK(void);

/*
Display n-byte sprite starting at memory location I at (Vx, Vy), set VF = collision.

The interpreter reads n bytes from memory, starting at the address stored in I. These bytes are then displayed as sprites on screen at coordinates (Vx, Vy). Sprites are XORed onto the existing screen. If this causes any pixels to be erased, VF is set to 1, otherwise it is set to 0. If the sprite is positioned so part of it is outside the coordinates of the display, it wraps around to the opposite side of the screen. See instruction 8xy3 for more information on XOR, and section 2.4, Display, for more information on the Chip-8 screen and sprites.
*/
void OP_DXYN(void);

/*
Skip next instruction if key with the value of Vx is pressed.

Checks the keyboard, and if the key corresponding to the value of Vx is currently in the down position, PC is increased by 2.
*/
void OP_EX9E(void);

/*
Skip next instruction if key with the value of Vx is not pressed.

Checks the keyboard, and if the key corresponding to the value of Vx is currently in the up position, PC is increased by 2.
*/
void OP_EXA1(void);

/*
Set Vx = delay timer value.

The value of DT is placed into Vx.
*/
void OP_FX07(void);

/*
Wait for a key press, store the value of the key in Vx.

All execution stops until a key is pressed, then the value of that key is stored in Vx.
*/
void OP_FX0A(void);

/*
Set delay timer = Vx.

DT is set equal to the value of Vx.
*/
void OP_FX15(void);

/*
Set sound timer = Vx.

ST is set equal to the value of Vx.
*/
void OP_FX18(void);

/*
Set I = I + Vx.

The values of I and Vx are added, and the results are stored in I.
*/
void OP_FX1E(void);

/*
Set I = location of sprite for digit Vx.

The value of I is set to the location for the hexadecimal sprite corresponding to the value of Vx.
*/
void OP_FX29(void);

/*
Store BCD representation of Vx in memory locations I, I+1, and I+2.

The interpreter takes the decimal value of Vx, and places the hundreds digit in memory at location in I, the tens digit at location I+1, and the ones digit at location I+2.
*/
void OP_FX33(void);

/*
Store registers V0 through Vx in memory starting at location I.

The interpreter copies the values of registers V0 through Vx into memory, starting at the address in I.
*/
void OP_FX55(void);

/*
Read registers V0 through Vx from memory starting at location I.

The interpreter reads values from memory starting at location I into registers V0 through Vx.
*/
void OP_FX65(void);

/*
A NULOP operation
*/
void OP_NULL(void);


extern void (*funcTable[0xE + 1])(void);
extern void (*funcTable__8[0xE + 1])(void);
extern void (*funcTable__ZERO[0xE + 1])(void);
extern void (*funcTable__E[0xE + 1])(void);
extern void (*funcTable__F[0x65 + 1])(void);

//  Sets up the func tables
void INSTRUCTIONS_init(void);


#endif