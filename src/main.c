#include "../inc/data.h"
#include "../inc/rule.h"
#include "../inc/main.h"
#include "../inc/watcher.h"
#include "../inc/typedef.h"

extern char *optarg;
extern int optind, opterr, optopt;

time_t p1start=0,p1end=0,p2start=0,p2end=0;
matchPtr current,head,temp;
int p1timeSec=0,p2timeSec=0;
int p1timeMin=0,p2timeMin=0;
int p1timesum=0,p2timesum=0;

void main(int argc, char **argv){
    int i;
    int iX,iY,nX,nY,O;
    int newX=0,newY=0;
    int inputX=0,inputY=0;
    char input;
    
    current=(matchPtr) malloc(sizeof(match));
    head=(matchPtr) malloc(sizeof(match));  
    temp=(matchPtr) malloc(sizeof(match));
    io_watcher = (ev_io*) malloc(sizeof(ev_io));
    timer_watcher = (ev_timer*) malloc(sizeof(ev_timer));
    current->next=current->previous=NULL; // Initialize the linked list
    head=current;
    
    chessIni();
    /* GET THE OPTIONS */
    while((O=getopt(argc,argv,"ns:l:"))!=-1){
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

        /* GAME MODE */
        while(status==1){
            FLAG = INPUT1;
            timer();
            if(winlose()==1){
                printf("= 恭喜上方玩家獲勝 =\n");
                status = 0;
                END = 1;
                saveInfo();  
                sleep(1);
                // ev_break(loop,EVBREAK_ALL);
                break;
            }
            else if(winlose()==2){
                printf("= 恭喜下方玩家獲勝 =\n");
                status=0;
                END = 1;
                saveInfo();  
                sleep(1);
                // ev_break(loop,EVBREAK_ALL);
                break;
            }
            
            scanf("%c",&input);
            
            if(input == 's' || input == 'S'){ // Type in s/S for Game Save
                getchar();
                printf("Game save!\n");
                status=1;
                END = 0;
                saveInfo();  
                sleep(2);
                break;
            }
            else if(input == '0'){ // Type in 0 for Regret
                getchar();
                if(count==0){
                    printf("已經到第一手了\n");
                    stoptimer();
                    sleep(1);
                    break;
                }
                count--;
                current=current->previous;
                chessBack(current->iX,current->iY,current->nX,current->nY,current->chessMoved,current->chessEaten);
                temp=current->next;
                current->next=NULL;
                free(temp);
                break;
            }
            else if(input == 'E' || input == 'e'){
                printf("Save and exit the game!\n");
                saveInfo();
                status = 0;
                END = 1;
                // sleep(1);
                break;
            }
            else if(input =='D' || input == 'd'){
                getchar();
                FLAG = DROPINPUT;
                timer();
                if(drop()){
                    count++;
                }                
                break;
            }
            inputX=input-48;
            scanf("%d",&inputY);
            
            getchar();
            if(inputX > 10 || inputY > 10 || inputX < 0 || inputY < 0){
                printf("輸入錯誤:(\n");
                sleep(1);
                break;
            }
            iX=9-inputX; //input position: X coordinate
            iY=inputY-1; //input position: y coordinate
            if(inputCheck(bd[iY][iX])==0){
                printf("選錯棋子了！\n");
                sleep(1);
                break;
            }
            FLAG = INPUT2;
            timer();
            /* Get Target */
            scanf("%d",&newX);
            if((newX/10)==0)
                scanf("%d",&newY);
            else{
                newY=newX%10;
                newX=newX/10;
            }
            getchar();
            if(newX > 10 || newY > 10 || newX < 0 || newY < 0){
                printf("輸入錯誤:(\n");
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
                chessMove(iX,iY,nX,nY,bd[iY][iX],bd[nY][nX]);
                break;
            }
            else{
                printf("違反規則:(\n");
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
                chessMove(current->iX,current->iY,current->nX,current->nY,current->chessMoved,current->chessEaten);
                current=current->next;
            }
            else if((input == 'b' || input == 'B') && count > 0){
                count--;
                current=current->previous;
                chessBack(current->iX,current->iY,current->nX,current->nY,current->chessMoved,current->chessEaten);
            }
            else if(input == 'e' || input == 'E'){
                END = 1;
                break;
            }
            else if(input == 'p' || input == 'P'){
                status=1;
                FROMREADTOPLAY=1;
                rewind(fPtr);
                for(i=0;i<count;i++){
                    fscanf(fPtr,"\n");
                }
                break;
            }
            
        } 
    }
    free(io_watcher);
    free(timer_watcher);
    free(current);
    free(head);
    fclose(fPtr);
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
        case 'q':
            printf("\033[31m步\033[0m");
            break;
        case 'B':
        case 'Q':
            printf("\033[34m步\033[0m");
            break;
        case 'f':
        case 'l':
            printf("\033[31m飛\033[0m");
            break;
        case 'F':
        case 'L':
            printf("\033[34m飛\033[0m");
            break;
        case 'c':
            printf("\033[31m角\033[0m");
            break;
        case 'C':
            printf("\033[34m角\033[0m");
            break;
        case 's':
        case 'z':
            printf("\033[31m香\033[0m");
            break;
        case 'S':
        case 'Z':
            printf("\033[34m香\033[0m");
            break;
        case 'g':
        case 'i':
            printf("\033[31m桂\033[0m");
            break;
        case 'G':
        case 'I':
            printf("\033[34m桂\033[0m");
            break;
        case 'y':
        case 'n':
            printf("\033[31m銀\033[0m");
            break;
        case 'Y':
        case 'N':
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
