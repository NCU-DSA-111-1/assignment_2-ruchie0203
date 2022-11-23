#include "../inc/functions.h"
#include "../inc/typedef.h"

matchPtr current,head,temp;

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
    maxcount=count;
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
    if(count<maxcount){
        fprintf(fPtr,"%d %d",-1,-1);
    }
    fflush(fPtr);
    
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
    current=new;
}