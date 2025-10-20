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

void datawriter(int sizebyte ,int sizefull ,int bitdata[sizefull],int data[sizebyte]){
    int m=0;
    for(int i=0;i<sizefull;i++){
        if(bitdata[i]==2){
            bitdata[i]=data[m];
            m++;
        }
        if(m==sizebyte){
            break;
        }
    }

}

int main(){
    int i[10],m[8];
    binaryconverter(8,m,161);
    for(int m=0;m<10;m++){
        i[m]=2;
    }
    i[0]=0;
    datawriter(8,10,i,m);
    for(int m=0;m<10;m++){
        printf("%d",i[m]);
    }
    
    printf("\n");
    for(int n=0;n<8;n++){
        printf("%d",m[n]);
    }
    return 0;
}