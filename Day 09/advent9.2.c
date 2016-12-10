#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

typedef struct data
{
    char str[15000];
    int a;
    int b;
    unsigned long long s;
} data;

typedef struct node
{
    struct node *p;
    struct node *n[50];
    data data;
} node;

int add(char str[], int a, int b, node *ptr)
{
    int i;
    node *temp = malloc(sizeof(node));
    temp -> p = NULL;
    for(i=0;i<50;i++)
        temp -> n[i] = NULL;
    strcpy(temp->data.str, str);
    temp->data.a = a;
    temp->data.b = b;
    temp->data.s = 0;
    for(i=0;ptr->n[i]!=NULL;i++);
    ptr->n[i]=temp;
    ptr->n[i]->p=ptr;
    return i;
}

int analyze(node *ptr)
{
    int a,b,x,y;
    char buf[5000]={0};
    x=0;
    while(ptr->data.str[x]!=0)
    {
        if(ptr->data.str[x]!='(')
            x++;
        else
        {
            a=0;
            b=0;
            x++;
            while(ptr->data.str[x]!='x')
            {
                a=a*10+ptr->data.str[x]-'0';
                x++;
            }
            x++;
            while(ptr->data.str[x]!=')')
            {
                b=b*10+ptr->data.str[x]-'0';
                x++;
            }
            x++;
            ptr->data.a-=a+5+(int)log10(a)+(int)log10(b);
            for(y=0;y<a;y++)
                buf[y]=ptr->data.str[x+y];
            analyze(ptr->n[add(buf, a, b, ptr)]);
            for(y=0;buf[y]!=0;y++)
                buf[y]=0;
            x+=a;
        }
    }
    return 0;
}

int sumtree(node *ptr)
{
    int i;
    if(ptr->data.s==0)
    {
        if(ptr->n[0]==NULL)
            ptr->data.s=ptr->data.a*ptr->data.b;
        else
        {
            for(i=0;ptr->n[i]!=NULL;i++)
                if(ptr->n[i]->data.s==0)
                    sumtree(ptr->n[i]);
            for(i=0;ptr->n[i]!=NULL;i++)
                ptr->data.s+=ptr->data.b*ptr->n[i]->data.s;
            ptr->data.s+=ptr->data.a;
        }
    }
    else if(ptr->p!=NULL)
        sumtree(ptr->p);
    return 0;
}

int main()
{
    FILE *in;
    in=fopen("input.txt","r+");
    if (in==NULL) printf("\nFNF\n");
    else
    {
        int i;
        int x=0;
        node *head;
        head = malloc(sizeof(node));
        head -> p = NULL;
        for(i=0;i<50;i++)
            head -> n[i] = NULL;
        while(!feof(in))
        {
            i=fgetc(in);
            if(i!=' ' && feof(in)==0)
            {
                head->data.str[x]=i;
                x++;
            }
        }
        head->data.a=x;
        head->data.b=1;
        analyze(head);
        sumtree(head);
        printf("Decompressed length of the file is %llu",head->data.s);
    }
    return 0;
}
