#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define XSIZE 50
#define YSIZE 6

int rect(char a, char b, char *disp)
{
    int i,j;
    for(j=0;j<b;j++)
        for(i=0;i<a;i++)
            disp[j*XSIZE+i]=1;
    return 0;
}
int rotate(char a, char b, char c, char *disp)
{
    char t[XSIZE]={0};
    if(a==0)
    {
        for(a=0;a<XSIZE;a++)
            t[a+c<XSIZE ? a+c : a+c-XSIZE]=disp[b*XSIZE+a];
        for(a=0;a<XSIZE;a++)
            disp[b*XSIZE+a]=t[a];
    }
    else
    {
        for(a=0;a<YSIZE;a++)
            t[a+c<YSIZE ? a+c : a+c-YSIZE]=disp[a*XSIZE+b];
        for(a=0;a<YSIZE;a++)
            disp[a*XSIZE+b]=t[a];
    }
    return 0;
}

int ctoi(int c) {return c - '0';}

int main()
{
    FILE *in;
    in=fopen("input.txt","r+");
    if (in==NULL) printf("\nFNF\n");
    else
    {
        int i=0;
        int a,b,c,s=0;
        char in2[1000][100]={0};
        static char display[YSIZE][XSIZE]={0};
        while(feof(in)==0)
        {
            fscanf(in,"%s",&in2[i]);
            i++;
        }
        i=0;
        while(in2[i][0]!=0)
        {
            if(in2[i][1]=='e')
            {
                i++;
                if(strlen(in2[i])==3)
                    rect(ctoi(in2[i][0]),ctoi(in2[i][2]),display);
                else
                    rect(ctoi(in2[i][0])*10+ctoi(in2[i][1]),ctoi(in2[i][3]),display);
            }
            else
            {
                i++;
                if(in2[i][0]=='r')
                    a=0;
                else
                    a=1;
                i++;
                if(strlen(in2[i])==3)
                    b=ctoi(in2[i][2]);
                else
                    b=ctoi(in2[i][2])*10+ctoi(in2[i][3]);
                i+=2;
                c=atoi(in2[i]);
                rotate(a,b,c,display);
            }
            i++;
        }
        for(b=0;b<YSIZE;b++)
        {
            for(a=0;a<XSIZE;a++)
                if(display[b][a]==1)
                {
                    printf("#");
                    s++;
                }
                else
                    printf(".");
            printf("\n");
        }
        printf("\n%d pixels on the screen will be lit\n",s);
    }
    return 0;
}
