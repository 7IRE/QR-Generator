#include <stdio.h>
#include "renderer.h"
#include "encoder.h"


void fixptr(int QRdata[size][size],int b){
    //Timing pattern
    int a=1;
    for(int i=0;i<size-4;i++){
        QRdata[i+2][b]=a;
        QRdata[b][i+2]=a;
        if(a==1){
            a=2;
        }
        else if(a==2){
            a=1;
        }
    }   
}

void findptr(int QRdata[size][size],int x,int y){
    for(int i=0;i<9;i++){
        QRdata[x+i][y]=2;
        QRdata[x+i][y+8]=2;
        QRdata[x][y+i]=2;
        QRdata[x+8][y+i]=2;
    }
    for(int i=0;i<7;i++){
        QRdata[x+1+i][y+1]=1;
        QRdata[x+1][y+1+i]=1;
        QRdata[x+1+i][y-1+8]=1;
        QRdata[x-1+8][y+1+i]=1;
    }
    for(int i=0;i<5;i++){
        QRdata[x+2+i][y+2]=2;
        QRdata[x+2][y+2+i]=2;
        QRdata[x+2+i][y-2+8]=2;
        QRdata[x-2+8][y+2+i]=2;
    }
    for(int i=0;i<3;i++){
        QRdata[x+3+i][y+3]=1;
        QRdata[x+3][y+3+i]=1;
        QRdata[x+3+i][y-3+8]=1;
        QRdata[x-3+8][y+3+i]=1;
    }
    QRdata[x+4][y+4]=1;
}

void initalize(){
    char QRchar[28];
    scanf("%s",&QRchar);
    int QRdata[size][size]={0};
    QRinit(QRchar,QRdata);
}


void tempformatbit(int QRdata[size][size]){
        for(int i=0;i<9;i++){
            if(QRdata[10][2+i]==0){
                QRdata[10][2+i]=2;
            }
            if(QRdata[2+i][10]==0){
                QRdata[2+i][10]=2;
            }
            if(QRdata[10][size-10+i]==0){
                QRdata[10][size-10+i]=2;
            }
            if(QRdata[2+i][10]==0){
                QRdata[2+i][10]=2;
            }
            if(QRdata[size-10+i][10]==0){
                QRdata[size-10+i][10]=2;
            }
            QRdata[size-10][10]=1;
        }
}
void border(int QRdata[size][size]){
    for(int i=0;i<size;i++){
        QRdata[size-1][i]=2;
        QRdata[size-2][i]=2;
        QRdata[i][size-1]=2;
        QRdata[i][size-2]=2;
        QRdata[0][i]=2;
        QRdata[1][i]=2;
        QRdata[i][0]=2;
        QRdata[i][1]=2;
    }
}

void QRinit(char QRchar[28],int QRdata[size][size]){
    fixptr(QRdata,8);
    findptr(QRdata,1,1);
    findptr(QRdata,size-10,1);
    findptr(QRdata,1,size-10);
    tempformatbit(QRdata);
    border(QRdata);

    display(QRdata,size,size);
}

int main(){
    initalize();
    return 0;
}