#ifndef INCLUDE_IO_H
#define INCLUDE_IO_H
void SendDataToPort(unsigned short port, unsigned char data);
char GetDataFromPort(unsigned short port);
int write(char *buf, unsigned int len);
int fb_write(char * buf, unsigned int len);
int serial_write(char * buf, unsigned int len);
#endif