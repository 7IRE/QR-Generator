#include <stdio.h>
#include "renderer.h"
#include "encoder.h"

#define stringinput 17
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
    char QRchar[stringinput];
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

void alignment(int QRdata[size][size],int x,int y){
    for(int i=0;i<5;i++){
        QRdata[i+x][y]=1;
        QRdata[x][y+i]=1;
        QRdata[i+x][y+4]=1;
        QRdata[x+4][y+i]=1;
    }
    for(int i=0;i<3;i++){
        QRdata[i+x+1][y+1]=2;
        QRdata[x+1][y+1+i]=2;
        QRdata[i+1+x][y+1+2]=2;
        QRdata[x+1+2][y+1+i]=2;
    }
    QRdata[x+2][y+2]=1;
}

void writedata(int QRdata[size][size],int bit1){
    if(bit1==0){
        bit1=2;
    }
    if(bit1==1){
        bit1=1;
    }
    int pos[2]={size-3,size-3};
    int dir = 1;
    // 1-UP , 2-DOWN
    while(1){
        if(dir==1){
            if(QRdata[pos[0]][pos[1]]==0){
                QRdata[pos[0]][pos[1]]=bit1;
                break;
            }
            pos[1] -= 1;
            if(QRdata[pos[0]][pos[1]]==0){
                QRdata[pos[0]][pos[1]]=bit1;
                break;
            }
            pos[1] += 1;
            pos[0] -= 1;
        }
        else if(dir == 2){
            if(QRdata[pos[0]][pos[1]]==0){
                QRdata[pos[0]][pos[1]]=bit1;
                break;
            }
            pos[1] -= 1;
            if(QRdata[pos[0]][pos[1]]==0){
                QRdata[pos[0]][pos[1]]=bit1;
                break;
            }
            pos[1] += 1;
            pos[0] += 1;
        }
    }
    //Change direction
    if(dir==1&&pos[0]==2&&QRdata[pos[0]][pos[1]]!=0){
        for(int i=1 ; i<size ; i += 2){
            if(pos[1]==size-i){
                dir=2;
                pos[1] -= 1;
            }
        }    
    }
    else if(dir==2&&pos[0]==size-3&&QRdata[pos[0]][pos[1]!=0]){
        for(int i=1 ; i<size ; i+=2){
            if(pos[1]==size-i){
                dir=1;
                pos[1] -= 1;
            }
        }
    }
}


void dataconverter(int QRdata[size][size],char QRchar[stringinput]){
    //byte mode
    writedata(QRdata,0);
    writedata(QRdata,1);
    writedata(QRdata,0);
    writedata(QRdata,0);
    int a,b;
    // for(int i=0;i<stringinput;i++){
    //     a=QRchar[i],b=0;
    //     while(a!=0){
            
    //     }
    // }
}

void QRinit(char QRchar[stringinput],int QRdata[size][size]){
    fixptr(QRdata,8);
    findptr(QRdata,1,1);
    findptr(QRdata,size-10,1);
    findptr(QRdata,1,size-10);
    tempformatbit(QRdata);
    border(QRdata);
    int QRmask[size][size]={0};
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            if(QRdata[i][j]==0){
                QRmask[i][j]==1;
            }
        }
    }
    dataconverter(QRdata,QRchar);
    display(QRdata,size,size);
}

int main(){
    initalize();
    return 0;
}