#include <stdio.h>
#include <conio.h>
#include "renderer.h"
#include "encoder.h"

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
    if(corlvl==0){
        if(strsize<=17){
            version=1;
            strsize=17;
        }
        else if(strsize<=32){
            version=2;
            strsize=32;
        }
        else if(strsize<=53){
            version=3;
            strsize=53;
        }
        else if(strsize<=78){
            version=4;
            strsize=78;
        }
        else if(strsize<=106){
            version=5;
            strsize=106;
        }
        else if(strsize<=134){
            version=6;
            strsize=134;
        }
        else if(strsize<=154){
            version=7;
            strsize=154;
        }
        else if(strsize<=192){
            version=8;
            strsize=192;
        }
        else if(strsize<=230){
            version=9;
            strsize=230;
        }
        else if(strsize<=271){
            version=10;
            strsize=271;
        }
        else if(strsize<=321){
            version=11;
            strsize=321;
        }
        else if(strsize<=367){
            version=12;
            strsize=367;
        }
        else if(strsize<=425){
            version=13;
            strsize=425;
        }
        else if(strsize<=458){
            version=14;
            strsize=458;
        }
        else if(strsize<=520){
            version=15;
            strsize=520;
        }
        else if(strsize<=586){
            version=16;
            strsize=586;
        }
        else if(strsize<=644){
            version=17;
            strsize=644;
        }
        else if(strsize<=718){
            version=18;
            strsize=718;
        }
        else if(strsize<=792){
            version=19;
            strsize=792;
        }
        else if(strsize<=858){
            version=20;
            strsize=858;
        }
        else if(strsize<=929){
            version=21;
            strsize=929;
        }
        else if(strsize<=1003){
            version=22;
            strsize=1003;
        }
        else if(strsize<=1091){
            version=23;
            strsize=1091;
        }
        else if(strsize<=1171){
            version=24;
            strsize=1171;
        }
        else if(strsize<=1273){
            version=25;
            strsize=1273;
        }
        else if(strsize<=1367){
            version=26;
            strsize=1367;
        }
        else if(strsize<=1465){
            version=27;
            strsize=1465;
        }
        else if(strsize<=1528){
            version=28;
            strsize=1528;
        }
        else if(strsize<=1628){
            version=29;
            strsize=1628;
        }
        else if(strsize<=1732){
            version=30;
            strsize=1732;
        }
        else if(strsize<=1840){
            version=31;
            strsize=1840;
        }
        else if(strsize<=1952){
            version=32;
            strsize=1952;
        }
        else if(strsize<=2068){
            version=33;
            strsize=2068;
        }
        else if(strsize<=2188){
            version=34;
            strsize=2188;
        }
        else if(strsize<=2303){
            version=35;
            strsize=2303;
        }
        else if(strsize<=2431){
            version=36;
            strsize=2431;
        }
        else if(strsize<=2563){
            version=37;
            strsize=2563;
        }
        else if(strsize<=2699){
            version=38;
            strsize=2699;
        }
        else if(strsize<=2809){
            version=39;
            strsize=2809;
        }
        else if(strsize<=2953){
            version=40;
            strsize=2953;
        }
    }
    else if(corlvl==1){
        if(strsize<=14){
            version=1;
            strsize=14;
        }
        else if(strsize<=26){
            version=2;
            strsize=26;
        }
        else if(strsize<=42){
            version=3;
            strsize=42;
        }
        else if(strsize<=62){
            version=4;
            strsize=62;
        }
        else if(strsize<=84){
            version=5;
            strsize=84;
        }
        else if(strsize<=106){
            version=6;
            strsize=106;
        }
        else if(strsize<=122){
            version=7;
            strsize=122;
        }
        else if(strsize<=152){
            version=8;
            strsize=152;
        }
        else if(strsize<=180){
            version=9;
            strsize=180;
        }
        else if(strsize<=213){
            version=10;
            strsize=213;
        }
        else if(strsize<=251){
            version=11;
            strsize=251;
        }
        else if(strsize<=287){
            version=12;
            strsize=287;
        }
        else if(strsize<=331){
            version=13;
            strsize=331;
        }
        else if(strsize<=362){
            version=14;
            strsize=362;
        }
        else if(strsize<=412){
            version=15;
            strsize=412;
        }
        else if(strsize<=450){
            version=16;
            strsize=450;
        }
        else if(strsize<=504){
            version=17;
            strsize=504;
        }
        else if(strsize<=560){
            version=18;
            strsize=560;
        }
        else if(strsize<=624){
            version=19;
            strsize=624;
        }
        else if(strsize<=666){
            version=20;
            strsize=666;
        }
        else if(strsize<=711){
            version=21;
            strsize=711;
        }
        else if(strsize<=779){
            version=22;
            strsize=779;
        }
        else if(strsize<=857){
            version=23;
            strsize=857;
        }
        else if(strsize<=911){
            version=24;
            strsize=911;
        }
        else if(strsize<=997){
            version=25;
            strsize=997;
        }
        else if(strsize<=1059){
            version=26;
            strsize=1059;
        }
        else if(strsize<=1125){
            version=27;
            strsize=1125;
        }
        else if(strsize<=1190){
            version=28;
            strsize=1190;
        }
        else if(strsize<=1264){
            version=29;
            strsize=1264;
        }
        else if(strsize<=1370){
            version=30;
            strsize=1370;
        }
        else if(strsize<=1452){
            version=31;
            strsize=1452;
        }
        else if(strsize<=1538){
            version=32;
            strsize=1538;
        }
        else if(strsize<=1628){
            version=33;
            strsize=1628;
        }
        else if(strsize<=1722){
            version=34;
            strsize=1722;
        }
        else if(strsize<=1809){
            version=35;
            strsize=1809;
        }
        else if(strsize<=1911){
            version=36;
            strsize=1911;
        }
        else if(strsize<=1989){
            version=37;
            strsize=1989;
        }
        else if(strsize<=2099){
            version=38;
            strsize=2099;
        }
        else if(strsize<=2212){
            version=39;
            strsize=2212;
        }
        else if(strsize<=2331){
            version=40;
            strsize=2331;
        }
    }
    else if(corlvl==2){
        if(strsize<=11){
            version=1;
            strsize=11;
        }
        else if(strsize<=20){
            version=2;
            strsize=20;
        }
        else if(strsize<=32){
            version=3;
            strsize=32;
        }
        else if(strsize<=46){
            version=4;
            strsize=46;
        }
        else if(strsize<=60){
            version=5;
            strsize=60;
        }
        else if(strsize<=74){
            version=6;
            strsize=74;
        }
        else if(strsize<=86){
            version=7;
            strsize=86;
        }
        else if(strsize<=108){
            version=8;
            strsize=108;
        }
        else if(strsize<=130){
            version=9;
            strsize=130;
        }
        else if(strsize<=151){
            version=10;
            strsize=151;
        }
        else if(strsize<=177){
            version=11;
            strsize=177;
        }
        else if(strsize<=203){
            version=12;
            strsize=203;
        }
        else if(strsize<=241){
            version=13;
            strsize=241;
        }
        else if(strsize<=258){
            version=14;
            strsize=258;
        }
        else if(strsize<=292){
            version=15;
            strsize=292;
        }
        else if(strsize<=322){
            version=16;
            strsize=322;
        }
        else if(strsize<=364){
            version=17;
            strsize=364;
        }
        else if(strsize<=394){
            version=18;
            strsize=394;
        }
        else if(strsize<=442){
            version=19;
            strsize=442;
        }
        else if(strsize<=482){
            version=20;
            strsize=482;
        }
        else if(strsize<=509){
            version=21;
            strsize=509;
        }
        else if(strsize<=565){
            version=22;
            strsize=565;
        }
        else if(strsize<=611){
            version=23;
            strsize=611;
        }
        else if(strsize<=661){
            version=24;
            strsize=661;
        }
        else if(strsize<=715){
            version=25;
            strsize=715;
        }
        else if(strsize<=751){
            version=26;
            strsize=751;
        }
        else if(strsize<=805){
            version=27;
            strsize=805;
        }
        else if(strsize<=868){
            version=28;
            strsize=868;
        }
        else if(strsize<=908){
            version=29;
            strsize=908;
        }
        else if(strsize<=982){
            version=30;
            strsize=982;
        }
        else if(strsize<=1030){
            version=31;
            strsize=1030;
        }
        else if(strsize<=1112){
            version=32;
            strsize=1112;
        }
        else if(strsize<=1168){
            version=33;
            strsize=1168;
        }
        else if(strsize<=1228){
            version=34;
            strsize=1228;
        }
        else if(strsize<=1283){
            version=35;
            strsize=1283;
        }
        else if(strsize<=1351){
            version=36;
            strsize=1351;
        }
        else if(strsize<=1423){
            version=37;
            strsize=1423;
        }
        else if(strsize<=1499){
            version=38;
            strsize=1499;
        }
        else if(strsize<=1579){
            version=39;
            strsize=1579;
        }
        else if(strsize<=1663){
            version=40;
            strsize=1663;
        }
    }
    else if(corlvl==3){
        if(strsize<=7){
            version=1;
            strsize=7;
        }
        else if(strsize<=14){
            version=2;
            strsize=14;
        }
        else if(strsize<=24){
            version=3;
            strsize=24;
        }
        else if(strsize<=34){
            version=4;
            strsize=34;
        }
        else if(strsize<=44){
            version=5;
            strsize=44;
        }
        else if(strsize<=58){
            version=6;
            strsize=58;
        }
        else if(strsize<=64){
            version=7;
            strsize=64;
        }
        else if(strsize<=84){
            version=8;
            strsize=84;
        }
        else if(strsize<=98){
            version=9;
            strsize=98;
        }
        else if(strsize<=119){
            version=10;
            strsize=119;
        }
        else if(strsize<=137){
            version=11;
            strsize=137;
        }
        else if(strsize<=155){
            version=12;
            strsize=155;
        }
        else if(strsize<=177){
            version=13;
            strsize=177;
        }
        else if(strsize<=194){
            version=14;
            strsize=194;
        }
        else if(strsize<=220){
            version=15;
            strsize=220;
        }
        else if(strsize<=250){
            version=16;
            strsize=250;
        }
        else if(strsize<=280){
            version=17;
            strsize=280;
        }
        else if(strsize<=310){
            version=18;
            strsize=310;
        }
        else if(strsize<=338){
            version=19;
            strsize=338;
        }
        else if(strsize<=382){
            version=20;
            strsize=382;
        }
        else if(strsize<=403){
            version=21;
            strsize=403;
        }
        else if(strsize<=439){
            version=22;
            strsize=439;
        }
        else if(strsize<=461){
            version=23;
            strsize=461;
        }
        else if(strsize<=511){
            version=24;
            strsize=511;
        }
        else if(strsize<=535){
            version=25;
            strsize=535;
        }
        else if(strsize<=593){
            version=26;
            strsize=593;
        }
        else if(strsize<=625){
            version=27;
            strsize=625;
        }
        else if(strsize<=658){
            version=28;
            strsize=658;
        }
        else if(strsize<=698){
            version=29;
            strsize=698;
        }
        else if(strsize<=742){
            version=30;
            strsize=742;
        }
        else if(strsize<=790){
            version=31;
            strsize=790;
        }
        else if(strsize<=842){
            version=32;
            strsize=842;
        }
        else if(strsize<=898){
            version=33;
            strsize=898;
        }
        else if(strsize<=958){
            version=34;
            strsize=958;
        }
        else if(strsize<=983){
            version=35;
            strsize=983;
        }
        else if(strsize<=1051){
            version=36;
            strsize=1051;
        }
        else if(strsize<=1093){
            version=37;
            strsize=1093;
        }
        else if(strsize<=1139){
            version=38;
            strsize=1139;
        }
        else if(strsize<=1219){
            version=39;
            strsize=1219;
        }
        else if(strsize<=1273){
            version=40;
            strsize=1273;
        }
    }
    QRsize=25;
    if(version==1){
    }
    else{
        for(int i=1;i<version;i++){
            QRsize += 4;
        }
    }
    //VERSION , STRSIZE , CORRECTION LEVEL , QRSIZE
    initalize(version,strsize,corlvl,QRsize);
    return 0;
}