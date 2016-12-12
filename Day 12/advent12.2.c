#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main()
{
    FILE *in;
    in=fopen("input.txt","r+");
    if (in==NULL) printf("\nFNF\n");
    else
    {
        int i,j;
        int reg[4]={0};
        reg[2]=1; //initialize register c to be 1
        int k=0;
        char buf[5]={0};
        int instr[30][3]={{0}};
        while(feof(in)==0)
        {
            fscanf(in,"%s", buf);
            if(strcmp(buf,"cpy")==0 || strcmp(buf,"jnz")==0)
            {
                if(strcmp(buf,"cpy")==0)
                    instr[k][0]=1;
                else
                    instr[k][0]=2;
                fscanf(in,"%s", buf);
                if(isdigit(buf[0]) || buf[0]=='-')
                    instr[k][1]=atoi(buf);
                else
                    instr[k][1]=1000+buf[0];
                fscanf(in,"%s", buf);
                if(isdigit(buf[0]) || buf[0]=='-')
                    instr[k][2]=atoi(buf);
                else if(buf[0]==45)
                    instr[k][2]=-atoi(buf[1]);
                else
                    instr[k][2]=1000+buf[0];
            }
            else if(strcmp(buf,"inc")==0 || strcmp(buf,"dec")==0)
            {
                if(strcmp(buf,"inc")==0)
                    instr[k][0]=3;
                else
                    instr[k][0]=4;
                fscanf(in,"%s", buf);
                if(isdigit(buf[0]))
                    instr[k][1]=atoi(buf);
                else
                    instr[k][1]=1000+buf[0];
            }
            k++;
        }
        /*for(i=0;instr[i][0]!=0;i++)
        {
            for(j=0;j<(instr[i][0]==1||instr[i][0]==2?3:2);j++)
                instr[i][j]>1000?printf("%c ",instr[i][j]-1000):printf("%d ",instr[i][j]);
            printf("\n");
        }*/
        i=0;
        while(instr[i][0]!=0)
        {
            if(instr[i][0]==1)
            {
                //printf("%c <- %d\n",instr[i][2]-1000,instr[i][1]>1000?reg[instr[i][1]-1000-'a']:instr[i][1]);
                reg[instr[i][2]-1000-'a']=instr[i][1]>1000?reg[instr[i][1]-1000-'a']:instr[i][1];
            }
            else if(instr[i][0]==2)
            {
                if ((instr[i][1]>1000 && reg[instr[i][1]-1000-'a']!=0) ||(instr[i][1]<1000 && instr[i][1]!=0))
                {
                    //printf("Jumping %d\n",instr[i][2]>1000?reg[instr[i][2]-1000-'a']:instr[i][2]);
                    i+=(instr[i][2]>1000?reg[instr[i][2]-1000-'a']:instr[i][2])-1;
                }
            }
            else if(instr[i][0]==3)
            {
                //printf("%c <- %d\n",instr[i][1]-1000,reg[instr[i][1]-1000-'a']+1);
                reg[instr[i][1]-1000-'a']++;
            }
            else if(instr[i][0]==4)
            {
                //printf("%c <- %d\n",instr[i][1]-1000,reg[instr[i][1]-1000-'a']-1);
                reg[instr[i][1]-1000-'a']--;
                }
            i++;
        }
        printf("After executing the assembunny code, the value left in register a is %d",reg[0]);
    }
    return 0;
}
