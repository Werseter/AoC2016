#include <stdio.h>

int main()
{
    int pad[3][3]={{1,4,7},{2,5,8},{3,6,9}};
    char out[10]={0};
    char i;
    FILE *in;
    in=fopen("advent2.txt","r+");
    if (in==NULL) printf("\nFNF\n");
    else
    {
        int x=1,y=1;
        printf("Code is ");
        while (feof(in)==0)
        {
            i=fgetc(in);
            //printf("%c\n", i);
            if (i=='U' && y>0)
                y--;
            if (i=='D' && y<2)
                y++;
            if (i=='R' && x<2)
                x++;
            if (i=='L' && x>0)
                x--;
            if (i=='\n' || i=='\0')
            {
                printf("%d",pad[x][y]);
                x=1;
                y=1;
            }
        }
        printf("%d",pad[x][y]);
        printf("\n");
    }
    return 0;
}
