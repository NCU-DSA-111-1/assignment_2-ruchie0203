#ifndef WATCHER_H
#define WATCHER_H

#include <ev.h>

typedef enum flags Flags;
enum flags{
    INPUT1,
    INPUT2,
    DROPINPUT,
    DROPPLACE,
    PROMOTECHOOSE,
};

extern ev_io* io_watcher;
extern ev_timer* timer_watcher;
extern Flags FLAG;

void timer();
void stoptimer();
void timecalc();
void printtimer();
static void io_cb(EV_P_ ev_io *w, int revents);
static void timer_cb(EV_P_ ev_timer *w, int revents);

#endif