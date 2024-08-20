#ifndef __EMULATOR_ERRORS__
#define __EMULATOR_ERRORS__


enum EmulatorStates {
    /* Base status */
    EMULATOR__SUCCESS = 0,
    /* File not found */
    EMULATOR__FILE_NOT_FOUND = 1,
    /* Instructions occupy more than the available program space (0xFFF - 0x200 bytes)*/
    EMULATOR__FILE_TOO_BIG,
    /* Program counter reached invalid space */
    EMULATOR__INVALID_PC,

    /* Platform specific. Failed SDL2 Video init*/
    EMULATOR__FAILED_VIDEO_INIT,
    /* Platform specific. Failed SDL2 Window init*/
    EMULATOR__FAILED_WINDOW_INIT,
    /* Platform specific. Failed SDL2 Renderer init*/
    EMULATOR__FAILED_RENDERER_INIT,
    /* Platform specific. Failed SDL2 Texture init*/
    EMULATOR__FAILED_TEXTURE_INIT
};


#endif