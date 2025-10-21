#ifndef ENCODER_H
#define ENCODER_H

void fixptr(int QRsize, int QRdata[QRsize][QRsize],int b);
void findptr(int QRsize , int QRdata[QRsize][QRsize],int x,int y);
void initalize(int version , int strsize , int corlvl , int QRsize);
void tempformatbit(int QRsize ,int QRdata[QRsize][QRsize],int version);
void border(int QRsize , int QRdata[QRsize][QRsize]);
void alignment(int QRsize ,int QRdata[QRsize][QRsize],int x,int y);
void writedata(int QRsize ,int QRdata[QRsize][QRsize],int bit1);
void dataconverter(int QRsize ,int stringinput,int QRdata[QRsize][QRsize],char QRchar[stringinput],int version);
void QRinit(int QRsize ,int stringinput ,char QRchar[stringinput],int QRdata[QRsize][QRsize],int version,int i );
void genalignmark(int version , int QRsize,int QRdata[QRsize][QRsize]);
void binaryconverter(int size,int arr[size],int data);
void datawriter(int sizebyte ,int sizefull ,int bitdata[sizefull],int data[sizebyte]);
#endif