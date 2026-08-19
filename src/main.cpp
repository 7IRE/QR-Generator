#include <iostream>
#include "QR_Generator.hpp"


int correctionlevel(){
    int pos = 0 ;
    std::cout<<"Low      : Upto 7  Percent Damage Recovery \n";
    std::cout<<"MEDIUM   : Upto 15 Percent Damage Recovery \n";
    std::cout<<"QUARTILE : Upto 25 Percent Damage Recovery \n";
    std::cout<<"HIGH     : Upto 30 Percent Damage Recovery \n";
    std::cout<<"Enter Error Correction Level : ";
    std::cin>>pos;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if(pos<0 || pos>3){pos=0;}
    return pos;
}



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

void render(std::vector <std::vector<int>> arr){
    int QRsize = arr.size();
    int row=QRsize,column=QRsize;
    printf("\033[2J");
    for(int i=0;i<QRsize+4;i++){
        block(i,0,0);
        block(0,i,0);
        block(i,QRsize+3,0);
        block(QRsize+3,i,0);
    }
    for(int i=1;i<QRsize+3;i++){
        block(i,1,0);
        block(1,i,0);
        block(i,QRsize+2,0);
        block(QRsize+2,i,0);
    }
    for(int i=0;i<row;i++){
        for(int j=0;j<column;j++){
            block(i+2,j+2,(int)arr[i][j]);
        }
    }
    
}

int main(){
    std::string QRchar;
    int corlvl=correctionlevel();
    std::cout<<"Enter Data To Encode :";
    std::getline(std::cin, QRchar);

    QR_Generator qr;
    std::vector<std::vector<int>> QR = qr.GenerateQR(QRchar,corlvl);
    render(QR);
    return 0;
}