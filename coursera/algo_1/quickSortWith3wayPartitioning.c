#include<stdio.h>

void swap(int * a, int * b)
{
    int t;
    t=*a;
    *a=*b;
    *b=t;
}

void printArray(int arr[], int l, int r)
{
    int i;
    for(i=l; i<=r; i++)
        printf("%d ",arr[i]);
    printf("\n");
}

void quickSortWith3WayPartitioning(int arr[], int l, int r)
{
    if(r<=l)return;

    int i,lt,gt,pi;
    i=lt=l;
    gt=r;
    pi=arr[l];

    while(i<=gt)
    {
        if(arr[i]>pi) swap(&arr[i],&arr[gt--]);
        else if(arr[i]<pi) swap(&arr[lt++],&arr[i++]);
        else i++;
    }
    printArray(arr, 0, 13);
    quickSortWith3WayPartitioning(arr,l,lt-1);
    quickSortWith3WayPartitioning(arr,gt+1,r);
}

int main()
{
    int arr[]={2,4,2,3,5,2,1,3,2,4,3,5,2,1};
    quickSort(arr,0,13);
    printArray(arr,0,13);
    return 0;
}
