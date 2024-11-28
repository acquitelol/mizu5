#include "mizu5.h"
#include "data.h"

int main() {
    bool firstRender = true;
    int key;

    if (tmp_mizu5_bin_len < CALC_WIDTH * CALC_HEIGHT * 2) {
        Print_OS("Binary data is too small!", 0, 0);
        return 1;
    }

    Bdisp_AllClr_VRAM();
    Clear_Display();

    EnableStatusArea(STATUS_ENABLE);
    DefineStatusAreaFlags(3, SAF_BATTERY | SAF_ALPHA_SHIFT | SAF_TEXT, 0, 0);
    Bdisp_EnableColor(1); // Enable 16-bit color mode

    for (;;) {
        // Wait for a key input after first render
        if (!firstRender) GetKey(&key);

        firstRender = false;
        unsigned short *p = GetVRAMAddress();

        for (int i = 0; i < CALC_WIDTH * CALC_HEIGHT; i++) {
            unsigned short color = (tmp_mizu5_bin[2 * i] << 8) | tmp_mizu5_bin[2 * i + 1];
            *p++ = color;
        }

        // 03A8 specifies that the GB18030 standard is being used
        // the other bytes correspond to "ごめんね。。。"
        PrintXY(1, 1, "\x03\xA8\xa4\xb4\xa4\xe1\xa4\xf3\xa4\xcd\xa1\xa3\xa1\xa3\xa1\xa3", 0, 0);
        DefineStatusMessage("I can't sing with you all anymore.", 1, 0, 0);
        DisplayStatusArea();
        Bdisp_PutDisp_DD();
    }

    return 0;
}
