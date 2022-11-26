#ifndef WATCHER_H
#define WATCHER_H

#include <ev.h>

extern ev_io* io_watcher;
extern ev_timer* timer_watcher;

void timer();
static void io_cb(EV_P_ ev_io *w, int revents);
static void timer_cb(EV_P_ ev_timer *w, int revents);

#endif