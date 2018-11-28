#include "io.h"

#define COLOR_GREEN                     2
#define COLOR_DARK_GREY                 8
#define FB_COMMAND_PORT                 0x3D4
#define FB_DATA_PORT                    0x3D5
#define FB_HIGH_BYTE_COMMAND            14
#define FB_LOW_BYTE_COMMAND             15
#define SERIAL_COM1_BASE                0x3F8
#define SERIAL_DATA_PORT(base)          (base)
#define SERIAL_FIFO_COMMAND_PORT(base)  (base + 2)
#define SERIAL_LINE_COMMAND_PORT(base)  (base + 3)
#define SERIAL_MODEM_COMMAND_PORT(base) (base + 4)
#define SERIAL_LINE_STATUS_PORT(base)   (base + 5)
#define SERIAL_LINE_ENABLE_DLAB         0x80

char * fb_colors = (char *) 0x000B8000;
void FBMoveCursor(unsigned short position);


void FBWriteCell(unsigned int i, char c, unsigned char foreground, unsigned char background)
{
    fb_colors[i] = c;
    fb_colors[i + 1] = ((foreground & 0x0F) << 4) | (background & 0x0F);
}

void KMain()
{
    //FBWriteCell(0, 'H', COLOR_GREEN, COLOR_DARK_GREY);
    char * hello = "hello";
    write(hello, 5);
}

int write(char * buf, unsigned int length)
{
    unsigned int i = 0;
    for (;i < length; i++)
    {
        FBWriteCell(2*i, buf[(int)i], COLOR_GREEN, COLOR_DARK_GREY);
    }
    return 0;
}

void FBMoveCursor(unsigned short position)
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

void SerialConfigureBaudRate(unsigned short com, unsigned short divisor)
{
    SendDataToPort(SERIAL_LINE_COMMAND_PORT(com), SERIAL_LINE_ENABLE_DLAB);
    SendDataToPort(SERIAL_DATA_PORT(com), (divisor >> 8) & 0x00FF);
    SendDataToPort(SERIAL_DATA_PORT(com), divisor & 0x00FF);
}

void SerialConfigureLine(unsigned short com)
{
    SendDataToPort(SERIAL_LINE_COMMAND_PORT(com), 0x03);
}

int SerialIsTrasmitFIFOEmpty(unsigned int com)
{
    return GetDataFromPort(SERIAL_LINE_STATUS_PORT(com) & 0x20);
}