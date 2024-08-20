#ifndef __EMULATOR_STACK__
#define __EMULATOR_STACK__

//  STACK OPERATIONS
#define STACK__PUSH(el) (__emulator.stack[__emulator.SP++] = el)
#define STACK__POP() (__emulator.stack[__emulator.SP--])
#define STACK__TOP() (__emulator.stack[__emulator.SP])

#endif