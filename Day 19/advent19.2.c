#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define INPUT 3018458

int main()
{
    int *elf = malloc(INPUT*sizeof(int));
    int i,j=floor(INPUT/(float)2),k=INPUT;
    for(i=0;i<INPUT;i++)
        elf[i]=1;
    for(i=0;elf[i]!=INPUT;i=(i+1)%INPUT)
        if(elf[i]!=0)
        {
            elf[i]+=elf[j];
            elf[j]=0;
            for(j=(j+1)%INPUT;elf[j]==0;j=(j+1)%INPUT);
            if(k%2==1)
                for(j=(j+1)%INPUT;elf[j]==0;j=(j+1)%INPUT);
            k--;
        }
    printf("Elf %d gets all the presents\n", i+1);
    return 0;
}
