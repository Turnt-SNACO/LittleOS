#include "io.h"

#define COLOR_GREEN     2
#define COLOR_DARK_GREY 8

#define FB_COMMAND_PORT 0x3D4
#define FB_DATA_PORT    0x3D5

#define FB_HIGH_BYTE_COMMAND 14
#define FB_LOW_BYTE_COMMAND  15

char * fb_colors = (char *) 0x000B8000;

void WriteCellWithColors(unsigned int i, char c, unsigned char foreground, unsigned char background)
{
    fb_colors[i] = c;
    fb_colors[i + 1] = ((foreground & 0x0F) << 4) | (background & 0x0F);
}

void KMain()
{
    FBWriteCellWithColors(0, 'A', COLOR_GREEN, COLOR_DARK_GREY);
}

void MoveCursor(unsigned short position)
{
    SendDataToPort(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    SendDataToPort(FB_DATA_PORT, ((position >> 8) & 0x00FF));
    SendDataToPort(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    SendDataToPort(FB_DATA_PORT, position & 0x00FF);
}

int SumOfThree(int arg1, int arg2, int arg3) 
{
    return arg1 + arg2 + arg3;
}