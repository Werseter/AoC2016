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
        int x=0,xmax=0;
        int a[10][27]={0};
        char i;
        while (feof(in)==0)
        {
            i=fgetc(in);
            if (i!='\n' && feof(in)==0)
            {
                a[x][i-97]++;
                if(a[x][i-97]>a[x][a[x][26]])
                    a[x][26]=i-97;
                x++;
            }
            else
            {
                if(xmax==0)
                    xmax=x;
                x=0;
            }
        }
        char out[10]={0};
        for(i=0;i<xmax;i++)
            out[i]=a[i][26]+97;
        printf("The error-corrected version of the message is: %s", out);
    }
    return 0;
}
