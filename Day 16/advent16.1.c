#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define input "00101000101111010"
#define disc_size 272

void dragonize(char *str)
{
    int i,l=strlen(str);
    char temp[disc_size]={0};
    char buf;
    strcpy(temp, str);
    for(i=0;i<l-i;i++)
    {
        buf=temp[i];
        temp[i]=abs((temp[l-1-i]-47)%2)+48;
        temp[l-1-i]=(buf-47)%2+48;
    }
    if(i==l-i)
        temp[i]=abs((temp[i]-47)%2)+48;
    strncat(str, "0", disc_size-l);
    strncat(str, temp, disc_size-l-1);
}

void checksum(char *str)
{
    int i,j,l=strlen(str);
    char temp[disc_size]={0};
    for(i=0,j=0;i+1<l;i+=2,j++)
        temp[j]=str[i]==str[i+1]?49:48;
    strcpy(str, temp);
}

int main()
{
    char str[disc_size]={0};
    strcpy(str, input);
    while(strlen(str)<disc_size)
        dragonize(str);
    do
        checksum(str);
    while(strlen(str)%2!=1);
    printf("The correct checksum is %s\n",str);
    return 0;
}
