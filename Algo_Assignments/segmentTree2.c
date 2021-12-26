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

int max(int a, int b)
{
    if(a>b) return a;
    else    return b;
}


struct Node
{
    int l;
    int r;
    int ps,ss,ts;
    int pi,si;
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
        if(arr[i].data>0)
        {
            arr[i].ps=arr[i].ss = arr[i].data;
            arr[i].pi = arr[i].si = k;
        }
        else
        {
            arr[i].ps=arr[i].ss = 0;
            arr[i].pi = arr[i].si = k+1;
        }
        arr[i].ts=arr[i].ts;
    }
    for(i=n; i<2*(n-j); i++,k++)
    {
        scanf("%d",&(arr[i].data));
        arr[i].l=arr[i].r=k;
        arr[i].ps=arr[i].ss = (arr[i].data>0)?arr[i].data:0;
        arr[i].ts=arr[i].data;
    }
    for(i=n-1; i>=1; i--)
    {
        arr[i].l = arr[2*i].l;
        arr[i].r = arr[2*i+1].r;
        arr[i].data = max(max(arr[2*i].data, arr[2*i+1].data), arr[2*k].ss + arr[2*k+1].ps);

        if(arr[2*i].ps > arr[2*i].ts + arr[2*i+1].ps)
        {
            arr[i].ps = arr[2*i].ps;
            arr[i].pi = arr[2*i].pi;
        }
        else
        {
            arr[i].ps = arr[2*i].ts + arr[2*i+1].ps;
            arr[i].pi = arr[2*i+1].pi;
        }
        if(arr[2*i+1].ss > arr[2*i+1].ts + arr[2*i].ss)
        {
            arr[i].ss = arr[2*i+1].ss;
            arr[i].si = arr[2*i+1].si;
        }
        else
        {
            arr[i].ss = arr[2*i+1].ts + arr[2*i+].ss;
            arr[i].si = arr[2*i].si;
        }
        arr[i].ts = arr[2*k].ts + arr[2*k+1].ts;

    }
}

void printSegTree()
{
    int i;
    for(i=1; i<2*n; i++)
        printf("%d %d -> %d\n", arr[i].l, arr[i].r, arr[i].data);
    printf("\n");
}

int getTotal(int l, int r, int k)
{
    int left = arr[k].l;
    int right = arr[k].r;

    if(left == l && right == r)
        return arr[k].ts;
    int mid = arr[2*k].r;

    if(l > mid)
        return getTotal(l, r, 2*k+1);
    else if(r<=mid)
        return getTotal(l, r, 2*k);
    else
    {
        int a = getTotal(l, mid, 2*k);
        int b = getTotal(mid+1, r, 2*k+1);
        return a+b;
    }
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
    {
        int a = getAns(l, mid, 2*k);
        int b = getAns(mid+1, r, 2*k+1);
        int c,d;
        if(arr[2*k].si<l)
            c = getTotal(l, mid, k);
        else
            c = arr[2*k].si;
    }
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
