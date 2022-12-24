#include "../inc/main.h"
#include "../inc/watcher.h"
#include "../inc/typedef.h"

ev_io* io_watcher;
ev_timer* timer_watcher;
Flags FLAG;

void timer(){
    struct ev_loop *loop = EV_DEFAULT;
    if(count%2==0)
        time(&p1start);
    else
        time(&p2start);
    ev_io_init(io_watcher,io_cb,0,EV_READ);
    ev_io_start(loop, io_watcher);
    ev_timer_init(timer_watcher,timer_cb,0,1);
    ev_timer_start(loop,timer_watcher);
    ev_run(loop,0);
}
void stoptimer(){
    struct ev_loop *loop = EV_DEFAULT;
    ev_io_stop(loop,io_watcher);
    ev_timer_stop(loop,timer_watcher);
    ev_break(loop,EVBREAK_ALL);
}

static void io_cb(EV_P_ ev_io *w, int revents){
    // getchar();
    if(count%2==0)
        p1timesum = p1timeSec;
    else
        p2timesum = p2timeSec;
    ev_io_stop(loop,w);
    ev_timer_stop(loop,timer_watcher);
    ev_break(loop,EVBREAK_ALL);
}

static void timer_cb(EV_P_ ev_timer *w, int revents){
    system("clear");
    printtimer();
    chessPrint();
    if(count%2==0)
        printf("- 輪到上方玩家 -\n");
    else
        printf("- 輪到下方玩家 -\n");
    switch(FLAG){
        case INPUT1: /* Get Input */
            printf("輸入目標的座標X與Y:\n> ");
            break;
        case INPUT2:
            printf("輸入下一步的座標X與Y:\n> ");
            break;
        case DROPINPUT:
            printf("選擇要打入的棋子編號！\n");
            break;
        case DROPPLACE:
            printf("輸入要打入的座標\n");\
            break;
        case PROMOTECHOOSE:
            printf("是否將該棋子升變？(Y/N)\n> ");
            break;
    }

    if(count%2==0)
        time(&p1end);
    //     p1timeSec++;
    else
        time(&p2end);
    //     p2timeSec++;
    timecalc();
    fflush(stdout);
}
/* Print the timer above the chessboard */
void printtimer(){
    printf("上方玩家: %d:%02d\n",p1timeMin,p1timeSec);
    printf("下方玩家: %d:%02d\n",p2timeMin,p2timeSec);
}
/* Calculate the time for player1/player2 */
void timecalc(){
    if(count%2==0){
        p1timeSec = p1timesum + abs(difftime(p1start,p1end));
        if((p1timeSec/60)!=0){
            p1timeMin++;
            p1timeSec=0;
            time(&p1start);
            // p1timeSec=(int)(p1timeSec)%60;
        }
    }
    else{
        p2timeSec = p2timesum + abs(difftime(p2start,p2end));
        if((p2timeSec/60)!=0){
            p2timeMin++;
            p2timeSec=0;
            time(&p2start);
            // p2timeSec=(int)(p2timeSec)%60;
        }
    }
}