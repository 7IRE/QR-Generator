#include <stdio.h>



void binaryconverter(int size,int arr[size],int data){
    for(int i=0;i<size;i++){
        arr[i]=0;
    }
    int m=size-1;    
    while(data>0){
        arr[m]=data%2;
        data /= 2;
        m--;
    }
}

int main(){
    int i[8];
    binaryconverter(8,i,10);
    for(int m=0;m<8;m++){
        printf("%d",i[m]);
    }
    return 0;
}