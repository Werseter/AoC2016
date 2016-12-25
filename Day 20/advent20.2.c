#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *in;
    in=fopen("input.txt","r+");
    if(in==NULL) printf("\nFNF\n");
    else
    {
        int i,j=0,a=0;
        unsigned k=0,l=0;
        unsigned num[1200][2]={{0}};
        for(i=0;feof(in)==0;i++)
            fscanf(in, "%u-%u\n", &num[i][0], &num[i][1]);
        i=0;
        while(1)
        {
            while(j==0)
            {
                j=1;
                for(i=0;num[i][0]+num[i][1]!=0;i++)
                    if(k>=num[i][0] && k<=num[i][1])
                        {j=0; k=num[i][1]+1;}
            }
            if(k<l)
                break;
            k++;
            l=k;
            j=0;
            a++;
        }
        printf("There are %d IPs allowed by the blacklist\n",a);
    }
    return 0;
}
