#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int power(int x, int y)
{
    int a=1;
    while(y)
    {
        if(y&1)
            a=a*x;
        x=x*x;
        y=y/2;
    }
    return a;
}

int min(int a, int b)
{
    if(a<b) return a;
    else    return b;
}

struct Node
{
    int l;
    int r;
    int data;
};
typedef struct Node Node;

Node arr[100];
int n;

void generateSegTree()
{
    int i,j,k,p;

    p = (int)(log(n)/log(2));
    p = power(2,p);
    j = n-p;
    for(i=2*(n-j), k=1; i<2*n; i++, k++)
    {
        scanf("%d",&(arr[i].data));
        arr[i].l=arr[i].r=k;
    }
    for(i=n; i<2*(n-j); i++,k++)
    {
        scanf("%d",&(arr[i].data));
        arr[i].l=arr[i].r=k;
    }
    for(i=n-1; i>=1; i--)
    {
        arr[i].l = arr[2*i].l;
        arr[i].r = arr[2*i+1].r;
        arr[i].data = min(arr[2*i].data, arr[2*i+1].data);
    }
}

void printSegTree()
{
    int i;
    for(i=1; i<2*n; i++)
        printf("%d %d -> %d\n", arr[i].l, arr[i].r, arr[i].data);
    printf("\n");
}

int getAns(int l, int r, int k)
{
    int left = arr[k].l;
    int right = arr[k].r;

    if(l==left && right==r)
        return arr[k].data;
    int mid = arr[2*k].r;

    if(l > mid)
        return getAns(l, r, 2*k+1);
    else if(r<=mid)
        return getAns(l, r, 2*k);
    else
        return min( getAns(l, mid, 2*k), getAns(mid+1, r, 2*k+1));
}

int main()
{
    int l, r;
    scanf("%d",&n);
    generateSegTree();
    printSegTree();

    while(1)
    {
        scanf("%d%d",&l,&r);
        printf("%d\n",getAns(l, r, 1));
    }

    return 0;
}
