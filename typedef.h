#ifndef TYPEDEF_H
#define TYPEDEF_H

#include <time.h>
#include <stdio.h>

#define ROW 9
#define COL 9

extern int x,y;
extern char bd[ROW][COL];
extern int status;
extern int count, maxcount;
extern int top1,top2;
extern double p1timeSec,p2timeSec;
extern int p1timeMin,p2timeMin;
extern char chessEat1[40];
extern char chessEat2[40];
extern int FROMREADTOPLAY;
extern int END;
extern int Print_eaten_chess;

extern time_t p1start,p1end,p2start,p2end;

struct matchinfo{
    int iX,iY,nX,nY;
    char chessMove;
    char chessEaten;
    struct matchinfo* next;
    struct matchinfo* previous;
};

typedef struct matchinfo match;
typedef struct matchinfo* matchPtr;

FILE *fPtr;

extern matchPtr current,head,temp;

#endif
