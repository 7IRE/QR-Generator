#include <stdio.h>
#include <conio.h>


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

int correctionlevel(){
    printf("\033[2J");
    printf("\033[0;0HENTER CORRECTION LEVEL(A-D FOR LEFT AND RIGHT , E FOR ENTER)");
    int pos=0;
    char direction;
    while(direction!='e'){
            direction = getch();
            if(direction=='a'){
                pos--;
            }
            else if(direction=='d'){
                pos++;
            }
            if(pos<0){
                pos=3;
            }
            else if(pos>3){
                pos=0;
            }

    if(pos==0){
        printf("\033[96m");
    }
    printf("\033[2;10HLOW           \033[2m\033[3;10HUp to 7 Percent\033[4;10Hdamage recovery");
    printf("\033[91;1m");
    if(pos==1){
        printf("\033[96m");
    }
    printf("\033[2;30HMEDIUM        \033[2m\033[3;30HUp to 15 Percent\033[4;30Hdamage recovery ");
    printf("\033[91;1m");
    if(pos==2){
        printf("\033[96m");
    }
    printf("\033[2;50HQUARTILE      \033[2m\033[3;50HUp to 25 Percent\033[4;50Hdamage recovery ");
    printf("\033[91;1m");
     
    if(pos==3){
        printf("\033[96m");
    }
    printf("\033[2;70HHIGH          \033[2m\033[3;70HUp to 30 Percent\033[4;70Hdamage recovery ");
    printf("\033[91;1m");
         
    }
    printf("\033[0m");
    return pos;
}


int main(){
    int corlvl=correctionlevel();
    int strsize,QRsize,version;
    printf("\033[5;0HENTER MESSAGE SIZE:");
    scanf("%d",&strsize);
    //VERSION AND MAX STRING SIZE
    switch (corlvl){
        case 0:
            switch(strsize){
                case 0    ... 17:   version = 1  , strsize = 17;   break;
                case 18   ... 32:   version = 2  , strsize = 32;   break;
                case 33   ... 53:   version = 3  , strsize = 53;   break;
                case 54   ... 78:   version = 4  , strsize = 78;   break;
                case 79   ... 106:  version = 5  , strsize = 106;  break;
                case 107  ... 134:  version = 6  , strsize = 134;  break;
                case 135  ... 154:  version = 7  , strsize = 154;  break;
                case 155  ... 192:  version = 8  , strsize = 192;  break;
                case 193  ... 230:  version = 9  , strsize = 230;  break;
                case 231  ... 271:  version = 10 , strsize = 271;  break;
                case 272  ... 321:  version = 11 , strsize = 321;  break;
                case 322  ... 367:  version = 12 , strsize = 367;  break;
                case 368  ... 425:  version = 13 , strsize = 425;  break;
                case 426  ... 458:  version = 14 , strsize = 458;  break;
                case 459  ... 520:  version = 15 , strsize = 520;  break;
                case 521  ... 586:  version = 16 , strsize = 586;  break;
                case 587  ... 644:  version = 17 , strsize = 644;  break;
                case 645  ... 718:  version = 18 , strsize = 718;  break;
                case 719  ... 792:  version = 19 , strsize = 792;  break;
                case 793  ... 858:  version = 20 , strsize = 858;  break;
                case 859  ... 929:  version = 21 , strsize = 929;  break;
                case 930  ... 1003: version = 22 , strsize = 1003; break;
                case 1004 ... 1091: version = 23 , strsize = 1091; break;
                case 1092 ... 1171: version = 24 , strsize = 1171; break;
                case 1172 ... 1273: version = 25 , strsize = 1273; break;
                case 1274 ... 1367: version = 26 , strsize = 1367; break;
                case 1368 ... 1465: version = 27 , strsize = 1465; break;
                case 1466 ... 1528: version = 28 , strsize = 1528; break;
                case 1529 ... 1628: version = 29 , strsize = 1628; break;
                case 1629 ... 1732: version = 30 , strsize = 1732; break;
                case 1733 ... 1840: version = 31 , strsize = 1840; break;
                case 1841 ... 1952: version = 32 , strsize = 1952; break;
                case 1953 ... 2068: version = 33 , strsize = 2068; break;
                case 2069 ... 2188: version = 34 , strsize = 2188; break;
                case 2189 ... 2303: version = 35 , strsize = 2303; break;
                case 2304 ... 2431: version = 36 , strsize = 2431; break;
                case 2432 ... 2563: version = 37 , strsize = 2563; break;
                case 2564 ... 2699: version = 38 , strsize = 2699; break;
                case 2700 ... 2809: version = 39 , strsize = 2809; break;
                case 2810 ... 2953: version = 40 , strsize = 2953; break;
            }
            break;
        case 1:
            switch(strsize){
                case 0    ... 14:   version = 1  , strsize = 14;   break;
                case 15   ... 26:   version = 2  , strsize = 26;   break;
                case 27   ... 42:   version = 3  , strsize = 42;   break;
                case 43   ... 62:   version = 4  , strsize = 62;   break;
                case 63   ... 84:   version = 5  , strsize = 84;   break;
                case 85   ... 106:  version = 6  , strsize = 106;  break;
                case 107  ... 122:  version = 7  , strsize = 122;  break;
                case 123  ... 152:  version = 8  , strsize = 152;  break;
                case 153  ... 180:  version = 9  , strsize = 180;  break;
                case 181  ... 213:  version = 10 , strsize = 213;  break;
                case 214  ... 251:  version = 11 , strsize = 251;  break;
                case 252  ... 287:  version = 12 , strsize = 287;  break;
                case 288  ... 331:  version = 13 , strsize = 331;  break;
                case 332  ... 362:  version = 14 , strsize = 362;  break;
                case 363  ... 412:  version = 15 , strsize = 412;  break;
                case 413  ... 450:  version = 16 , strsize = 450;  break;
                case 451  ... 504:  version = 17 , strsize = 504;  break;
                case 505  ... 560:  version = 18 , strsize = 560;  break;
                case 561  ... 624:  version = 19 , strsize = 624;  break;
                case 625  ... 666:  version = 20 , strsize = 666;  break;
                case 667  ... 711:  version = 21 , strsize = 711;  break;
                case 712  ... 779:  version = 22 , strsize = 779;  break;
                case 780  ... 857:  version = 23 , strsize = 857;  break;
                case 858  ... 911:  version = 24 , strsize = 911;  break;
                case 912  ... 997:  version = 25 , strsize = 997;  break;
                case 998  ... 1059: version = 26 , strsize = 1059; break;
                case 1060 ... 1125: version = 27 , strsize = 1125; break;
                case 1126 ... 1190: version = 28 , strsize = 1190; break;
                case 1191 ... 1264: version = 29 , strsize = 1264; break;
                case 1265 ... 1370: version = 30 , strsize = 1370; break;
                case 1371 ... 1452: version = 31 , strsize = 1452; break;
                case 1453 ... 1538: version = 32 , strsize = 1538; break;
                case 1539 ... 1628: version = 33 , strsize = 1628; break;
                case 1629 ... 1722: version = 34 , strsize = 1722; break;
                case 1723 ... 1809: version = 35 , strsize = 1809; break;
                case 1810 ... 1911: version = 36 , strsize = 1911; break;
                case 1912 ... 1989: version = 37 , strsize = 1989; break;
                case 1990 ... 2099: version = 38 , strsize = 2099; break;
                case 2100 ... 2212: version = 39 , strsize = 2212; break;
                case 2213 ... 2331: version = 40 , strsize = 2331; break;
            } 
            break;
        case 2:
            switch(strsize){
                case 0    ... 11:   version = 1  , strsize = 11;   break;
                case 12   ... 20:   version = 2  , strsize = 20;   break;
                case 21   ... 32:   version = 3  , strsize = 32;   break;
                case 33   ... 46:   version = 4  , strsize = 46;   break;
                case 47   ... 60:   version = 5  , strsize = 60;   break;
                case 61   ... 74:   version = 6  , strsize = 74;   break;
                case 75   ... 86:   version = 7  , strsize = 86;   break;
                case 87   ... 108:  version = 8  , strsize = 108;  break;
                case 109  ... 130:  version = 9  , strsize = 130;  break;
                case 131  ... 151:  version = 10 , strsize = 151;  break;
                case 152  ... 177:  version = 11 , strsize = 177;  break;
                case 178  ... 203:  version = 12 , strsize = 203;  break;
                case 204  ... 241:  version = 13 , strsize = 241;  break;
                case 242  ... 258:  version = 14 , strsize = 258;  break;
                case 259  ... 292:  version = 15 , strsize = 292;  break;
                case 293  ... 322:  version = 16 , strsize = 322;  break;
                case 323  ... 364:  version = 17 , strsize = 364;  break;
                case 365  ... 394:  version = 18 , strsize = 394;  break;
                case 395  ... 442:  version = 19 , strsize = 442;  break;
                case 443  ... 482:  version = 20 , strsize = 482;  break;
                case 483  ... 509:  version = 21 , strsize = 509;  break;
                case 510  ... 565:  version = 22 , strsize = 565;  break;
                case 566  ... 611:  version = 23 , strsize = 611;  break;
                case 612  ... 661:  version = 24 , strsize = 661;  break;
                case 662  ... 715:  version = 25 , strsize = 715;  break;
                case 716  ... 751:  version = 26 , strsize = 751;  break;
                case 752  ... 805:  version = 27 , strsize = 805;  break;
                case 806  ... 868:  version = 28 , strsize = 868;  break;
                case 869  ... 908:  version = 29 , strsize = 908;  break;
                case 909  ... 982:  version = 30 , strsize = 982;  break;
                case 983  ... 1030: version = 31 , strsize = 1030; break;
                case 1031 ... 1112: version = 32 , strsize = 1112; break;
                case 1113 ... 1168: version = 33 , strsize = 1168; break;
                case 1169 ... 1228: version = 34 , strsize = 1228; break;
                case 1229 ... 1283: version = 35 , strsize = 1283; break;
                case 1284 ... 1351: version = 36 , strsize = 1351; break;
                case 1352 ... 1423: version = 37 , strsize = 1423; break;
                case 1424 ... 1499: version = 38 , strsize = 1499; break;
                case 1500 ... 1579: version = 39 , strsize = 1579; break;
                case 1580 ... 1663: version = 40 , strsize = 1663; break;
            }
            break;
        case 3:
            switch(strsize){
                case 0    ... 7:    version = 1  , strsize = 7;    break;
                case 8    ... 14:   version = 2  , strsize = 14;   break;
                case 15   ... 24:   version = 3  , strsize = 24;   break;
                case 25   ... 34:   version = 4  , strsize = 34;   break;
                case 35   ... 44:   version = 5  , strsize = 44;   break;
                case 45   ... 58:   version = 6  , strsize = 58;   break;
                case 59   ... 64:   version = 7  , strsize = 64;   break;
                case 65   ... 84:   version = 8  , strsize = 84;   break;
                case 85   ... 98:   version = 9  , strsize = 98;   break;
                case 99   ... 119:  version = 10 , strsize = 119;  break;
                case 120  ... 137:  version = 11 , strsize = 137;  break;
                case 138  ... 155:  version = 12 , strsize = 155;  break;
                case 156  ... 177:  version = 13 , strsize = 177;  break;
                case 178  ... 194:  version = 14 , strsize = 194;  break;
                case 195  ... 220:  version = 15 , strsize = 220;  break;
                case 221  ... 250:  version = 16 , strsize = 250;  break;
                case 251  ... 280:  version = 17 , strsize = 280;  break;
                case 281  ... 310:  version = 18 , strsize = 310;  break;
                case 311  ... 338:  version = 19 , strsize = 338;  break;
                case 339  ... 382:  version = 20 , strsize = 382;  break;
                case 383  ... 403:  version = 21 , strsize = 403;  break;
                case 404  ... 439:  version = 22 , strsize = 439;  break;
                case 440  ... 461:  version = 23 , strsize = 461;  break;
                case 462  ... 511:  version = 24 , strsize = 511;  break;
                case 512  ... 535:  version = 25 , strsize = 535;  break;
                case 536  ... 593:  version = 26 , strsize = 593;  break;
                case 594  ... 625:  version = 27 , strsize = 625;  break;
                case 626  ... 658:  version = 28 , strsize = 658;  break;
                case 659  ... 698:  version = 29 , strsize = 698;  break;
                case 699  ... 742:  version = 30 , strsize = 742;  break;
                case 743  ... 790:  version = 31 , strsize = 790;  break;
                case 791  ... 842:  version = 32 , strsize = 842;  break;
                case 843  ... 898:  version = 33 , strsize = 898;  break;
                case 899  ... 958:  version = 34 , strsize = 958;  break;
                case 959  ... 983: version = 35 , strsize = 983;   break;
                case 984  ... 1051: version = 36 , strsize = 1051; break;
                case 1052 ... 1093: version = 37 , strsize = 1093; break;
                case 1094 ... 1139: version = 38 , strsize = 1139; break;
                case 1140 ... 1219: version = 39 , strsize = 1219; break;
                case 1220 ... 1273: version = 40 , strsize = 1273; break;
            }
            break;
    }
    //QR SIZE
    QRsize=21;
    if(version==1){
    }
    else{
        for(int i=1;i<version;i++){
            QRsize += 4;
        }
    }

    char QRchar[strsize+1];
    for(int i=0;i<=strsize;i++){
        QRchar[i]=' ';
    }
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
            QRdata[i][j]=2;
        }
    }
    //Timing pattern
    int a=1;
    for(int i=0;i<QRsize;i++){
        QRdata[i][6]=a;
        QRdata[6][i]=a;
        if(a==1){
            a=0;
        }
        else if(a==0){
            a=1;
        }
    } 
    //Finder patterns
    for(int i=0;i<7;i++){
        //INNER SQUARE
        QRdata[2][i]=1;
        QRdata[i][2]=1;
        QRdata[i][4]=1;
        QRdata[4][i]=1;

        QRdata[QRsize-3][i]=1;
        QRdata[QRsize-5][i]=1;
        QRdata[QRsize-7+i][2]=1;
        QRdata[QRsize-7+i][4]=1;

        QRdata[2][QRsize-7+i]=1;
        QRdata[4][QRsize-7+i]=1;
        QRdata[i][QRsize-3]=1;
        QRdata[i][QRsize-5]=1;  
    }
    for(int i=0;i<7;i++){
        //MIDDLE SQUARE
        QRdata[1][i]=0;
        QRdata[i][1]=0;
        QRdata[5][i]=0;
        QRdata[i][5]=0;

        QRdata[1][QRsize-7+i]=0;
        QRdata[5][QRsize-7+i]=0;
        QRdata[i][QRsize-6]=0;
        QRdata[i][QRsize-2]=0;

        QRdata[QRsize-7+i][1]=0;
        QRdata[QRsize-7+i][5]=0;
        QRdata[QRsize-2][i]=0;
        QRdata[QRsize-6][i]=0;

        QRdata[i][7]=0;
        QRdata[i][QRsize-8]=0;
        QRdata[QRsize-7+i][7]=0;
        
        QRdata[7][i]=0;
        QRdata[QRsize-8][i]=0;
        QRdata[7][QRsize-7+i]=0;


    }

    QRdata[7][7]=0;
    QRdata[QRsize-8][7]=0;
    QRdata[7][QRsize-8]=0;
    QRdata[3][3]=1;
    QRdata[3][QRsize-4]=1;
    QRdata[QRsize-4][3]=1;


    for(int i=0;i<7;i++){
        //OUTER SQUARE
        QRdata[0][i]=1;
        QRdata[i][0]=1;
        QRdata[i][6]=1;
        QRdata[6][i]=1;
        
        QRdata[i][QRsize-1]=1;
        QRdata[i][QRsize-7]=1;
        QRdata[0][QRsize-7+i]=1;
        QRdata[6][QRsize-7+i]=1;


        QRdata[QRsize-7][i]=1;
        QRdata[QRsize-1][i]=1;
        QRdata[QRsize-7+i][0]=1;
        QRdata[QRsize-7+i][6]=1;
    }
    
    display(QRsize,QRdata,QRsize,QRsize);
    printf("\033[%d;%dH",QRsize+10,QRsize+4);
    printf("\n\n");
    return 0;
}