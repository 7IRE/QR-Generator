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
    binaryconverter(8,m,8);
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
    int QRchar[17];
    for(int i=0;i<=16;i++){
        QRchar[i]='-';
    }
    // printf("Enter Data To Encode:");
    // while(getchar()=='\n');
    // char cbuf;
    // int i=0;
    // while((cbuf = getchar())!='\n'){
    //     QRchar[i++]=cbuf;
    // }
    // QRchar[i]='\0';
    
    // for(int i=0;i<17;i++){
    //     printf("%c",QRchar[i]);
    // }
    // printf("%d",i);
    

    return 0;
}