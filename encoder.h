#ifndef ENCODER_H
#define ENCODER_H

void fixptr(int QRsize, int QRdata[QRsize][QRsize],int b);
void findptr(int QRsize , int QRdata[QRsize][QRsize],int x,int y);
void initalize(int version , int strsize , int corlvl , int QRsize);
void tempformatbit(int QRsize ,int QRdata[QRsize][QRsize]);
void border(int QRsize , int QRdata[QRsize][QRsize]);
void alignment(int QRsize ,int QRdata[QRsize][QRsize],int x,int y);
void writedata(int QRsize ,int QRdata[QRsize][QRsize],int bit1);
void dataconverter(int QRsize ,int stringinput,int QRdata[QRsize][QRsize],char QRchar[stringinput]);
void QRinit(int QRsize ,int stringinput ,char QRchar[stringinput],int QRdata[QRsize][QRsize],int version);
void genalignmark(int version , int QRsize,int QRdata[QRsize][QRsize]);
#endif