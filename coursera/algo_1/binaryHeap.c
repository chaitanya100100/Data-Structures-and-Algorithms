#include<stdio.h>

int n,pq[100005];

void swap(int a, int b)
{
    int t=pq[a];
    pq[a]=pq[b];
    pq[b]=t;
}
void printPriorityQueue()
{
    int i;
    for(i=1; i<=n; i++)
        printf("%d ",pq[i]);
    printf("\n");
}

void sink(int k)
{
    int j;
    while(2*k<=n)
    {
        j=2*k;
        if(j<n && pq[j]<pq[j+1])j++;
        if(pq[k]>=pq[j])break;
        swap(k,j);
        k=j;
    }
}
void delMax()
{
    if(n==0)
    {
        printf("Empty\n");
        return;
    }
    swap(1,n);
    pq[n]=0;
    n--;
    sink(1);
}

void swim(int k)
{
    while(k>1 && pq[k]>pq[k/2])
    {
        swap(k,k/2);
        k=k/2;
    }
}
void insert(int t)
{
    pq[++n]=t;
    swim(n);
}

void createHeap()
{
    int i=n/2;
    while(i>=1)
    {
        sink(i);
        i--;
    }
    /*int i = 1;
    while(i<=n)
    {
        swim(i);
        i++;
    }*/
    //printPriorityQueue();
}

void heapSort()
{
    while(n>1)
    {
        swap(1,n--);
        sink(1);
    }
}

int main()
{
    int t=1,i,j;
    n=0;

    /*scanf("%d",&t);
    while(t--)
        scanf("%d",&pq[++n]);*/
    for(i=0; i<100000; i++)
        pq[++n]=rand();
    printf("%d\n",pq[n]);
    /*for(i=1; i<=n; i++)
    for(j=1; j<=n-i; j++)
    {
        if(pq[j]>pq[j+1])
            swap(j,j+1);
    }*/

    createHeap();
    //printPriorityQueue();
    i=n;
    heapSort();
    n=i;
    for(i=1000; i<1100; i++)
        printf("%d ",pq[i]);
    //printPriorityQueue();
    //for(i=0; i<100000000; i++)
     //   insert(rand()%100000000);
    /*n=0;
    scanf("%d",&t);
    while(t!=-1)
    {
        insert(t);
        printPriorityQueue();
        scanf("%d",&t);
    }*/
    /*scanf("%d",&t);
    while(t!=-1)
    {
        delMax();
        printPriorityQueue();
        scanf("%d",&t);
    }*/

    return 0;
}
