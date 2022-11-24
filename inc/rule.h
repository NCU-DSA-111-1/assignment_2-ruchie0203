#ifndef RULE_H
#define RULE_H

void promoDetect(int iX,int iY, int nX, int nY);
int drop();
int Side(int x,int y);
void chessMove(int iX,int iY, int nX, int nY);
int winlose();
int moveCheck(int iX,int iY, int nX, int nY);
void chessBack(int iX,int iY, int nX, int nY, char cM, char cE);
void addMatch(int iX,int iY, int nX, int nY, char cM, char cE);
int inputCheck(char chess);

#endif