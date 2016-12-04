#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
int blng(int x, int y[])
{
    int i;
    for(i=0;i<5;i++)
        if(y[i]==x)
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
        int x[27]={0},x2[5],y,z,z2,s=0;
        for(z2=0;z2<5;z2++) x2[z2]=26;
        int i;
        char buf[5]={0}, buf2[60]={0};
        while (feof(in)==0)
        {
            i=fgetc(in);
            if(i!='\n')
            {
                if(isalpha(i))
                {
                    x[i-97]++;
                    z=strlen(buf2);
                    buf2[z]=i;
                }
                else if(isdigit(i))
                {
                    z=strlen(buf);
                    buf[z]=i;
                }
                else if(i=='[')
                {
                    y++;
                    x[26]=-1;
                    for(z2=0;z2<5;z2++)
                        for(z=0;z<26;z++)
                            if(x[z]>x[x2[z2]] && !blng(z,x2))
                                x2[z2]=z;
                    y=0;
                    for(z2=0;z2<5;z2++)
                    {
                        i=fgetc(in);
                        if(i-97!=x2[z2])
                            y++;
                    }
                    if(y==0)
                    {
                        for(z=0;z<60;z++)
                            if(buf2[z]!=0)
                                buf2[z]=((buf2[z]-97+atoi(buf))%26)+97;
                            if(!strcmp("northpoleobjectstorage",buf2))
                                s=atoi(buf);
                    }
                    for(z2=0;z2<5;z2++) {x2[z2]=26; buf[z2]=0;}
                    for(z=0;z<26;z++) x[z]=0;
                    for(z=0;z<60;z++) buf2[z]=0;
                }
            }
        }
        printf("Sector ID of the room where North Pole objects are stored is %d\n",s);
    }
    return 0;
}
