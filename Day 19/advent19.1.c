#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT 3018458

int main()
{
    int *elf = malloc(INPUT*sizeof(int));
    int i,j;
    for(i=0;i<INPUT;i++)
        elf[i]=1;
    for(i=0;elf[i]!=INPUT;i=(i+1)%INPUT)
        if(elf[i]!=0)
        {
            for(j=(i+1)%INPUT;j!=i && elf[j]==0;j=(j+1)%INPUT);
            elf[i]+=elf[j];
            elf[j]=0;
        }
    printf("Elf %d gets all the presents\n", i+1);
    return 0;
}
