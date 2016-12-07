#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int sub(char a[], char b[])
{
    int i,j,l1=strlen(a);
    if(l1>=3)
        for(i=0;i<l1-2;i++)
        {
            for(j=0;j<3;j++)
                if(a[i+j]!=b[j])
                    break;
            if(j==3)
                return 1;
        }
    return 0;
}

int aba(char *a, char *b)
{
    char i,k;
    while(b[k*4]!=0) k++;
    for(i=0;a[i+2]!=0;i++)
        if(a[i]!=a[i+1] && a[i]==a[i+2])
        {
            b[k*4]=a[i+1];
            b[k*4+1]=a[i+0];
            b[k*4+2]=a[i+1];
            k++;
        }
    return k;
}

int main()
{
    FILE *in;
    in=fopen("input.txt","r+");
    if (in==NULL) printf("\nFNF\n");
    else
    {
        char x[30]={0};
        static char x1[30][30]={0}, x2[30][4]={0};
        char aba1=0,aba2=0,i,y=0,z=0;
        int s=0;
        while (feof(in)==0)
        {
            i=fgetc(in);
            if(i=='\n' || feof(in)!=0)
            {
                aba1=aba(x,x2);
                if(aba1!=0)
                    for(y=0;x1[y][0]!=0  && aba2==0;y++)
                        for(z=0;x2[z][0]!=0 && aba2==0;z++)
                            if(sub(x1[y],x2[z])!=0)
                                aba2=1;
                if(aba2==1)
                    s++;
                for(y=0;y<30;y++)
                {
                    x[y]=0;
                    for(z=0;x1[y][z]!=0;z++)
                        x1[y][z]=0;
                    for(z=0;x2[y][z]!=0;z++)
                        x2[y][z]=0;
                }
                y=0;
                z=0;
                aba1=0;
                aba2=0;
            }
            else if(i=='[' || i==']')
            {
                if(i=='[')
                    aba1=aba(x,x2);
                else
                {
                    strcpy(x1[z], x);
                    z++;
                }
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
        printf("%d IPs support SSL\n",s);
    }
    return 0;
}
