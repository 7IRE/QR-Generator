#include "QRrenderer.h"
#include <stdio.h>

//To print individual pixels at 2*1 size
void block(int a,int b , int c){
    a += 2, b += 2;
    int x,y;
    if(a==0){
        x=a;
    }
    else{
        x=a+1;
    }
    if(b==0){
        y=2*b;
    }
    else{
        y=2*b+1;
    }
    //1-BLACK , 0-WHITE
    if(c==1){
        printf("\033[40m");
    }
    else if(c==0){
        printf("\033[47m");
    }
    else if(c==2){
        printf("\033[100m");
    }
    printf("\033[%d;%dH",x,y);
    printf("  \033[0m");
}

void display(int QRsize,int arr[QRsize][QRsize],int row,int column){
    printf("\033[2J");
    for(int i=0;i<QRsize+4;i++){
        block(i,0,0);
        block(0,i,0);
        block(QRsize-i,0,0);
        block(0,QRsize-i,0);
    }
    for(int i=1;i<QRsize+3;i++){
        block(i,1,0);
        block(1,i,0);
        block(QRsize-i,1,0);
        block(1,QRsize-i,0);
    }
    for(int i=0;i<row;i++){
        for(int j=0;j<column;j++){
            block(i+2,j+2,(int)arr[i][j]);
        }
    }
}