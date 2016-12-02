#include <stdio.h>

int main()
{
    char pad[5][5]={{ 0 , 0 ,'5', 0 , 0 },
                    { 0 ,'2','6','A', 0 },
                    {'1','3','7','B','D'},
                    { 0 ,'4','8','C', 0 },
                    { 0 , 0 ,'9', 0 , 0 }};
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
            if (i=='U' && y>0 && pad[x][y-1]!=0)
                y--;
            if (i=='D' && y<4 && pad[x][y+1]!=0)
                y++;
            if (i=='R' && x<4 && pad[x+1][y]!=0)
                x++;
            if (i=='L' && x>0 && pad[x-1][y]!=0)
                x--;
            if (i=='\n' || i=='\0')
            {
                printf("%c",pad[x][y]);
                x=1;
                y=1;
            }
        }
        printf("%c",pad[x][y]);
        printf("\n");
    }
    return 0;
}
