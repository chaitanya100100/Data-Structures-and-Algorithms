#include<stdio.h>

int partition(int arr[], int l, int r)
{
    int p=l,pi=arr[l];
    int i=l,j=r+1;
    int t;

    while(1)
    {
        while(arr[++i]<pi)
            if(i==r)break;
        while(arr[--j]>pi)
            if(j==l)break;
        if(i>=j)break;

        t=arr[i];
        arr[i]=arr[j];
        arr[j]=t;
    }
    arr[l]=arr[j];
    arr[j]=pi;
    //printf("%d done\n",pi);
    return j;
}

void quickSort(int arr[], int l, int r)
{
    if(l<r)
    {
        int m = partition(arr, l, r);
        quickSort(arr, l, m-1);
        quickSort(arr, m+1, r);
    }
}

int select(int arr[], int l, int r, int k)
{
    int m;
    while(l<r)
    {
        m = partition(arr, l, r);
        if(m<k)l=m+1;
        else if(m>k)r=m-1;
        else return arr[k];
    }
    return arr[k];
}

int main()
{
    int i,arr[]={1,9,2,6,5,9,3,-2,6,4,5,1,6,7,3,3,4,-8,5,12,7};
    quickSort(arr,0,20);
    for(i=0; i<21; i++)
        printf("%d ",arr[i]);
    printf("\n\n");
    while(1)
    {
        printf("which element : ");
        int arr1[]={1,9,2,6,5,9,3,-2,6,4,5,1,6,7,3,3,4,-8,5,12,7};
        scanf("%d",&i);
        printf("%d\n",select(arr1,0,20,i));
    }
    return 0;
}
