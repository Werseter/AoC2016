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
        int x,y,z;
        char buf[5]={0};
        int i;
        int dir=0;
        x=0;
        y=0;
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
                    if(dir==0)
                        y=y+z;
                    else
                        y=y-z;
                }
                else
                {
                    if(dir==1)
                        x=x+z;
                    else
                        x=x-z;
                }
            }
            else
            {
                z=strlen(buf);
                buf[z]=i;
            }
        }
        printf("The shortest path to the destination is %d blocks long", x+y);
    }
    return 0;
}
