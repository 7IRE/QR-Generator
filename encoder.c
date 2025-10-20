#include <stdio.h>

#include "renderer.h"
#include "encoder.h"
#include <unistd.h>



void fixptr(int QRsize, int QRdata[QRsize][QRsize],int b){
    //Timing pattern
    int a=1;
    for(int i=0;i<QRsize-4;i++){
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

void findptr(int QRsize , int QRdata[QRsize][QRsize],int x,int y){
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

void initalize(int version , int strsize , int corlvl , int QRsize){
    char QRchar[strsize+1];
    printf("Enter Data To Encode:");
    while(getchar()=='\n');
    char cbuf;
    int i=0;
    while((cbuf = getchar())!='\n'){
        QRchar[i++]=cbuf;
    }
    QRchar[i]='\0';
    
    int QRdata[QRsize][QRsize];
    for(int i=0;i<QRsize;i++){
        for(int j=0;j<QRsize;j++){
            QRdata[i][j]=0;
        }
    }
    QRinit(QRsize,strsize,QRchar,QRdata,version,i);
}


void tempformatbit(int QRsize ,int QRdata[QRsize][QRsize],int version){
        for(int i=0;i<9;i++){
            if(QRdata[10][2+i]==0){
                QRdata[10][2+i]=2;
            }
            if(QRdata[2+i][10]==0){
                QRdata[2+i][10]=2;
            }
            if(QRdata[10][QRsize-10+i]==0){
                QRdata[10][QRsize-10+i]=2;
            }
            if(QRdata[2+i][10]==0){
                QRdata[2+i][10]=2;
            }
            if(QRdata[QRsize-10+i][10]==0){
                QRdata[QRsize-10+i][10]=2;
            }
            QRdata[QRsize-10][10]=1;
        }
        if(version>6){
            for(int i=0;i<6;i++){
                QRdata[QRsize-11][2+i]=2;
                QRdata[QRsize-12][2+i]=2;
                QRdata[QRsize-13][2+i]=2;
                QRdata[2+i][QRsize-11]=2;
                QRdata[2+i][QRsize-12]=2;
                QRdata[2+i][QRsize-13]=2;
            }
        }
}
void border(int QRsize , int QRdata[QRsize][QRsize]){
    for(int i=0;i<QRsize;i++){
        QRdata[QRsize-1][i]=2;
        QRdata[QRsize-2][i]=2;
        QRdata[i][QRsize-1]=2;
        QRdata[i][QRsize-2]=2;
        QRdata[0][i]=2;
        QRdata[1][i]=2;
        QRdata[i][0]=2;
        QRdata[i][1]=2;
    }
}
void genalignmark(int version , int QRsize,int QRdata[QRsize][QRsize]){
    if(version==1){
    }
    else if(version==2){
        int arr[]={6,18};
        int s=sizeof(arr)/sizeof(arr[0]);
        for(int i=0;i<s;i++){
            for(int j=0;j<s;j++){
                alignment(QRsize,QRdata,arr[i],arr[j]);
            }
        }
    }
    else if(version==3){
        int arr[]={6,22};
        int s=sizeof(arr)/sizeof(arr[0]);
        for(int i=0;i<s;i++){
            for(int j=0;j<s;j++){
                alignment(QRsize,QRdata,arr[i],arr[j]);
            }
        }
    }
    else if(version==4){
        int arr[]={6,26};
        int s=sizeof(arr)/sizeof(arr[0]);
        for(int i=0;i<s;i++){
            for(int j=0;j<s;j++){
                alignment(QRsize,QRdata,arr[i],arr[j]);
            }
        }
    }
    else if(version==5){
        int arr[]={6,30};
        int s=sizeof(arr)/sizeof(arr[0]);
        for(int i=0;i<s;i++){
            for(int j=0;j<s;j++){
                alignment(QRsize,QRdata,arr[i],arr[j]);
            }
        }
    }
    else if(version==6){
        int arr[]={6,34};
        int s=sizeof(arr)/sizeof(arr[0]);
        for(int i=0;i<s;i++){
            for(int j=0;j<s;j++){
                alignment(QRsize,QRdata,arr[i],arr[j]);
            }
        }
    }
    else if(version==7){
        int arr[]={6,22,38};
        int s=sizeof(arr)/sizeof(arr[0]);
        for(int i=0;i<s;i++){
            for(int j=0;j<s;j++){
                alignment(QRsize,QRdata,arr[i],arr[j]);
            }
        }
    }
    else if(version==8){
        int arr[]={6,24,42};
        int s=sizeof(arr)/sizeof(arr[0]);
        for(int i=0;i<s;i++){
            for(int j=0;j<s;j++){
                alignment(QRsize,QRdata,arr[i],arr[j]);
            }
        }
    }
    else if(version==9){
        int arr[]={6,26,46};
        int s=sizeof(arr)/sizeof(arr[0]);
        for(int i=0;i<s;i++){
            for(int j=0;j<s;j++){
                alignment(QRsize,QRdata,arr[i],arr[j]);
            }
        }
    }
    else if(version==10){
        int arr[]={6,28,50};
        int s=sizeof(arr)/sizeof(arr[0]);
        for(int i=0;i<s;i++){
            for(int j=0;j<s;j++){
                alignment(QRsize,QRdata,arr[i],arr[j]);
            }
        }
    }
    else if(version==11){
        int arr[]={6,30,54};
        int s=sizeof(arr)/sizeof(arr[0]);
        for(int i=0;i<s;i++){
            for(int j=0;j<s;j++){
                alignment(QRsize,QRdata,arr[i],arr[j]);
            }
        }
    }
    else if(version==12){
        int arr[]={6,32,58};
        int s=sizeof(arr)/sizeof(arr[0]);
        for(int i=0;i<s;i++){
            for(int j=0;j<s;j++){
                alignment(QRsize,QRdata,arr[i],arr[j]);
            }
        }
    }
    else if(version==13){
        int arr[]={6,34,62};
        int s=sizeof(arr)/sizeof(arr[0]);
        for(int i=0;i<s;i++){
            for(int j=0;j<s;j++){
                alignment(QRsize,QRdata,arr[i],arr[j]);
            }
        }
    }
    else if(version==14){
        int arr[]={6,26,46,66};
        int s=sizeof(arr)/sizeof(arr[0]);
        for(int i=0;i<s;i++){
            for(int j=0;j<s;j++){
                alignment(QRsize,QRdata,arr[i],arr[j]);
            }
        }
    }
    else if(version==15){
        int arr[]={	6,26,48,70};
        int s=sizeof(arr)/sizeof(arr[0]);
        for(int i=0;i<s;i++){
            for(int j=0;j<s;j++){
                alignment(QRsize,QRdata,arr[i],arr[j]);
            }
        }
    }
    else if(version==16){
        int arr[]={6,26,50,74};
        int s=sizeof(arr)/sizeof(arr[0]);
        for(int i=0;i<s;i++){
            for(int j=0;j<s;j++){
                alignment(QRsize,QRdata,arr[i],arr[j]);
            }
        }
    }
    else if(version==17){
        int arr[]={6,30,54,78};
        int s=sizeof(arr)/sizeof(arr[0]);
        for(int i=0;i<s;i++){
            for(int j=0;j<s;j++){
                alignment(QRsize,QRdata,arr[i],arr[j]);
            }
        }
    }
    else if(version==18){
        int arr[]={6,30,56,82};
        int s=sizeof(arr)/sizeof(arr[0]);
        for(int i=0;i<s;i++){
            for(int j=0;j<s;j++){
                alignment(QRsize,QRdata,arr[i],arr[j]);
            }
        }
    }
    else if(version==19){
        int arr[]={6,30,56,86};
        int s=sizeof(arr)/sizeof(arr[0]);
        for(int i=0;i<s;i++){
            for(int j=0;j<s;j++){
                alignment(QRsize,QRdata,arr[i],arr[j]);
            }
        }
    }
    else if(version==20){
        int arr[]={6,34,62,90};
        int s=sizeof(arr)/sizeof(arr[0]);
        for(int i=0;i<s;i++){
            for(int j=0;j<s;j++){
                alignment(QRsize,QRdata,arr[i],arr[j]);
            }
        }
    }
    else if(version==21){
        int arr[]={6,28,50,72,94};
        int s=sizeof(arr)/sizeof(arr[0]);
        for(int i=0;i<s;i++){
            for(int j=0;j<s;j++){
                alignment(QRsize,QRdata,arr[i],arr[j]);
            }
        }
    }
    else if(version==22){
        int arr[]={6,26,50,74,98};
        int s=sizeof(arr)/sizeof(arr[0]);
        for(int i=0;i<s;i++){
            for(int j=0;j<s;j++){
                alignment(QRsize,QRdata,arr[i],arr[j]);
            }
        }
    }
    else if(version==23){
        int arr[]={6,30,54,78,102};
        int s=sizeof(arr)/sizeof(arr[0]);
        for(int i=0;i<s;i++){
            for(int j=0;j<s;j++){
                alignment(QRsize,QRdata,arr[i],arr[j]);
            }
        }
    }
    else if(version==24){
        int arr[]={6,28,54,80,106};
        int s=sizeof(arr)/sizeof(arr[0]);
        for(int i=0;i<s;i++){
            for(int j=0;j<s;j++){
                alignment(QRsize,QRdata,arr[i],arr[j]);
            }
        }
    }
    else if(version==25){
        int arr[]={6,32,58,84,110};
        int s=sizeof(arr)/sizeof(arr[0]);
        for(int i=0;i<s;i++){
            for(int j=0;j<s;j++){
                alignment(QRsize,QRdata,arr[i],arr[j]);
            }
        }
    }
    else if(version==26){
        int arr[]={6,30,58,86,114};
        int s=sizeof(arr)/sizeof(arr[0]);
        for(int i=0;i<s;i++){
            for(int j=0;j<s;j++){
                alignment(QRsize,QRdata,arr[i],arr[j]);
            }
        }
    }
    else if(version==27){
        int arr[]={6,34,62,90,118};
        int s=sizeof(arr)/sizeof(arr[0]);
        for(int i=0;i<s;i++){
            for(int j=0;j<s;j++){
                alignment(QRsize,QRdata,arr[i],arr[j]);
            }
        }
    }
    else if(version==28){
        int arr[]={6,26,50,74,98,122};
        int s=sizeof(arr)/sizeof(arr[0]);
        for(int i=0;i<s;i++){
            for(int j=0;j<s;j++){
                alignment(QRsize,QRdata,arr[i],arr[j]);
            }
        }
    }
    else if(version==29){
        int arr[]={6,30,54,78,102,126};
        int s=sizeof(arr)/sizeof(arr[0]);
        for(int i=0;i<s;i++){
            for(int j=0;j<s;j++){
                alignment(QRsize,QRdata,arr[i],arr[j]);
            }
        }
    }
    else if(version==30){
        int arr[]={6,26,52,78,104,130};
        int s=sizeof(arr)/sizeof(arr[0]);
        for(int i=0;i<s;i++){
            for(int j=0;j<s;j++){
                alignment(QRsize,QRdata,arr[i],arr[j]);
            }
        }
    }
    else if(version==31){
        int arr[]={	6,30,56,82,108,134};
        int s=sizeof(arr)/sizeof(arr[0]);
        for(int i=0;i<s;i++){
            for(int j=0;j<s;j++){
                alignment(QRsize,QRdata,arr[i],arr[j]);
            }
        }
    }
        else if(version==32){
        int arr[]={	6,30,56,82,108,134};
        int s=sizeof(arr)/sizeof(arr[0]);
        for(int i=0;i<s;i++){
            for(int j=0;j<s;j++){
                alignment(QRsize,QRdata,arr[i],arr[j]);
            }
        }
    }
        else if(version==33){
        int arr[]={6,30,58,86,114,142};
        int s=sizeof(arr)/sizeof(arr[0]);
        for(int i=0;i<s;i++){
            for(int j=0;j<s;j++){
                alignment(QRsize,QRdata,arr[i],arr[j]);
            }
        }
    }
        else if(version==34){
        int arr[]={6,34,62,90,118,146};
        int s=sizeof(arr)/sizeof(arr[0]);
        for(int i=0;i<s;i++){
            for(int j=0;j<s;j++){
                alignment(QRsize,QRdata,arr[i],arr[j]);
            }
        }
    }
        else if(version==35){
        int arr[]={6,30,54,78,102,126,150};
        int s=sizeof(arr)/sizeof(arr[0]);
        for(int i=0;i<s;i++){
            for(int j=0;j<s;j++){
                alignment(QRsize,QRdata,arr[i],arr[j]);
            }
        }
    }
        else if(version==36){
        int arr[]={6,24,50,76,102,128,154};
        int s=sizeof(arr)/sizeof(arr[0]);
        for(int i=0;i<s;i++){
            for(int j=0;j<s;j++){
                alignment(QRsize,QRdata,arr[i],arr[j]);
            }
        }
    }
        else if(version==37){
        int arr[]={6,28,54,80,106,132,158};
        int s=sizeof(arr)/sizeof(arr[0]);
        for(int i=0;i<s;i++){
            for(int j=0;j<s;j++){
                alignment(QRsize,QRdata,arr[i],arr[j]);
            }
        }
    }
        else if(version==38){
        int arr[]={6,32,58,84,110,136,162};
        int s=sizeof(arr)/sizeof(arr[0]);
        for(int i=0;i<s;i++){
            for(int j=0;j<s;j++){
                alignment(QRsize,QRdata,arr[i],arr[j]);
            }
        }
    }
        else if(version==39){
        int arr[]={6,26,54,82,110,138,166};
        int s=sizeof(arr)/sizeof(arr[0]);
        for(int i=0;i<s;i++){
            for(int j=0;j<s;j++){
                alignment(QRsize,QRdata,arr[i],arr[j]);
            }
        }
    }
        else if(version==40){
        int arr[]={6,30,58,86,114,142,170};
        int s=sizeof(arr)/sizeof(arr[0]);
        for(int i=0;i<s;i++){
            for(int j=0;j<s;j++){
                alignment(QRsize,QRdata,arr[i],arr[j]);
            }
        }
    }

}
void alignment(int QRsize ,int QRdata[QRsize][QRsize],int x,int y){
    
    for(int i=0;i<5;i++){
       if( QRdata[i+x][y]!=0||QRdata[x][y+i]!=0||QRdata[i+x][y+4]!=0||QRdata[x+4][y+i]!=0){
        return;
       }
    }
    for(int i=0;i<3;i++){
        if( QRdata[i+x+1][y+1]!=0||QRdata[x+1][y+1+i]!=0||QRdata[i+1+x][y+1+2]!=0||QRdata[x+1+2][y+1+i]!=0){
            return;
        }
    }
    if(QRdata[x+2][y+2]!=0){
        return;
    }


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

void writedata(int QRsize ,int QRdata[QRsize][QRsize],int bit1){
    if(bit1==0){
        bit1=2;
    }
    else if(bit1==1){
        bit1=1;
    }
    else if(bit1==2){
        return;
    }
    int pos[2]={QRsize-2,QRsize-4};
    int dir = 1;
    // 1-UP , 2-DOWN.
    while(1){
        if(dir==1){
            pos[1] += 1;
            pos[0] -= 1;
            if(QRdata[pos[0]][pos[1]]==0){
                QRdata[pos[0]][pos[1]]=bit1;
                break;
            }
            pos[1] -= 1;
            if(QRdata[pos[0]][pos[1]]==0){
                QRdata[pos[0]][pos[1]]=bit1;
                break;
            }
            
        }
        else if(dir == 2){
            pos[1] += 1;
            pos[0] += 1;
            if(QRdata[pos[0]][pos[1]]==0){
                QRdata[pos[0]][pos[1]]=bit1;
                break;
            }
            pos[1] -= 1;
            if(QRdata[pos[0]][pos[1]]==0){
                QRdata[pos[0]][pos[1]]=bit1;
                break;
            }
            
        }
        //Change direction
        if(pos[1]==9){
            if(dir==1&&pos[0]==0){
                dir=2;
                pos[1] -=3;
            }
        }
        else{
            if(dir==1&&pos[0]==0){
                dir=2;
                pos[1] -= 2;
            }   
            else if(dir==2&&pos[0]==QRsize){
                dir=1;
                pos[1] -= 2;        
            }
        }
    }
}


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

void dataconverter(int QRsize ,int stringinput,int QRdata[QRsize][QRsize],char QRchar[stringinput],int i,int version){
    //byte mode
    i--;
    int bitcount=0;
    for(int i=0;i<QRsize;i++){
        for(int j=0;j<QRsize;j++){
            if(QRdata[i][j]==0){
                bitcount++;
            }
        }
    }
    int bitdata[bitcount];
    for(int i=0;i<bitcount;i++){
        bitdata[i]=2;
    }
    bitdata[0]=0,bitdata[1]=1,bitdata[2]=0,bitdata[3]=0;
    if(version<10){
        int data[8];
        binaryconverter(8,data,i);
        datawriter(8,bitcount,bitdata,data);
    }
    else{
        int data[16];
        binaryconverter(16,data,i);
        datawriter(16,bitcount,bitdata,data);
    }
    int z=0;
    while(1){
        if(QRchar[z]=='\0'){
            break;
        }
        z++;
    }
    int data[8];
    for(int i=0;i<z;i++){
        binaryconverter(8,data,QRchar[i]);
        datawriter(8,bitcount,bitdata,data);
    }
    int dat[4]={0};
    datawriter(4,bitcount,bitdata,dat);
    int Z=0;
    while(1){
        if(bitdata[Z]==2){
            break;
        }
        Z++;
    }
    Z=Z/8;
    Z=stringinput-Z;
    //Z holds no. of remaining bits
    //11101100 00010001
    int databit1[8]={1,1,1,0,1,1,0,0};
    int databit2[8]={0,0,0,1,0,0,0,1};
    for(int i=0;i<Z;i++){
        if(i%2==0){
            datawriter(8,bitcount,bitdata,databit1);
        }
        else{
            datawriter(8,bitcount,bitdata,databit2);
        }
    }



    for(int i=0;i<bitcount;i++){
        writedata(QRsize,QRdata,bitdata[i]);
    }
}

void QRinit(int QRsize ,int stringinput ,char QRchar[stringinput],int QRdata[QRsize][QRsize],int version,int i){
    fixptr(QRsize,QRdata,8);
    findptr(QRsize,QRdata,1,1);
    findptr(QRsize,QRdata,QRsize-10,1);
    findptr(QRsize,QRdata,1,QRsize-10);
    tempformatbit(QRsize,QRdata,version);
    border(QRsize,QRdata);
    genalignmark(version,QRsize,QRdata);
    int QRmask[QRsize][QRsize];
    for(int i=0;i<QRsize;i++){
        for(int j=0;j<QRsize;j++){
            QRmask[i][j]=0;
        }
    }
    for(int i=0;i<QRsize;i++){
        for(int j=0;j<QRsize;j++){
            if(QRdata[i][j]==0){
                QRmask[i][j]==1;
            }
        }
    }
    dataconverter(QRsize,stringinput,QRdata,QRchar,i,version);
    display(QRsize,QRdata,QRsize,QRsize);
    printf("\n\n");
}
