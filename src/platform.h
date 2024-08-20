#ifndef __EMULATOR_PLATFORM__
#define __EMULATOR_PLATFORM__

#include "../includes/SDL2/SDL.h"

#include "types.h"
#include "err.h"

/*
Init function for the platform. Runs at the start of the program
*/
byte PLATFORM_init(char const* title, int windowWidth, int windowHeight, int textureWidth, int textureHeight);

/*
Clean up function for the platform. Runs at the end of the program
*/
void PLATFORM_destroy(void);

/*
Update function. Runs every cycle
*/
void PLATFORM_update(void const* buffer, int pitch);

/*
Process input function. Runs every cycle

We will use the following mappings:

Keypad       Keyboard
+-+-+-+-+    +-+-+-+-+
|1|2|3|C|    |1|2|3|4|
+-+-+-+-+    +-+-+-+-+
|4|5|6|D|    |Q|W|E|R|
+-+-+-+-+ => +-+-+-+-+
|7|8|9|E|    |A|S|D|F|
+-+-+-+-+    +-+-+-+-+
|A|0|B|F|    |Z|X|C|V|
+-+-+-+-+    +-+-+-+-+
*/
int PLATFORM_processInput(byte* keys);


static SDL_Window* _window;
static SDL_Renderer* _renderer;
static SDL_Texture* _texture;

#endif