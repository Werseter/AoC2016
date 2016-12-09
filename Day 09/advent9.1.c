#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    FILE *in;
    in=fopen("input.txt","r+");
    if (in==NULL) printf("\nFNF\n");
    else
    {
        char i;
        int x,y,z,s=0;
        while(feof(in)==0)
        {
            i=fgetc(in);
            if(i!='(' && i!=' ' && feof(in)==0)
                s++;
            else if(i=='(')
            {
                x=0;
                y=0;
                i=fgetc(in);
                while(i!='x')
                {
                    x=x*10+i-'0';
                    i=fgetc(in);
                }
                i=fgetc(in);
                while(i!=')')
                {
                    y=y*10+i-'0';
                    i=fgetc(in);
                }
                s+=x*y;
                for(y=0;y<x;y++)
                    fgetc(in);
            }
        }
        printf("Decompressed length of the file is %d",s);
    }
    return 0;
}
