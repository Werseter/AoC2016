#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "md5.h"

#define INPUT "rrrbmfta"

typedef struct state
{
    char moves[1000];
    char x;
    char y;
    struct state *n;
} state;

state *newstate(state *ptrs)
{
    state *temp=malloc(sizeof(state)+1);
    ptrs?memcpy(temp->moves, ptrs->moves, 1000):memset(temp->moves, 0, 1000);
    temp->x = ptrs?ptrs->x:0;
    temp->y = ptrs?ptrs->y:0;
    temp->n = 0;
    return temp;
}

void hashf(char *x, BYTE *buf)
{
    MD5_CTX ctx;
    md5_init(&ctx);
    md5_update(&ctx, x, strlen(x));
    md5_final(&ctx, buf);
}

void htos(BYTE *x, char *str)
{
    int i;
    memset(str, 0, 32);
    char temp[3]={0};
    for(i=0;i<16;i++)
    {
        sprintf(temp,"%2x", x[i]);
        if(temp[0]==' ')
            temp[0]='0';
        strcat(str,temp);
    }
}

char shiftcnvrt(char i, char j)
{
    if(i==0 && j==-1)
        return 'U';
    if(i==1 && j==0)
        return 'R';
    if(i==0 && j==1)
        return 'D';
    if(i==-1 && j==0)
        return 'L';
    return 0;
}

state *attach(state *ptrs, char i, char j)
{
    state *temp = newstate(ptrs);
    temp->moves[strlen(temp->moves)+1]=0;
    temp->moves[strlen(temp->moves)]=shiftcnvrt(i, j);
    temp->x+=i;
    temp->y+=j;
    state *attach = ptrs;
    while (attach->n)
        attach = attach->n;
    attach->n = temp;
    return temp;
}

void makevalidmove(state *ptrs, char i, char j, int *moves)
{
    if(ptrs->x+i>=0 && ptrs->x+i<4 && ptrs->y+j>=0 && ptrs->y+j<4)
    {
        state *temp = attach(ptrs, i, j);
        if(temp->x == 3 && temp->y == 3)
            if(*moves<strlen(temp->moves+strlen(INPUT)))
                *moves=strlen(temp->moves+strlen(INPUT));
    }
}

void makemove(state *ptrs, int *max)
{
    BYTE hash[17]={0};
    char str[33]={0};
    hashf(ptrs->moves, &hash);
    htos(hash, str);
    char i=0;
    char j=-1;
    if(str[0]>='b' && str[0]<='f')
        makevalidmove(ptrs, i, j, max);
    i=1;
    j=0;
    if(str[3]>='b' && str[0]<='f')
        makevalidmove(ptrs, i, j, max);
    i=0;
    j=1;
    if(str[1]>='b' && str[0]<='f')
        makevalidmove(ptrs, i, j, max);
    i=-1;
    j=0;
    if(str[2]>='b' && str[0]<='f')
        makevalidmove(ptrs, i, j, max);
}

int main()
{
	state *ptrs = newstate(NULL);
	strcpy(ptrs->moves, INPUT);
	int maxmoves=0;
    while(ptrs)
    {
        if(ptrs->x!=3 || ptrs->y!=3)
            makemove(ptrs, &maxmoves);
        ptrs=ptrs->n;
    }
    if(maxmoves!=0)
        printf("The length of the longest path that reaches the vault is %d\n",maxmoves);
    else
        printf("Solution not found! (Somehow)\n");
    return -1;
}
