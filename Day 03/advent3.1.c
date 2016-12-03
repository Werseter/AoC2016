#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int trngl(int x,int y,int z)
    {return !(x+y<=z||x+z<=y||y+z<=x);}

int main()
{
    FILE *in;
    in=fopen("input.txt","r+");
    if (in==NULL) printf("\nFNF\n");
    else
    {
        int x[3],y=0,z,s=0;
        int i;
        char buf[5]={0};
        while (feof(in)==0)
        {
            i=fgetc(in);
            if(i!='\n')
            {
                if(i==' ')
                {
                    if(buf[0]!=0)
                    {
                        x[y]=atoi(buf);
                        y++;
                        for(z=0;z<4;z++) buf[z]=0;
                    }
                }
                else
                {
                    z=strlen(buf);
                    buf[z]=i;
                }
            }
            else
            {
                x[y]=atoi(buf);
                y=0;
                for(z=0;z<4;z++) buf[z]=0;
                s+=trngl(x[0],x[1],x[2]);
            }
        }
        x[y]=atoi(buf);
        s+=trngl(x[0],x[1],x[2]);
        printf("Number of possible triangles is %d\n",s);
    }
    return 0;
}
