#include <fxcg/display.h>
#include <fxcg/keyboard.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define CALC_WIDTH 384
#define CALC_HEIGHT 216
#define FILE_PATH "\\\\fls0\\mizu5.bin"

typedef enum {
    STATUS_ENABLE = 2,
    STATUS_DISABLE = 3
} Status;

void Clear_Display();
void Locate_OS(int x, int y);
