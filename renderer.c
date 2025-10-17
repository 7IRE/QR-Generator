#include "renderer.h"
#include <stdio.h>
#define size 25

int main(){
    int data[25][25]={0};
    data[0][0]=1,data[1][1]=1,data[2][2]=1,data[3][3]=1,data[4][4]=1,data[5][5]=1;
    display(data,6,6);
}
//To print individual pixels at 2*1 size
void block(int a,int b , int c){
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
    if(c==0){
        printf("\033[40m");
    }
    else if(c==1){
        printf("\033[47m");
    }
    printf("\033[%d;%dH",x,y);
    printf("  \033[0m");
}

void display(int arr[size][size],int row,int column){
    printf("\033[2J");
    for(int i=0;i<row;i++){
        for(int j=0;j<column;j++){
            block(i,j,(int)arr[i][j]);
        }
    }
}