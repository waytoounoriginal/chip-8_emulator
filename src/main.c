#include <time.h>

#include "emulator.h"
#include "platform.h"

#define VIDEO_SCALE 10
#define CYCLE_DELAY 3

int main(int argc, char** argv) {
    if(argc != 2) {
        printf("Usage: %s <ROM>", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    char const* romFile = argv[1];

    EMULATOR_init();
    PLATFORM_init("CHIP-8 Emulator", SCREEN_WIDTH * VIDEO_SCALE, SCREEN_HEIGHT * VIDEO_SCALE, SCREEN_WIDTH, SCREEN_HEIGHT);

    //  Load the rom
    byte success = EMULATOR_loadROM(romFile);


    if(success != EMULATOR__SUCCESS) {
        printf("Error!");
        exit(EXIT_FAILURE);
    }

    int videoPitch = sizeof(__emulator.video[0]) * SCREEN_WIDTH;

    int quit = 0;

    int lastCycleTime = 0;

    while(!quit) {
        quit = PLATFORM_processInput(__emulator.keypad);

        //  Check if we need to cycle
        int currentTime = clock();
        if(currentTime - lastCycleTime < CYCLE_DELAY) {
            continue;
        }

        lastCycleTime = currentTime;

        // Cycle
        byte successCycle = EMULATOR_cycle();

        if(successCycle != EMULATOR__SUCCESS) {
            printf("Error during cycle!");
            PLATFORM_destroy();
            exit(EXIT_FAILURE);
        }

        PLATFORM_update(__emulator.video, videoPitch);
    }

    PLATFORM_destroy();

    return 0;
}