#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT 1362
#define REACHX 31
#define REACHY 39

//This code is using GCC compiler specific macro for calculating 1s (for speed)

typedef struct state
{
    char moves;
    char tiles[50][50];
    char x;
    char y;
    struct state *n;
} state;

state *newstate(state *ptrs)
{
    state *temp=malloc(sizeof(state)+1);
    temp->moves = ptrs?ptrs->moves:0;
    ptrs?memcpy(temp->tiles, ptrs->tiles, 2500):memset(temp->tiles, 0, 2500);
    temp->x = ptrs?ptrs->x:1;
    temp->y = ptrs?ptrs->y:1;
    temp->n = 0;
    return temp;
}
char iswall(char x, char y)
{
    if(__builtin_popcount(INPUT+(x+y)*(x+y)+3*x+y)%2==0)
        return -1;
    return 0;
}

char isdup(state *ptrs, char i, char j)
{
    if(ptrs->tiles[ptrs->x+i][ptrs->y+j]==1)
        return 0;
    return -1;
}

void attach(state *ptrs, char i, char j)
{
    state *temp = newstate(ptrs);
    temp->moves++;
    temp->x+=i;
    temp->y+=j;
    temp->tiles[temp->x][temp->y]++;
    state *attach = ptrs;
    while (attach->n)
        attach = attach->n;
    attach->n = temp;
}

void makevalidmove(state *ptrs, char i, char j)
{
    if(ptrs->x+i>=0 && ptrs->x+i<50 && ptrs->y+j>=0 && ptrs->y+j<50)
       if(isdup(ptrs, i, j)==-1)
            if(iswall(ptrs->x+i, ptrs->y+j)==-1)
                if(ptrs->x+i==REACHX && ptrs->y+j==REACHY)
                    {printf("Fewest number of steps required to reach (%d, %d) is %d steps\n", REACHX, REACHY, ptrs->moves+1); exit(0);}
                else
                    attach(ptrs, i, j);
}

void makemove(state *ptrs)
{
    char i=0;
    char j=-1;
    makevalidmove(ptrs, i, j);
    i=1;
    j=0;
    makevalidmove(ptrs, i, j);
    i=0;
    j=1;
    makevalidmove(ptrs, i, j);
    i=-1;
    j=0;
    makevalidmove(ptrs, i, j);
}

int main()
{
    state *ptrs = newstate(NULL);
    while(ptrs)
    {
        makemove(ptrs);
        ptrs=ptrs->n;
    }
    printf("Solution not found! (Somehow)\n");
    return -1;
}
