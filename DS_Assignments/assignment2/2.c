#include<stdio.h>
#define MAX (100000)
int arr[100005];

void merge(int arr[], int l, int m, int r)
{
    int i,j,k,n1=(m-l+1),n2=(r-m);
    int a1[n1],a2[n2];

    for(i=0; i<n1; i++)
        a1[i]=arr[l+i];
    for(j=0; j<n2; j++)
        a2[j]=arr[m+j+1];
    i=j=0;
    k=l;
    while(i<n1 && j<n2)
    {
        if(a1[i]<a2[j])
            arr[k++]=a1[i++];
        else
            arr[k++]=a2[j++];
    }
    while(i<n1)
        arr[k++]=a1[i++];
    while(j<n2)
        arr[k++]=a2[j++];
}

void mergeSort(int arr[], int l, int r)
{
    if(l<r)
    {
        int m=(r-l)/2+l;
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
        merge(arr, l, m, r);
    }
}

int main()
{
    int ans,sum,t,i,n,j,k;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        for(i=1; i<=n; i++)
            scanf("%d",&arr[i]);
        mergeSort(arr, 1, n);
        ans=0;
        for(i=1; i<=n; i++)
        {
            if(n-i+1<=arr[i])
            {
                ans=n-i+1;
                break;
                //printf("ans=%d\n",ans);
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
