#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define X 14

typedef struct state
{
    char moves;
    char items[X][3][20];
    char status[4][4];
    char floornum;
    struct state *n;
} state;

state *newstate(state *ptrs)
{
    state *temp=malloc(sizeof(state)+1);
    temp->moves = ptrs?ptrs->moves:0;
    ptrs?memcpy(temp->items, ptrs->items, X*61):memset(temp->items, 0, X*61);
    memset(temp->status, 0, 17);
    temp->floornum=ptrs?ptrs->floornum:0;
    temp->n = 0;
    return temp;
}

void update(state *prts)
{
    char i,j;
    for(j=0;j<4;j++)
    {
        for(i=0;i<X;i++)
            if(prts->items[i][2][0]==j)
                prts->status[j][prts->items[i][1][0]]++;
        prts->status[j][0]=abs(prts->status[j][1]-prts->status[j][2]);
        prts->status[j][3]=prts->status[j][1]+prts->status[j][2];
    }
}

char isempty(state *prts, char floor)
{
    char i;
    for(i=0;i<X;i++)
        if(prts->items[i][2][0]==floor)
            return -1;
    return 0;
}

char isdup(state *ptrs, state *head)
{
    state *curr = head;
    while(curr)
        if(ptrs->floornum==curr->floornum && memcmp(ptrs->items, curr->items, X*61)==0)
            return -1;
        else
            curr=curr->n;
    return 0;
}

char isequiv(state *ptrs, state *head)
{
    state *curr = head;
    while(curr)
        if(ptrs->floornum==curr->floornum && memcmp(ptrs->status, curr->status, 17)==0)
            return -1;
        else
            curr=curr->n;
    return 0;
}

char makevalidmove(state *ptrs, char i, char j, char dir, state *head)
{
    state *temp = newstate(ptrs);
    temp->floornum+=dir;
    char floor = temp->floornum;
    if(floor>=0 && floor<=3)
    {
        char found=0;
        char a,b,c,d;
        if(dir==-1)
        {
            for(a=floor;a>-1 && isempty(temp, a)==0;a--);
            if(a==-1)
                {free(temp); return -1;}
        }
        temp->moves++;
        temp->items[i][2][0]+=dir;
        if(j!=-1)
            temp->items[j][2][0]+=dir;
        if(isdup(temp, head)!=0)
            {free(temp); return -1;}
        c=0;
        d=0;
        for(a=0;a<X;a++)
            if(temp->items[a][2][0]==floor)
                if(temp->items[a][1][0]==1)
                    c++;
                else if(temp->items[a][1][0]==2)
                    d++;
        if(c!=0 && d!=0)
        {
            for(a=0;a<X;a++)
                if(temp->items[a][2][0]==floor &&
                   temp->items[a][1][0]==2)
                {
                    found=0;
                    for(b=0;b<X;b++)
                        if(temp->items[b][2][0]==floor &&
                           temp->items[b][1][0]==1 &&
                           strcmp(temp->items[b][0], temp->items[a][0])==0)
                           found=1;
                    if(found==0)
                        {free(temp); return -1;}
                }
        }
        c=0;
        d=0;
        for(a=0;a<X && found==0;a++)
            if(temp->items[a][2][0]==floor)
                if(temp->items[a][1][0]==1)
                    c++;
                else if(temp->items[a][1][0]==2)
                    d++;
        if(c!=0 && d!=0)
        {
            for(a=0;a<X;a++)
                if(temp->items[a][2][0]==floor-dir &&
                   temp->items[a][1][0]==2)
                {
                    found=0;
                    for(b=0;b<X;b++)
                        if(temp->items[b][2][0]==floor-dir &&
                           temp->items[b][1][0]==1 &&
                           strcmp(temp->items[b][0], temp->items[a][0])==0)
                           found=1;
                    if(found==0)
                        {free(temp); return -1;}
                }
        }
        update(temp);
        if(temp->status[3][3]==X)
        {
            printf("Minimum number of steps required to bring all of the objects to the fourth floor is %d steps\n", temp->moves);
            exit(0);
        }

        if(isequiv(temp, head)==0)
        {
            state *attach = ptrs;
            while (attach->n)
                attach = attach->n;
            attach->n = temp;
        }
        return 0;
    }
    free(temp);
    return -1;
}

void checkmoves(state *ptrs, state *head)
{
    char floor = ptrs->floornum;
    char i,j;
    for(i=0;i<X;i++)
        if(ptrs->items[i][2][0]==floor)
        {
            for(j=i+1;j<X;j++)
                if(ptrs->items[j][2][0]==floor)
                {
                    makevalidmove(ptrs, i, j, 1, head);
                    makevalidmove(ptrs, i, j, -1, head);
                }
            makevalidmove(ptrs, i, -1, 1, head);
            makevalidmove(ptrs, i, -1, -1, head);
        }
}

int main()
{
    FILE *in;
    in=fopen("input2.txt","r+");
    if (in==NULL) printf("\nFNF\n");
    else
    {
        char i,j,k;
        char a=0,b=0,c=0;
        state *start = newstate(NULL);
        char buf[30]={0};
        char buf2[30]={0};
        while(feof(in)==0)
        {
            i=fgetc(in);
            if(i=='\n' || i==' ' || feof(in)!=0)
            {
                if(strcmp(buf2,"generator")==0)
                {
                    strcpy(start->items[c][0], buf);
                    start->items[c][1][0]=1;
                    start->items[c][2][0]=a;
                    c++;
                }
                if(strcmp(buf2,"microchip")==0)
                {
                    for(k=0;buf[k]!='-';k++);
                    buf[k]=0;
                    strcpy(start->items[c][0], buf);
                    start->items[c][1][0]=2;
                    start->items[c][2][0]=a;
                    c++;
                }
                for(j=0;buf[j]!=0;j++)
                    buf[j]=0;
                strcpy(buf, buf2);
                for(j=0;buf2[j]!=0;j++)
                    buf2[j]=0;
                b=0;
                if(i=='\n')
                    a++;
            }
            else if(isalpha(i) || i=='-')
            {
                buf2[b]=i;
                b++;
            }
        }
        update(start);
        checkmoves(start, start);
        state *ptrs = start;
        while(ptrs)
        {
            checkmoves(ptrs, start);
            ptrs=ptrs->n;
        }
        printf("Impossible! (Somehow)\n");
    }
    return -1;
}
