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
        int i,j;
        int a,b,c;
        static char buf[12][10]={{0}};
        int bots[1250][4]={{0}};
        for(j=0;j<1250;j++)
            for(i=0;i<4;i++)
                bots[j][i]=-1;
        while(feof(in)==0)
        {
            fscanf(in,"%s",buf[0]);
            if(!strcmp(buf[0], "value"))
            {
                for(i=1;i<6;i++)
                    fscanf(in,"%s",buf[i]);
                a=0;
                b=0;
                for(i=0;buf[5][i]!=0;i++)
                    a=a*10+buf[5][i]-'0';
                for(i=0;buf[1][i]!=0;i++)
                    b=b*10+buf[1][i]-'0';
                if(bots[a][0]==-1)
                    bots[a][0]=b;
                else
                    bots[a][1]=b;
            }
            else
            {
                for(i=1;i<12;i++)
                    fscanf(in,"%s",buf[i]);
                a=0;
                b=0;
                c=0;
                for(i=0;buf[1][i]!=0;i++)
                    a=a*10+buf[1][i]-'0';
                for(i=0;buf[6][i]!=0;i++)
                    b=b*10+buf[6][i]-'0';
                if(!strcmp(buf[5], "output"))
                    b+=1000;
                for(i=0;buf[11][i]!=0;i++)
                    c=c*10+buf[11][i]-'0';
                if(!strcmp(buf[10], "output"))
                    c+=1000;
                bots[a][2]=b;
                bots[a][3]=c;
            }
            for(j=0;j<12;j++)
                for(i=0;i<10;i++)
                    buf[j][i]=0;
        }
        while(1)
            for(b=0;b<250;b++)
                if(bots[b][0]!=-1 && bots[b][1]!=-1)
                {
                    if(bots[1000][0]!=-1 && bots[1001][0]!=-1 && bots[1002][0]!=-1)
                    {
                        b=bots[1000][0]*bots[1001][0]*bots[1002][0];
                        printf("If you multiply together the values of one chip in each of outputs 0, 1, and 2, you get %d",b);
                        exit(1);
                    }
                    if(bots[bots[b][2]][0]==-1)
                        i=0;
                    else if(bots[bots[b][2]][1]==-1)
                        i=1;
                    if(bots[bots[b][3]][0]==-1)
                        j=0;
                    else if(bots[bots[b][3]][1]==-1)
                        j=1;
                    bots[bots[b][2]][i] = bots[b][0]<bots[b][1] ? bots[b][0] : bots[b][1];
                    bots[bots[b][3]][j] = bots[b][0]>bots[b][1] ? bots[b][0] : bots[b][1];
                    bots[b][0]=-1;
                    bots[b][1]=-1;
                }

    }
    return 0;
}
