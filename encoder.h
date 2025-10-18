#ifndef ENCODER_H
#define ENCODER_H
#define size 25
#define stringinput 17
void initalize();
void QRinit(char QRchar[stringinput],int QRdata[size][size]);
void fixptr(int QRdata[size][size],int b);
void findptr(int QRdata[size][size],int x,int y);
void tempformatbit(int QRdata[size][size]);
void dataconverter(int QRdata[size][size],char QRchar[stringinput]);
void writedata(int QRdata[size][size],int bit1);
#endif