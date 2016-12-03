#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
    FILE *in;
    in=fopen("input.txt","r+");
    if (in==NULL) printf("\nFNF\n");
    else
    {
        int a[220][220];
        int x1,x2,y1,y2,z;
        char buf[5]={0};
        int i;
        int dir=0;
        x1=0+6;                     //Cartesian shifts calculated elsewhere
        y1=0+43;                    //And set here for optimal operation
        while (feof(in)==0)
        {
            i=fgetc(in);
            if (i=='L')
            {
                dir=dir--;
                if(dir==-1)
                    dir=3;
            }
            else if (i=='R')
            {
                dir=dir++;
                if(dir==4)
                    dir=0;
            }
            else if (i==',' || feof(in)!=0)
            {
                fgetc(in);
                z=atoi(buf);
                for(i=0;i<5;i++) buf[i]=0;
                if(!(dir%2))
                {
                    x2=x1;
                    if(dir==0)
                        y2=y1+z;
                    else
                        y2=y1-z;
                }
                else
                {
                    y2=y1;
                    if(dir==1)
                        x2=x1+z;
                    else
                        x2=x1-z;
                }
                if(x2!=x1)
                {
                    while(x2>x1)
                    {
                        if(a[x1][y1]==1) goto found;
                        a[x1][y1]++;
                        x1++;
                    }
                    while(x2<x1)
                    {
                        if(a[x1][y1]==1) goto found;
                        a[x1][y1]++;
                        x1--;
                    }
                }
                if(y2!=y1)
                {
                    while(y2>y1)
                    {
                        if(a[x1][y1]==1) goto found;
                        a[x1][y1]++;
                        y1++;
                    }
                    while(y2<y1)
                    {
                        if(a[x1][y1]==1) goto found;
                        a[x1][y1]++;
                        y1--;
                    }
                }
                goto cont;
                found:
                    printf("Easter Bunny HQ is %d blocks away", x1-6+y1-43);
                    exit(0);
                cont:;
            }
            else
            {
                z=strlen(buf);
                buf[z]=i;
            }
        }

    }
    return 0;
}
