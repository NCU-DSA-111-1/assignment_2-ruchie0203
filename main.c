#include "typedef.h"
#include "functions.h"

extern char *optarg;
extern int optind, opterr, optopt;
matchPtr current,head;

void main(int argc, char **argv){
    int i;
    int iX,iY,nX,nY,O;
    int newX=0,newY=0;
    int inputX=0,inputY=0;
    char input;
    current=(matchPtr) malloc(sizeof(match));
    head=(matchPtr) malloc(sizeof(match));
    current->next=current->previous=NULL; // Initialize the linked list
    head=current;
    chessIni();
    /* GET THE OPTIONS */
    while((O =getopt(argc,argv,"ns:l:"))!=-1){
        switch(O){
            case 'n': // -n: new game
                status=1;
                break;
            case 's': // -s [file name]: game saving location
                fPtr = fopen(optarg,"w+");
                if(fPtr == NULL){
                    printf("File cannot be opened!\n");
                    return;
                }
                status=1;
                break;
            
            case 'l': // -l [file name]: game loading location
                fPtr = fopen(optarg,"r+");
                if(fPtr == NULL){
                    printf("File cannot be opened!");
                    return;
                }
                readbd();
                status=2;
                break;
            default:
                printf("Not Supported Option!\n");
                sleep(1);
                status=0;
                END=1;
                break;
        }
    }
    while(!END){
        /* Start the timer for player1/player2*/
        if(count%2==0)
            time(&p1start);
        
        else
            time(&p2start);
        
       /* GAME MODE */
        while(status==1){
            system("clear");
            printtimer();
            chessPrint();
            if(winlose()==1){
                printf("= 恭喜上方玩家獲勝 =\n");
                status = 0;
                END = 1;
                saveInfo();  
                sleep(1);
                break;
            }
            else if(winlose()==2){
                printf("= 恭喜下方玩家獲勝 =\n");
                status=0;
                END = 1;
                saveInfo();  
                sleep(1);
                break;
            }
            if(count%2==0)
                printf("- 輪到上方玩家 -\n");
            else
                printf("- 輪到下方玩家 -\n");
            /* Get Input */
            printf("輸入目標的座標X與Y:\n> ");
            scanf("%c",&input);
            if(input == 's' || input == 'S'){ // Type in s/S for Game Save
                getchar();
                printf("Game Save!\n");
                status=1;
                END = 0;
                saveInfo();  
                if(count%2==0)
                    time(&p1end);
                else
                    time(&p2end);
                timecalc(); 
                sleep(1);
                break;
            }
            else if(input == '0'){ // Type in 0 for Regret
                getchar();
                if(count==0){
                    printf("已經到第一手了\n");
                    sleep(1);
                    break;
                }
                if(count%2==0)
                    time(&p1end);
                else
                    time(&p2end);
                timecalc(); 
                count--;
                current=current->previous;
                chessBack(current->iX,current->iY,current->nX,current->nY,current->chessMove,current->chessEaten);
                break;
            }
            else if(input == 'E' || input == 'e'){
                printf("Save and exit the game!\n");
                saveInfo();
                status = 0;
                END = 1;
                sleep(1);
                break;
            }
            else if(input =='D' || input == 'd'){
                getchar();
                printf("選擇要打入的棋子編號！\n");
                drop();
                timecalc(); 
                break;
            }
            inputX=input-48;
            scanf("%d",&inputY);
            getchar();
            if(inputX > 10 || inputY > 10 || inputX < 0 || inputY < 0){
                printf("輸入錯誤:(\n");
                if(count%2==0)
                    time(&p1end);
                else
                    time(&p2end);
                timecalc(); 
                sleep(1);
                break;
            }
            iX=9-inputX; //input position: X coordinate
            iY=inputY-1; //input position: y coordinate
            if(inputCheck(bd[iY][iX])==0){
                printf("選錯棋子了！\n");
                if(count%2==0)
                    time(&p1end);
                else
                    time(&p2end);
                timecalc(); 
                sleep(1);
                break;
            }
            /* Get Target */
            printf("輸入下一步的座標X與Y:\n> ");
            scanf("%d",&newX);
            if((newX/10)==0)
                scanf("%d",&newY);
            else{
                newY=newX%10;
                newX=newX/10;
            }
            getchar();
            if(newX > 10 || newY > 10 || newX < 0 || newY < 0){
                printf("輸入錯誤:P\n");
                if(count%2==0)
                    time(&p1end);
                else
                    time(&p2end);
                timecalc(); 
                sleep(1);
                break;   
            }
            nX=9-newX; //target position: x coordinate
            nY=newY-1; //target position: y coordinate
            if(moveCheck(iX,iY,nX,nY)==1){
                switch(bd[iY][iX]){
                    case 'j':
                    case 'w':
                    case 'J':
                    case 'W':
                    case 'k':
                    case 'K':
                    case 'h':
                    case 'H':
                    case 'd':
                    case 'D':
                        break;
                    default:
                        promoDetect(iX,iY,nX,nY);
                        break;
                } 
                addMatch(iX,iY,nX,nY,bd[iY][iX],bd[nY][nX]);
                if(count%2==0)
                    time(&p1end);
                else
                    time(&p2end);
                timecalc();
                chessMove(iX,iY,nX,nY);
                break;
            }
            else{
                printf("違反規則:(\n");
                if(count%2==0)
                    time(&p1end);
                else
                    time(&p2end);
                timecalc(); 
                sleep(1);
                break;
            }
        }

        /* READ-ONLY MODE */
        while(status==2){
            system("clear");
            chessPrint(); 
            printf("輸入 \'f\' 移動下一手 \'b\' 移動上一手\n　　 \'p\' 遊玩模式　 \'e\' 退出\n> ");
            scanf("%c",&input);
            getchar();
            if((input == 'f' || input == 'F') && count >= maxcount){
                printf("已經是最後一手了\n"); 
                sleep(1);
            }
            else if((input == 'b' || input == 'B') && count == 0){
                printf("已經是第一手了\n");
                sleep(1);
            }
            else if((input == 'f' || input == 'F') && count < maxcount){
                chessMove(current->iX,current->iY,current->nX,current->nY);
                current=current->next;
            }
            else if((input == 'b' || input == 'B') && count > 0){
                count--;
                current=current->previous;
                chessBack(current->iX,current->iY,current->nX,current->nY,current->chessMove,current->chessEaten);
            }
            else if(input == 'e' || input == 'E'){
                END = 1;
                break;
            }
            else if(input == 'p' || input == 'P'){
                status=1;
                rewind(fPtr);
                for(i=0;i<count;i++){
                    fscanf(fPtr,"\n");
                }
                break;
            }
            
        } 
    }
    free(current);
    free(head);
    fclose(fPtr);
}
/* Detect if the chess can be promoted */
void promoDetect(int iX,int iY, int nX, int nY){
    char I;
    char *c = &bd[iY][iX];
    int rightInput=0;
    if(count%2==0){
        if(nY<6 && iY<6)
            return;
        while(rightInput!=1){
            printf("是否將該棋子升變？(Y/N)\n> ");
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
            printf("是否將該棋子升變？(Y/N)\n> ");
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
void drop(){
    int i;
    int newX=0,newY=0;
    int dropNum=0;
    char *c;
    scanf("%d",&dropNum);
    getchar();
    if(dropNum<=0){
        printf("選錯了啦!\n");
        sleep(1);
        return;
    }
    dropNum-=1;
    if((count%2==0 && dropNum>top1) || (count%2==1 && dropNum>top2)){
        printf("駒台上沒有這個位子喔!\n");
        sleep(1);
        return;
    }
    printf("輸入要打入的座標\n");\
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
        return;
    }
    if(count%2==0){
        if(dropNum>top1)
            return;
        addMatch(-2,dropNum,newX,newY,chessEat1[dropNum]-32,'t');
        switch(*c){
            case 'h': //角 -> 馬
                *c='C';
                break;
            case 'd': //飛 -> 龍
                *c='F';
                break;
            case 'a': //銀 -> 全
                *c='Y';
                break; 
            case 'x': //香 -> 杏
                *c='S';
                break;
            case 'p': //桂 -> 圭
                *c='G';
                break;
            case 'k': //步 -> と
                *c='B';
                break;
            default:
                *c=(char)(chessEat1[dropNum]-32);
                break;
        }
        for(i=dropNum;i<top1;i++){
            chessEat1[i]=chessEat1[i+1];
        }
        chessEat1[top1]='t';
        top1--;
    }
    else{
        if(dropNum>top2)
            return;
        addMatch(-2,dropNum,newX,newY,chessEat2[dropNum]+32,'t');
        switch(*c){
            case 'H': //角 -> 馬
                *c='c';
                break;
            case 'D': //飛 -> 龍
                *c='f';
                break;
            case 'A': //銀 -> 全
                *c='y';
                break; 
            case 'X': //香 -> 杏
                *c='s';
                break;
            case 'P': //桂 -> 圭
                *c='g';
                break;
            case 'K': //步 -> と
                *c='b';
                break;
            default:
                *c=(char)(chessEat2[dropNum]+32);
                break;
        }
        for(i=dropNum;i<top2;i++){
            chessEat2[i]=chessEat2[i+1];
        }
        chessEat2[top2]='t';
        top2--;
    }
    count++;
    
}
/* Calculate the time for player1/player2 */
void timecalc(){
    int p1sum=0,p2sum=0;
    if(count%2==0){
        p1sum+=abs(difftime(p1end,p1start));
        p1timeSec+=p1sum;
        if(((int)(p1timeSec)/60)!=0){
            p1timeMin+=((int)(p1timeSec)/60);
            p1timeSec=(int)(p1timeSec)%60;
        }
    }
        
    else{
        p2sum+=abs(difftime(p2end,p2start));
        p2timeSec+=p2sum;
        if((p2timeSec/60)!=0){
            p2timeMin+=((int)(p2timeSec)/60);
            p2timeSec=(int)(p2timeSec)%60;
        }
    }
}
/* Print the timer above the chessboard */
void printtimer(){
    printf("上方玩家: %d:%02d\n",p1timeMin,(int)(p1timeSec));
    printf("下方玩家: %d:%02d\n",p2timeMin,(int)(p2timeSec));
}
/* Read the file and store the data in "Match" array */
void readbd(){
    int i;
    int iX,iY,nX,nY;
    char chessmoved,chesseaten;
    while(!feof(fPtr)){
        fscanf(fPtr,"%d %d %c %d %d %c\n",&iX,&iY,&chessmoved,&nX,&nY,&chesseaten);
        if(iX==-1)
            break;
        addMatch(iX,iY,nX,nY,chessmoved,chesseaten);
        chessMove(iX,iY,nX,nY);
    }
    FROMREADTOPLAY=1;
    maxcount=count;
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
            chessEat1[iY]=cM+32;
            bd[nY][nX]='t';
        }
        else{
            top2++;
            for(i=top2;i>=iY;i--){ // iY now is the dropNum(the number of chess that player wants to drop)
                chessEat2[i]=chessEat2[i-1];
            }
            chessEat2[iY]=cM-32;
            bd[nY][nX]='t';
        }
        return;
    }
    switch(cM){
        case 'D':
            cM = 'F';
            break;
        case 'H':
            cM = 'C';
            break;
        case 'X':
            cM = 'S';
            break;
        case 'K':
            cM = 'B';
            break;
        case 'P':
            cM = 'G';
            break;
        case 'A':
            cM = 'Y';
            break;
        case 'd':
            cM = 'f';
            break;
        case 'h':
            cM = 'c';
            break;
        case 'x':
            cM = 's';
            break;
        case 'k':
            cM = 'b';
            break;
        case 'p':
            cM = 'g';
            break;
        case 'a':
            cM = 'y';
            break;            
        
    }
    bd[iY][iX]=cM;
    bd[nY][nX]=cE;
    // printf("top1:%c, top2:%c\n",chessEat1[top1],chessEat2[top2]);
    if(chessEat1[top1]==cE){
        chessEat1[top1]='t';
        top1--;
    }
    else if(chessEat2[top2]==cE){
        chessEat2[top2]='t';
        top2--;
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
                return 1;
                break;                        
        }
    }
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
                return 1;
                break;                               
        }
    }
    else
        return 0;
}
/* Save the chessboard */
void saveInfo(){
    int i;
    rewind(fPtr);
    current=head;
    for(i=0;i<count;i++){
        fprintf(fPtr,"%d %d %c %d %d %c\n",current->iX,current->iY,current->chessMove,current->nX,current->nY,current->chessEaten);
        current=current->next;
    }
    if(FROMREADTOPLAY){
        if(count<maxcount){
            fprintf(fPtr,"%d %d",-1,-1);
        }
    }
    fflush(fPtr);
    
}
/* To move the chess */
void chessMove(int iX,int iY, int nX, int nY){
    int i;
    if(iX==-2){ // The DROP situation
        bd[nY][nX]=current->chessMove;
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
    if(count%2==0 && bd[nY][nX]!='t'){
        top1++;
        chessEat1[top1]=bd[nY][nX];
    }
    else if(count%2==1 && bd[nY][nX]!='t'){
        top2++;
        chessEat2[top2]=bd[nY][nX];
    }
    bd[nY][nX]=bd[iY][iX];
    bd[iY][iX]='t';
    count++;
    return;
}
/* Print the chessboard*/
void chessPrint(){
    int i,j;
    Print_eaten_chess=1;
    for(i=0;i<top1+1;i++){
        chessIdentify(chessEat1[i]);
        printf(" ");
    }
    printf("\n");
    printf("９ ８ ７ ６ ５ ４ ３ ２ １\n");
    Print_eaten_chess=0;
    for(i=0;i<9;i++){
        for(j=0;j<9;j++){
            chessIdentify(bd[i][j]);
            printf(" ");
            if(j==8){
                switch (i+1){
                case 1:
                    printf("一");
                    break;
                case 2:
                    printf("二");
                    break;    
                case 3:
                    printf("三");
                    break;
                case 4:
                    printf("四");
                    break;
                case 5:
                    printf("五");
                    break;
                case 6:
                    printf("六");
                    break;
                case 7:
                    printf("七");
                    break;
                case 8:
                    printf("八");
                    break;
                case 9:
                    printf("九");
                    break;
                }
            }
        }
    printf("\n");
    }
    Print_eaten_chess=1;
    for(i=0;i<top2+1;i++){
        chessIdentify(chessEat2[i]);
        printf(" ");
    }
    Print_eaten_chess=0;
    printf("\n");
}
/* Sub function in [chessPrint] to print every chess */
void chessIdentify(char c){
    switch(c){
        case 't':
            printf("．");
            break;
        case 'b':
            printf("\033[31m步\033[0m");
            break;
        case 'B':
            printf("\033[34m步\033[0m");
            break;
        case 'f':
            printf("\033[31m飛\033[0m");
            break;
        case 'F':
            printf("\033[34m飛\033[0m");
            break;
        case 'c':
            printf("\033[31m角\033[0m");
            break;
        case 'C':
            printf("\033[34m角\033[0m");
            break;
        case 's':
            printf("\033[31m香\033[0m");
            break;
        case 'S':
            printf("\033[34m香\033[0m");
            break;
        case 'g':
            printf("\033[31m桂\033[0m");
            break;
        case 'G':
            printf("\033[34m桂\033[0m");
            break;
        case 'y':
            printf("\033[31m銀\033[0m");
            break;
        case 'Y':
            printf("\033[34m銀\033[0m");
            break;
        case 'j':
            printf("\033[31m金\033[0m");
            break;
        case 'J':
            printf("\033[34m金\033[0m");
            break;
        case 'w':
            printf("\033[31m玉\033[0m");
            break;
        case 'W':
            printf("\033[34m王\033[0m");
            break;
        case 'h':
            if(Print_eaten_chess){
                printf("\033[31m角\033[0m");
                break;
            }
            printf("\033[31m馬\033[0m");
            break;
        case 'H':
            if(Print_eaten_chess){
                printf("\033[34m角\033[0m");
                break;
            }
            printf("\033[34m馬\033[0m");
            break;
        case 'd':
            if(Print_eaten_chess){
                printf("\033[31m飛\033[0m");
                break;
            }
            printf("\033[31m龍\033[0m");
            break;
        case 'D':
            if(Print_eaten_chess){
                printf("\033[34m飛\033[0m");
                break;
            }
            printf("\033[34m龍\033[0m");
            break;
        case 'A':
            if(Print_eaten_chess)
                printf("\033[34m銀\033[0m");
                break;
            printf("\033[34m全\033[0m");
            break;
        case 'X':
            if(Print_eaten_chess){
                printf("\033[34m香\033[0m");
                break;
            }
            printf("\033[34m杏\033[0m");
            break;
        case 'P':
            if(Print_eaten_chess){
                printf("\033[34m桂\033[0m");
                break;
            }
            printf("\033[34m圭\033[0m");
            break;
        case 'K':
            if(Print_eaten_chess){
                printf("\033[34m步\033[0m");
                break;
            }
            printf("\033[34mと\033[0m");
            break;
        case 'a':
            if(Print_eaten_chess){
                printf("\033[31m銀\033[0m");
                break;
            }
            printf("\033[31m全\033[0m");
            break;
        case 'x':
            if(Print_eaten_chess){
                printf("\033[31m香\033[0m");
                break;
            }
            printf("\033[31m杏\033[0m");
            break;
        case 'p':
            if(Print_eaten_chess){
                printf("\033[31m桂\033[0m");
                break;
            }
            printf("\033[31m圭\033[0m");
            break;
        case 'k':
            if(Print_eaten_chess){
                printf("\033[31m步\033[0m");
                break;
            }
            printf("\033[31mと\033[0m");
            break;
    }
}
/* Chessboard initialization */
void chessIni(){
    int i,j;
    for(i=0;i<9;i++){
        for(j=0;j<9;j++){
            y=i+1;
            x=9-j;
            bd[i][j]='t';
            switch(y){
                case 3:
                    bd[i][j]='B';
                    break;
                case 7:
                    bd[i][j]='b';
                    break;
                case 2:
                    if(x==8)
                        bd[i][j]='F';
                    if(x==2)
                        bd[i][j]='C';
                    break;
                case 8:
                    if(x==2)
                        bd[i][j]='f';
                    if(x==8)
                        bd[i][j]='c';
                    break;
                case 1:
                    if(x==9 || x==1)
                        bd[i][j]='S';
                    if(x==8 || x==2)
                        bd[i][j]='G';
                    if(x==7 || x==3)
                        bd[i][j]='Y';
                    if(x==6 || x==4)
                        bd[i][j]='J';
                    if(x==5)
                        bd[i][j]='W';
                    break;
                case 9:
                    if(x==9 || x==1)
                        bd[i][j]='s';
                    if(x==8 || x==2)
                        bd[i][j]='g';
                    if(x==7 || x==3)
                        bd[i][j]='y';
                    if(x==6 || x==4)
                        bd[i][j]='j';
                    if(x==5)
                        bd[i][j]='w';
                    break;
            }
        }
    }
}
/* Creat a new match data*/
void addMatch(int iX,int iY, int nX, int nY, char cM, char cE){
    matchPtr new = (matchPtr) malloc(sizeof(match));
    current->iX=iX;
    current->iY=iY;
    current->nX=nX;
    current->nY=nY;
    current->chessMove=cM;
    current->chessEaten=cE;
    current->next=new;
    new->previous=current;
    new->next=NULL;
    current=current->next;
}