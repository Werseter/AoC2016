#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "md5.h"

void hashf(char *x, char *y, BYTE *buf)
{
    int i;
    MD5_CTX ctx;
    md5_init(&ctx);
    md5_update(&ctx, x, strlen(x));
    md5_update(&ctx, y, strlen(y));
    md5_final(&ctx, buf);
}

void htos(BYTE *x, char *str)
{
    int i;
    memset(str, 0, 32);
    char temp[3]={0};
    for(i=0;i<16;i++)
    {
        sprintf(temp,"%2x", x[i]);
        if(temp[0]==' ')
            temp[0]='0';
        strcat(str,temp);
    }
}

int hasrep(int count, char *str)
{
    int i,j,reps;
    int l=strlen(str);
    for(i=0;i+count<l;i++)
    {
        reps=0;
        for(j=i+1;j<i+count && reps!=-1;j++)
            if(str[j]==str[i])
                reps=1;
            else
                reps=-1;
        if(reps==1)
            return i;
    }
    return -1;
}

int main()
{
	int i,j,x=1;
	int a,b;
	BYTE buf[16];
	BYTE str[33];
	BYTE t1[] = {"ngcjuoqr"}; //Input goes here
	BYTE t2[15]={0};
	char keys[1000][33]={0};
	for(i=0;x!=64;i++)
    {
        if(strcmp(keys[i%1000],"")!=0)
            if((a = hasrep(3, keys[i%1000])) != -1)
                for(j=0;j<1000;j++)
                    if(strcmp(keys[i%1000],keys[j])!=0)
                        if((b = hasrep(5, keys[j])) != -1)
                            if(keys[i%1000][a] == keys[j][b])
                                {x++; break;}
        itoa(i, &t2, 10);
        hashf(t1,t2, buf);
        for(j=0;j<2016;j++)
        {
            htos(buf, str);
            hashf(str,"", buf);
        }
        htos(buf, keys[i%1000]);
    }
    printf("Index %d produces 64th one-time pad key", i-1001);
	return 0;
}
