#ifndef FUNCTIONSPTR_H
#define FUNCTIONSPTR_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int Side(int x,int y);
int inputCheck(char chess);
int winlose();
void saveInfo();
void chessIni();
void chessPrint();
void chessIdentify(char c);
int moveCheck(int iX,int iY, int nX, int nY);
void chessMove(int iX,int iY, int nX, int nY);
void chessBack(int iX,int iY, int nX, int nY, char cM, char cE);
void readbd();
void timecalc();
void printtimer();
void drop();
void promoDetect(int iX,int iY, int nX, int nY);
void addMatch(int iX,int iY, int nX, int nY, char cM, char cE);

#endif