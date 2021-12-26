#include<stdio.h>
#include<limits.h>

int N,arr[100005],pq[100005],qp[100005];

void swap(int a, int b)
{
    int t;
    t=pq[a];
    pq[a]=pq[b];
    pq[b]=t;
    qp[pq[a]] = a;
    qp[pq[b]] = b;
}

void swim(int k)
{
    while(k>1 && arr[pq[k]]>arr[pq[k/2]])
    {
        swap(k,k/2);
        k=k/2;
    }
}

void sink(int k)
{
    int j;
    while(2*k<=N)
    {
        j=2*k;
        if(j<N && arr[pq[j]]<arr[pq[j+1]])j++;
        if(arr[pq[j]]<=arr[pq[k]])break;
        swap(j,k);
        k=j;
    }
}

void insert(int i)
{
    pq[++N]=i;
    qp[i]=N;
    swim(N);
    /*int b;
    for(b=1; b<=N; b++)
        printf("%d ",arr[pq[b]]);
    printf("\n");*/
}

void del(int i)
{
    int b = qp[i];
    swap(qp[i],N);
    N--;
    sink(b);

    /*for(b=1; b<=N; b++)
        printf("%d ",arr[pq[b]]);
    printf("\n");*/
}

int main()
{
    int t,i,n,j,w,p,max;
    scanf("%d",&t);
    while(t--)
    {
        N=0;
        scanf("%d%d",&n,&w);
        for(i=0; i<n; i++)
            scanf("%d",&arr[i]);
        max=0;
        for(i=0; i<w; i++)
        {
            insert(i);
            if(arr[i]>arr[max])
                max=i;
        }
        printf("%d ",arr[max]);
        for(j=0;i<n;i++,j++)
        {
            del(j);
            insert(i);
            printf("%d ",arr[pq[1]]);
        }
        printf("\n");
    }
    return 0;
}
