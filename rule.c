#include "functions.h"
#include "typedef.h"

#define ROW 9
#define COL 9

int x=0,y=0;
char bd[ROW][COL];
int status = 0;
int count = 0, maxcount;
int top1=-1,top2=-1;
double p1timeSec=0,p2timeSec=0;
int p1timeMin=0,p2timeMin=0;
char chessEat1[40];
char chessEat2[40];
int FROMREADTOPLAY=0;
int END=0;
int Print_eaten_chess=0;

time_t p1start=0,p1end=0,p2start=0,p2end=0;


/* Shogi rule check */
int moveCheck(int iX,int iY, int nX, int nY){
    int i,j,chessNum=0;
    switch(bd[iY][iX]){
        case 'b': // Lower "步"
            if(nX==iX && iY-nY == 1){
                return 1;
            }
            else{
                return 0;
            }
            break;
        case 'B': // Upper "步"
            if(nX==iX && nY-iY == 1){
                return 1;
            }
            else{
                return 0;
            }
            break;
        case 's': // Lower "香車"
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
        case 'k': // Lower "金"(成桂, 成銀, 成香)
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
        case 'K': // Upper "金"(成桂, 成銀, 成香)
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
            if(((abs(nY-iY)+abs(nX-iX))<=2) && abs(nY-iY)!=2 && abs(nX-iX)!=2){
                if(Side(nX,nY))
                    return 1;
                else
                    return 0;
            }
            break;
        case 'y': // Lower "銀將"
            if(nY==iY)
                return 0;
            else if(nX==iX && nY-iY==1)
                return 0;
            else{
                if(Side(nX,nY))
                    return 1;
                else
                    return 0;
            }
            break;
        case 'Y': // Upper "銀將"
            if(nY==iY)
                return 0;
            else if(nX==iX && iY-nY==1)
                return 0;
            else{
                if(Side(nX,nY))
                    return 1;
                else
                    return 0;
            }
            break;
        case 'c': // "角行"
        case 'C':
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
        case 'd':
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
        case 'h':
        case 'H':
            break;
        default:
            return 0;
            break;
    }
}