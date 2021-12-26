#include<stdio.h>
#include<stdlib.h>
#define ll long long

int n,arr[100005],sort[100005],uf[100005], size[100005], ans[100005];

void merge(int sort[], int l, int m, int r)
{
    int i,j,k,n1=(m-l+1),n2=(r-m);
    int a1[n1],a2[n2];

    for(i=0; i<n1; i++)
        a1[i]=sort[l+i];
    for(j=0; j<n2; j++)
        a2[j]=sort[m+1+j];

    i=j=0;k=l;
    while(i<n1 && j<n2)
    {
        if(arr[a1[i]]>arr[a2[j]])
            sort[k++]=a1[i++];
        else
            sort[k++]=a2[j++];
    }
    while(i<n1)
        sort[k++]=a1[i++];
    while(j<n2)
        sort[k++]=a2[j++];
}

void mergeSort(int sort[], int l, int r)
{
    if(l<r)
    {
        int m = (r-l)/2+l;
        mergeSort(sort, l, m);
        mergeSort(sort, m+1, r);
        merge(sort, l, m, r);
    }
}

int root(int a)
{
    while(uf[a] != a)
    {
        uf[a] = uf[uf[a]];
        a = uf[a];
    }
    return a;
}

void mkunion(int p, int q)
{
    int a = root(p);
    int b = root(q);
    uf[b] = a;
    size[a] = size[a] + size[b];
}

int main()
{
    int t,i,j,k,till,ele,ind;
    scanf("%d",&t);
    while(t--)
    {
        for(i=0; i<100005; i++)
        {
            uf[i] = i;
            size[i] = 0;
            sort[i] = i;
        }
        scanf("%d",&n);
        for(i=0; i<n; i++)
            scanf("%d",&arr[i]);

        mergeSort(sort, 0, n-1);

        /*for(i=0; i<n; i++)
            printf("%d ",sort[i]);
        printf("\n");*/

        till=2;
        ans[1] = sort[0];
        size[sort[0]] = 1;

        for(i=1; i<n; i++)
        {
            ind = sort[i];
            size[ind] = 1;
            if(ind!=0 && size[ind-1]!=0)
            {
                mkunion(ind, ind-1);
                j=size[root(ind)];
                for(; till<=j; till++)
                    ans[till]=ind;
            }
            if(ind!=n-1 && size[ind+1]!=0)
            {
                mkunion(ind, ind+1);
                j=size[root(ind)];
                for(; till<=j; till++)
                    ans[till]=ind;
            }
        }
        for(i=1; i<=n; i++)
            printf("%d ",arr[ans[i]]);
        printf("\n");
    }
    return 0;
}
