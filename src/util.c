#include "util.h"

void Clear_Display() {
    unsigned short *p = GetVRAMAddress();

    for (int i = 0; i < CALC_WIDTH * CALC_HEIGHT; i++) {
        *p++ = 65535;
    }

    Bdisp_PutDisp_DD();
}

void Locate_OS(int x, int y) {
    locate_OS(x, y);
}
