#include "mizu5.h"

unsigned short fileNameBuffer[sizeof(FILE_PATH) * 2];
int fileHandle;

int main(void) {
    bool firstRender = true;

    Bdisp_AllClr_VRAM();
    Clear_Display();

    EnableStatusArea(STATUS_ENABLE);
    DefineStatusAreaFlags(3, SAF_BATTERY | SAF_TEXT, 0, 0);

    Bdisp_EnableColor(1); // Enable 16-bit color mode
    Bfile_StrToName_ncpy(fileNameBuffer, FILE_PATH, sizeof(FILE_PATH));
    fileHandle = Bfile_OpenFile_OS(fileNameBuffer, READ, 0);

    if (fileHandle < 0) {
        Locate_OS(1, 1);
        Print_OS("Error reading image", 0, 0);
        for (;;) GetKey(NULL);
    }

    for (;;) {
        // Wait for a key input after first render
        if (!firstRender) {
            int key;
            GetKey(&key);
        }

        firstRender = false;

        Bfile_SeekFile_OS(fileHandle, 0);
        unsigned short *p = GetVRAMAddress();

        for (int i = 0; i < CALC_WIDTH * CALC_HEIGHT; i++) {
            unsigned short color;

            if (Bfile_ReadFile_OS(fileHandle, &color, 2, -1) != 2) {
                *p++ = 0;
                continue;
            }

            *p++ = (color >> 8) | (color << 8); // Reverse byte order
        }

        // PrintXY(2, 0, "\0\0ominous bells", 0x20, 0);
        DefineStatusMessage("ominous bells", 1, 0, 0);
        DisplayStatusArea();
        Bdisp_PutDisp_DD();
    }

    Bfile_FindClose(fileHandle);
    Clear_Display();
    return 0;
}
