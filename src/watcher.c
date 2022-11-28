#include "../inc/main.h"
#include "../inc/watcher.h"
#include "../inc/typedef.h"

ev_io* io_watcher;
ev_timer* timer_watcher;
Flags FLAG;

void timer(){
    struct ev_loop *loop = EV_DEFAULT;
    ev_io_init(io_watcher,io_cb,0,EV_READ);
    ev_io_start(loop, io_watcher);
    ev_timer_init(timer_watcher,timer_cb,0,1);
    ev_timer_start(loop,timer_watcher);
    ev_run(loop,0);
}
static void io_cb(EV_P_ ev_io *w, int revents){
    // getchar();
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
        p1timeSec++;
    else
        p2timeSec++;
    timecalc();
    fflush(stdout);
}