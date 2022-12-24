#include "../inc/rule.h"
#include "../inc/typedef.h"
#include "../inc/watcher.h"

#define ROW 9
#define COL 9

int x=0,y=0;
char bd[ROW][COL];
int status = 0;
int count = 0, maxcount = 0;
int top1=-1,top2=-1;
char chessEat1[40];
char chessEat2[40];
int FROMREADTOPLAY=0;
int END=0;
int Print_eaten_chess=0;

/* Detect if the chess can be promoted */
void promoDetect(int iX,int iY, int nX, int nY){
    char I;
    char *c = &bd[iY][iX];
    int rightInput=0;
    if(count%2==0){
        if(nY<6 && iY<6)
            return;
        while(rightInput!=1){
            FLAG = PROMOTECHOOSE;
            timer();
            scanf("%c",&I);
            getchar();
            switch(I){
                case 'y':
                case 'Y':
                    switch(*c){
                        case 'C': //角 -> 馬
                            *c='H';
                            break;
                        case 'F': //飛 -> 龍
                            *c='D';
                            break;
                        case 'Y': //銀 -> 全
                            *c='A';
                            break; 
                        case 'S': //香 -> 杏
                            *c='X';
                            break;
                        case 'G': //桂 -> 圭
                            *c='P';
                            break;
                        case 'B': //步 -> と
                            *c='K';
                            break;
                    }
                    rightInput=1;
                    break;
                case 'n':
                case 'N':
                    rightInput=1;
                    break;
                default:
                    printf("請輸入Y/N！\n");
                    sleep(1);
                    break;
            }
        }
        
    }
    else{
        if(nY>2 && iY>2)
            return;
        while(rightInput!=1){
            FLAG = PROMOTECHOOSE;
            timer();
            scanf("%c",&I);
            getchar();
            switch(I){
                case 'y':
                case 'Y':
                    switch(*c){
                        case 'c': //角 -> 馬
                            *c='h';
                            break;
                        case 'f': //飛 -> 龍
                            *c='d';
                            break;
                        case 'y': //銀 -> 全
                            *c='a';
                            break; 
                        case 's': //香 -> 杏
                            *c='x';
                            break;
                        case 'g': //桂 -> 圭
                            *c='p';
                            break;
                        case 'b': //步 -> と
                            *c='k';
                            break;
                    }
                    rightInput=1;
                    break;
                case 'n':
                case 'N':
                    rightInput=1;
                    break;
                default:
                    printf("請輸入Y/N！\n");
                    sleep(1);
                    break;
            }
        }
    }
}
/* Drop the chess in hand */
int drop(){
    int i;
    int newX=0,newY=0;
    int dropNum=0;
    char *c;
    scanf("%d",&dropNum);
    getchar();
    if(dropNum<=0){
        printf("選錯了啦!\n");
        sleep(1);
        return 0;
    }
    dropNum-=1;
    if((count%2==0 && dropNum>top1) || (count%2==1 && dropNum>top2)){
        printf("駒台上沒有這個位子喔!\n");
        sleep(1);
        return 0;
    }
    FLAG = DROPPLACE;
    timer();
    scanf("%d",&newX);
    getchar();
    if((newX/10)==0)
        scanf("%d",&newY);
    else{
        newY=newX%10;
        newX=newX/10;
    }
    newX=9-newX;
    newY=newY-1;
    c=&bd[newY][newX];
    if((*c)!='t'){
        printf("必須選空的地方！\n");
        sleep(1);
        return 0;
    }
    if(count%2==0){
        // *c=(char)(chessEat1[dropNum]-32);
        switch(chessEat1[dropNum]){
            case 'h': //馬u -> 角
                *c='U';
                break;
            case 'd': //龍l -> 飛
                *c='L';
                break;
            case 'a': //全n -> 銀
                *c='N';
                break; 
            case 'x': //杏z -> 香
                *c='Z';
                break;
            case 'p': //圭i -> 桂
                *c='I';
                break;
            case 'k': //とq -> 步
                *c='Q';
                break;
            default:
                *c=(char)(chessEat1[dropNum]-32);
                break;
        }
        addMatch(-2,dropNum,newX,newY,*c,'t');
        for(i=dropNum;i<top1;i++){
            chessEat1[i]=chessEat1[i+1];
        }
        chessEat1[top1]='t';
        top1--;
    }
    else{
        // *c=(char)(chessEat2[dropNum]+32);
        switch(chessEat2[dropNum]){
            case 'H': //馬 -> 角
                *c='u';
                break;
            case 'D': //龍 -> 飛
                *c='l';
                break;
            case 'A': //全 -> 銀
                *c='n';
                break; 
            case 'X': //杏 -> 香
                *c='z';
                break;
            case 'P': //圭 -> 桂
                *c='i';
                break;
            case 'K': //と -> 步
                *c='q';
                break;
            default:
                *c=(char)(chessEat2[dropNum]+32);
                break;
        }
        addMatch(-2,dropNum,newX,newY,*c,'t');
        for(i=dropNum;i<top2;i++){
            chessEat2[i]=chessEat2[i+1];
        }
        chessEat2[top2]='t';
        top2--;
    }
    return 1;
    
}
/* Determine if the chess eating is available*/
int Side(int x,int y){
    char chess=bd[y][x];
    if(count%2==0){
        switch(chess){
            case 'b':
            case 'g':
            case 'y':
            case 'f':
            case 'c':
            case 's':
            case 'j':
            case 'w':
            case 't':
            case 'd':
            case 'h':
            case 'k':
            case 'a':
            case 'x':
            case 'p':
            case 'i':
            case 'q':
            case 'n':
            case 'l':
            case 'u':
                return 1;
                break;
            case 'B':
            case 'G':
            case 'Y':
            case 'F':
            case 'C':
            case 'S':
            case 'J':
            case 'W':
            case 'D':
            case 'H':
            case 'K':
            case 'A':
            case 'X':
            case 'P':
            case 'I':
            case 'Q':
            case 'N':
            case 'L':
            case 'U':
                return 0;
                break;                        
        }
    }
    else if(count%2==1){
        switch(chess){
            case 'b':
            case 'g':
            case 'y':
            case 'f':
            case 'c':
            case 's':
            case 'j':
            case 'w':
            case 'k':
            case 'a':
            case 'x':
            case 'p':
            case 'i':
            case 'q':
            case 'n':
            case 'l':
            case 'u':
                return 0;
                break;
            case 'B':
            case 'G':
            case 'Y':
            case 'F':
            case 'C':
            case 'S':
            case 'J':
            case 'W':
            case 't':
            case 'D':
            case 'H':
            case 'A':
            case 'X':
            case 'P':
            case 'K':
            case 'I':
            case 'Q':
            case 'N':
            case 'L':
            case 'U':
                return 1;
                break;                               
        }
    }
    else
        return 0;
}
/* To move the chess */
void chessMove(int iX,int iY, int nX, int nY, char cM, char cE){
    int i;
    if(iX==-2){ // The DROP situation
        bd[nY][nX]=current->chessMoved;
        if(count%2==0){
            for(i=iY;i<top1;i++){ // iY now is the dropNum(the number of chess that player wants to drop)
                chessEat1[i]=chessEat1[i+1];
            }
            chessEat1[top1]='t';
            top1--;
        }
        else{
            for(i=iY;i<top2;i++){ 
                chessEat2[i]=chessEat2[i+1];
            }
            chessEat2[top2]='t';
            top2--;
        }
        count++;
        return;
    }
    if(count%2==0 && cE!='t'){
        top1++;
        chessEat1[top1]=cE;
    }
    else if(count%2==1 && cE!='t'){
        top2++;
        chessEat2[top2]=cE;
    }
    bd[nY][nX]=cM;
    bd[iY][iX]='t';
    count++;
    return;
}
/* To make the chess "go backward" */
void chessBack(int iX,int iY, int nX, int nY, char cM, char cE){
    int i;
    if(iX==-2){ // The DROP situation
        if(count%2==0){
            top1++;
            for(i=top1;i>=iY;i--){ // iY now is the dropNum(the number of chess that player wants to drop)
                chessEat1[i]=chessEat1[i-1];
            }
            changeChess(&cM);
            chessEat1[iY]=cM+32;
            bd[nY][nX]='t';
        }
        else{
            top2++;
            for(i=top2;i>=iY;i--){ // iY now is the dropNum(the number of chess that player wants to drop)
                chessEat2[i]=chessEat2[i-1];
            }
            changeChess(&cM);
            chessEat2[iY]=cM-32;
            bd[nY][nX]='t';
        }
        return;
    }
    bd[iY][iX]=cM;
    bd[nY][nX]=cE;
    if(chessEat1[top1]==cE){
        chessEat1[top1]='t';
        top1--;
    }
    else if(chessEat2[top2]==cE){
        chessEat2[top2]='t';
        top2--;
    }
    return;
}
/* Change the chess that is promoted and being eaten*/
// void changeChessE(char *c){
//     switch(*c){
//         case 'H': //馬 -> 角
//             *c = 'C';
//             break;
//         case 'D': //龍 -> 飛
//             *c = 'F';
//             break;
//         case 'A': //全 -> 銀
//             *c = 'Y';
//             break;
//         case 'X': //杏 -> 香
//             *c = 'S';
//             break;
//         case 'P': //圭 -> 桂
//             *c = 'G';
//             break;
//         case 'K': //と -> 步
//             *c = 'B';
//             break;
//         case 'h':
//             *c = 'c';
//             break;
//         case 'd':
//             *c = 'f';
//             break;
//         case 'a':
//             *c = 'y';
//             break;
//         case 'x':
//             *c = 's';
//             break;
//         case 'p':
//             *c = 'g';
//             break;
//         case 'k':
//             *c = 'b';
//             break;
//     }
// }
/* Change the chess that already promoted and being dropped*/
void changeChess(char *c){
    switch(*c){
        case 'U': //U -> 馬
            *c = 'H';
            break;
        case 'L': //L -> 龍
            *c = 'D';
            break;
        case 'N': //N -> 全
            *c = 'A';
            break;
        case 'Z': //Z -> 杏
            *c = 'X';
            break;
        case 'I': //I -> 圭
            *c = 'P';
            break;
        case 'Q': //Q -> と
            *c = 'K';
            break;
        case 'u':
            *c = 'h';
            break;
        case 'l':
            *c = 'd';
            break;
        case 'n':
            *c = 'a';
            break;
        case 'z':
            *c = 'x';
            break;
        case 'i':
            *c = 'p';
            break;
        case 'q':
            *c = 'k';
            break;
    }   
}
/* Check if the winning condition is satisfied */
int winlose(){
    if(count%2==1){
        if(chessEat1[top1]=='w')
            return 1;
        else
            return 0;
    }
    else{
        if(chessEat2[top2]=='W')
            return 2;
        else
            return 0;
    }  
}
/* Shogi rule check */
int moveCheck(int iX,int iY, int nX, int nY){
    int i,j,chessNum=0;
    switch(bd[iY][iX]){
        case 'b': // Lower "步"
        case 'q':
            if(nX==iX && iY-nY == 1){
                return 1;
            }
            else{
                return 0;
            }
            break;
        case 'B': // Upper "步"
        case 'Q':
            if(nX==iX && nY-iY == 1){
                return 1;
            }
            else{
                return 0;
            }
            break;
        case 's': // Lower "香車"
        case 'z':
            if(nX==iX && (nY < iY)){
                chessNum=0;
                for(i=iY-1;i>nY;i--){
                    if(bd[i][iX]!='t')
                        chessNum++;
                }
                if(chessNum>0)
                    return 0;
                else
                    if(Side(nX,nY))
                        return 1;
                    else 
                        return 0;
            }
            else
                return 0;
            break;
        case 'S': // Upper "香車"
        case 'Z':
            if(nX==iX && (nY > iY)){
                chessNum=0;
                for(i=iY+1;i<nY;i++){
                    if(bd[i][iX]!='t')
                        chessNum++;
                }
                if(chessNum>0)
                    return 0;
                else
                    if(Side(nX,nY))
                        return 1;
                    else 
                        return 0;
            }
            else
                return 0;
            break;
        case 'f': // 飛車
        case 'F':
        case 'l':
        case 'L': 
            if((nX==iX)&&(nY!=iY)){
                chessNum=0;
                /* Choose the vertical direction(Up/Down) */
                if(nY>iY){ // Down
                    for(i=iY+1;i<nY;i++){ // 
                        if(bd[i][iX]!='t')
                            chessNum++;
                    }
                }
                else{ // Up
                    for(i=iY-1;i>nY;i--){
                        if(bd[i][iX]!='t')
                            chessNum++;
                    }
                }
                if(chessNum>0)
                    return 0;
                else
                    if(Side(nX,nY))
                        return 1;
                    else 
                        return 0;
            }
            else if ((nX!=iX)&&(nY==iY)){
                chessNum=0;
                /* Choose the horizontal direction(Left/Right) */
                if(nX>iX){ // Right
                    for(i=iX+1;i<nX;i++){
                        if(bd[iY][i]!='t')
                            chessNum++;
                    }
                }
                else{ // Left
                    for(i=iX-1;i>nX;i--){
                        if(bd[iY][i]!='t')
                            chessNum++;
                    }
                }
                if(chessNum>0)
                    return 0;
                else
                    if(Side(nX,nY))
                        return 1;
                    else 
                        return 0;
            }
            break;
        case 'g': // Lower "桂馬"
        case 'i':
            if(iY-nY==2){               
                if(abs(nX-iX)==1){
                    if(Side(nX,nY))
                        return 1;
                    else
                        return 0;
                }
                else
                    return 0;
            }
            else
                return 0;
            break;
        case 'G': // Upper "桂馬"
        case 'I':
            if(nY-iY==2){
                if(abs(nX-iX)==1){
                    if(Side(nX,nY))
                        return 1;
                    else
                        return 0;
                }
                else
                    return 0;
            }
            else
                return 0;
            break;
        case 'j': // Lower "金將"
        case 'k': // Lower "金"
        case 'p': // Lower "と"
        case 'a': // Lower '全"
        case 'x': // Lower "杏"
            if(abs(nY-iY)==1 || abs(nX-iX)==1){
                if(nY==iY+1 && abs(nX-iX)==1)
                    return 0;
                else if(Side(nX,nY))
                    return 1;
                else
                    return 0;
            }
            else
                return 0;
            break;
        case 'J': // Upper "金將"
        case 'K': // Upper "と"
        case 'P': // Upper '圭"
        case 'A': // Upper "全"
        case 'X': // Upper "杏"
            if(abs(nY-iY)==1 || abs(nX-iX)==1){
                if(nY==iY-1 && abs(nX-iX)==1)
                    return 0;
                else if(Side(nX,nY))
                    return 1;
                else
                    return 0;
            }
            else
                return 0;
            break;
        case 'w': // 王將
        case 'W':
            if(abs(nY-iY)<2 && abs(nX-iX)<2){
                if(Side(nX,nY))
                    return 1;
                else
                    return 0;
            }
            break;
        case 'y': // Lower "銀將"
        case 'n':
            if(abs(nY-iY)<2 && abs(nX-iX)<2){
                if(iX==nX && nY==iY+1)
                    return 0;
                else if(nY==iY)
                    return 0;
                else{
                    if(Side(nX,nY))
                        return 1;
                    else return 0;
                }
            }
            break;
        case 'Y': // Upper "銀將"
        case 'N':
            if(abs(nY-iY)<2 && abs(nX-iX)<2){
                if(iX==nX && nY==iY-1)
                    return 0;
                else if(nY==iY)
                    return 0;
                else{
                    if(Side(nX,nY))
                        return 1;
                    else return 0;
                }
            }
            break;
        case 'c': // "角行"
        case 'C':
        case 'u':
        case 'U':
            if(abs(nX-iX)==abs(nY-iY)){
                chessNum=0;
                // Choose the direction
                if(nX>iX){ // Right
                    if(nY>iY){ // Down-Right
                        for(i=iY+1,j=iX+1;i<nY;i++,j++){
                            if(bd[i][j]!='t')
                                chessNum++;
                        }
                    }
                    else{ // Up-Right
                        for(i=iY-1,j=iX+1;i>nY;i--,j++){
                            if(bd[i][j]!='t')
                                chessNum++;
                        }
                    }
                }
                else{ // Left
                    if(nY>iY){ // Down-Left
                        for(i=iY+1,j=iX-1;i<nY;i++,j--){
                            if(bd[i][j]!='t')
                                chessNum++;
                        }
                    }
                    else{ // Up-Left
                        for(i=iY-1,j=iX-1;i>nY;i--,j--){
                            if(bd[i][j]!='t')
                                chessNum++;
                        }
                    }
                }
                // Find if there's any block
                if(chessNum>0)
                    return 0;
                else
                    if(Side(nX,nY))
                        return 1;
                    else
                        return 0; 
            }
            else
                return 0;
            break;
        case 'd': //龍
        case 'D':
            if((nX==iX)&&(nY!=iY)){
                chessNum=0;
                /* Choose the vertical direction(Up/Down) */
                if(nY>iY){ // Down
                    for(i=iY+1;i<nY;i++){ // 
                        if(bd[i][iX]!='t')
                            chessNum++;
                    }
                }
                else{ // Up
                    for(i=iY-1;i>nY;i--){
                        if(bd[i][iX]!='t')
                            chessNum++;
                    }
                }
                if(chessNum>0)
                    return 0;
                else
                    if(Side(nX,nY))
                        return 1;
                    else 
                        return 0;
            }
            else if ((nX!=iX)&&(nY==iY)){
                chessNum=0;
                /* Choose the horizontal direction(Left/Right) */
                if(nX>iX){ // Right
                    for(i=iX+1;i<nX;i++){
                        if(bd[iY][i]!='t')
                            chessNum++;
                    }
                }
                else{ // Left
                    for(i=iX-1;i>nX;i--){
                        if(bd[iY][i]!='t')
                            chessNum++;
                    }
                }
                if(chessNum>0)
                    return 0;
                else
                    if(Side(nX,nY))
                        return 1;
                    else 
                        return 0;
            }
            else if(((abs(nY-iY)+abs(nX-iX))<=2) && abs(nY-iY)!=2 && abs(nX-iX)!=2){
                if(Side(nX,nY))
                    return 1;
                else
                    return 0;
            }
            break;
        case 'h': // 馬
        case 'H':if(abs(nX-iX)==abs(nY-iY)){
            chessNum=0;
            if(abs(nX-iX)<2 && abs(nY-iY)<2)
                return 1;
            // Choose the direction
            if(nX>iX){ // Right
                if(nY>iY){ // Down-Right
                    for(i=iY+1,j=iX+1;i<nY;i++,j++){
                        if(bd[i][j]!='t')
                            chessNum++;
                    }
                }
                else{ // Up-Right
                    for(i=iY-1,j=iX+1;i>nY;i--,j++){
                        if(bd[i][j]!='t')
                            chessNum++;
                    }
                }
            }
            else{ // Left
                if(nY>iY){ // Down-Left
                    for(i=iY+1,j=iX-1;i<nY;i++,j--){
                        if(bd[i][j]!='t')
                            chessNum++;
                    }
                }
                else{ // Up-Left
                    for(i=iY-1,j=iX-1;i>nY;i--,j--){
                        if(bd[i][j]!='t')
                            chessNum++;
                    }
                }
            }
            // Find if there's any block
            if(chessNum>0)
                return 0;
            else
                if(Side(nX,nY))
                    return 1;
                else
                    return 0; 
            }
            break;
        default:
            return 0;
            break;
    }
}
/* Determine if the player select the right chess in their team */
int inputCheck(char chess){
    if(count%2==1){
        switch(chess){
            case 'b':
            case 'g':
            case 'y':
            case 'f':
            case 'c':
            case 's':
            case 'j':
            case 'w':
            case 'z':
                return 1;
                break;
            case 'B':
            case 'G':
            case 'Y':
            case 'F':
            case 'C':
            case 'S':
            case 'J':
            case 'W':
            case 't':
            case 'Z':
                return 0;
                break;                        
        }
    }
    else if(count%2==0){
        switch(chess){
            case 'b':
            case 'g':
            case 'y':
            case 'f':
            case 'c':
            case 's':
            case 'j':
            case 'w':
            case 't':
            case 'z':
                return 0;
                break;
            case 'B':
            case 'G':
            case 'Y':
            case 'F':
            case 'C':
            case 'S':
            case 'J':
            case 'W':
            case 'Z':
                return 1;
                break;                        
        }
    }
}
