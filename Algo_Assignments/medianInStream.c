#include<stdio.h>
#define SIZE 1000

int left=0,right=1;
int heap[2][SIZE],count[2];
double median;

void swap(int a, int i, int j)
{
    int temp=heap[a][i];
    heap[a][i] = heap[a][j];
    heap[a][j] = temp;
}

void swim(int a, int k)
{
    if(a==left)
    {
        while(k>1 && heap[a][k]>heap[a][k/2])
            swap(a,k,k/2);
    }
    if(a==right)
    {
        while(k>1 && heap[a][k]<heap[a][k/2])
            swap(a,k,k/2);
    }
}

void sink(int a, int k)
{
    int j;
    while(2*k<=count[a])
    {
        j=2*k;
        if(a==left && j<count[a] && heap[a][j]<heap[a][j+1]) j++;
        else if(j<count[a] && heap[a][j]>heap[a][j+1]) j++;

        if(a==left && heap[a][k]>=heap[a][j])break;
        else if(heap[a][k]<=heap[a][j])break;

        swap(a,j,k);
        k=j;
    }
}

int del(int a)
{
    swap(a,1,count[a]--);
    sink(a,1);
    return heap[a][count[a]+1];
}

void insert(int a, int ele)
{
    heap[a][++count[a]]=ele;
    swim(a, count[a]);
}

void print()
{
    int i;
    printf(" left :- ");
    for(i=1; i<=count[0]; i++)
        printf("%d ",heap[0][i]);
    printf("\nright :- ");

    for(i=1; i<=count[1]; i++)
        printf("%d ",heap[1][i]);
    printf("\n---------\n");
}


int main()
{
    int k,n,i,j,p,m;
    median=count[0]=count[1]=0;
    scanf("%d",&n);
    for(i=0; i<n; i++)
    {
        scanf("%d",&p);
        if(p<=median)
            insert(left, p);
        else
            insert(right, p);

        //print();

        if(count[left]>count[right]+1)
            insert(right,del(left));
        else if(count[right]>count[left]+1)
            insert(left,del(right));

        //scanf("%d",&j);
        //if(j)
        //print();

        if(count[left]>count[right])
            median=heap[left][1];
        else if(count[left]<count[right])
            median=heap[right][1];
        else
            median=(double)(heap[right][1]+heap[left][1])/2.0;

        printf("%.1f ",median);
    }
    return 0;
}
