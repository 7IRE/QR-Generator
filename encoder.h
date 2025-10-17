#ifndef ENCODER_H
#define ENCODER_H
#define size 25
void initalize();
void QRinit(char QRchar[28],int QRdata[size][size]);
void fixptr(int QRdata[size][size],int b);
void findptr(int QRdata[size][size],int x,int y);
void tempformatbit(int QRdata[size][size]);
#endif