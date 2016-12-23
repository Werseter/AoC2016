#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT ".^.^..^......^^^^^...^^^...^...^....^^.^...^.^^^^....^...^^.^^^...^^^^.^^.^.^^..^.^^^..^^^^^^.^^^..^"

char issafe(char a, char b, char c)
{
    char rule[4][3]={{'^', '^', '.'},
                     {'.', '^', '^'},
                     {'^', '.', '.'},
                     {'.', '.', '^'}};
    int i;
    for(i=0;i<4;i++)
        if(a==rule[i][0] && b==rule[i][1] && c==rule[i][2])
            return '^';
    return '.';
}

int main()
{
    char row[120]={0};
    char row2[120]={0};
    strcpy(row, INPUT);
    int count=0,i,j,l=strlen(row);
    for(i=0;i<l;i++)
        if(row[i]=='.')
            count++;
    for(j=1;j<40;j++)
    {
        for(i=0;i<l;i++)
        {
            if(i==0)
                row2[i]=issafe('.', row[i], row[i+1]);
            else if(i==l-1)
                row2[i]=issafe(row[i-1], row[i], '.');
            else
                row2[i]=issafe(row[i-1], row[i], row[i+1]);
            if(row2[i]=='.')
                count++;
        }
        strcpy(row, row2);
        memset(row2, 0, l);
    }
    printf("There are %d safe tiles in 40 rows\n", count);
    return 0;
}
