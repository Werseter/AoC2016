#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int abba(char x[])
{
    int i;
    for(i=0;x[i+3]!=0;i++)
        if(x[i]!=x[i+1] && x[i]==x[i+3] && x[i+1]==x[i+2])
            return 1;
    return 0;
}

int main()
{
    FILE *in;
    in=fopen("input.txt","r+");
    if (in==NULL) printf("\nFNF\n");
    else
    {
        int s=0;
        char x[30]={0},abba1=0,abba2=0,i,y=0;
        while (feof(in)==0)
        {
            i=fgetc(in);
            if(i=='\n' || feof(in)!=0)
            {
                abba1+=abba(x);
                for(y=0;y<30;y++)
                        x[y]=0;
                y=0;
                if(abba1!=0 && abba2==0)
                    s++;
                abba1=0;
                abba2=0;
            }
            else if(i=='[' || i==']')
            {
                if(i=='[')
                    abba1+=abba(x);
                else
                    abba2+=abba(x);
                for(y=0;y<30;y++)
                    x[y]=0;
                y=0;
            }
            else
            {
                x[y]=i;
                y++;
            }
        }
        printf("%d IPs support TLS\n",s);
    }
    return 0;
}
