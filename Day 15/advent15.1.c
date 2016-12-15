#include<stdio.h>

int main()
{
    char input[][3]={{17,0,1},
                     {7 ,0,0},
                     {19,0,2},
                     {5 ,0,0},
                     {3 ,0,0},
                     {13,0,5}};
    int found=0;
    int i,x=0;
    int l=sizeof(input)/3;
    while(found==0)
    {
        for(i=0;i<l;i++)
            if((i+1+x+input[i][1]+input[i][2])%input[i][0]==0)
                found=1;
            else
            {
                found=0;
                break;
            }
        if(found==0)
            x++;
    }
    printf("The first time you can press the button to get a capsule is time period %d\n",x);

    return 0;
}
