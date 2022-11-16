#ifndef TYPEDEFPTR_H
#define TYPEDEFPTR_H

#include <time.h>
#include <stdio.h>

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

#endif
