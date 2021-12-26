#include<iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;

//int n,arr[1000000];

void swap(int* a, int* b)
{
    int temp=*a;
    *a=*b;
    *b=temp;
}

int partition(int arr[], int l, int r)
{
    int pivot=arr[l],i=l+1,j=r;

    while(i<=j)
    {
        while(arr[i]<pivot)i++;
        while(arr[j]>pivot)j--;
        if(i>j)break;
        swap(&arr[i],&arr[j]);
        i++;
        j--;
    }
    swap(&arr[l],&arr[j]);
    return j;
}

void quickSort(int arr[], int l, int r)
{
    if(l>=r)
        return;
    int j = partition(arr, l, r);
    quickSort(arr, l, j-1);
    quickSort(arr, j+1, r);
}

void bubbleSort(int arr[], int n)
{
    for(int i=0; i<n-1; i++)
    for(int j=0; j<n-1-i; j++)
    if(arr[j]>arr[j+1])
    swap(&arr[j],&arr[j+1]);
}

int main()
{
    int n=1000,arr[1005];
    //int n,arr[100];
    //cin >> n;

    //for(int i=0; i<n; i++)
    //    arr[i] = rand();

    //for(int i=0; i<n; i++)
    //    cin >> arr[i];

    FILE* ptr = fopen("test.txt","r");
    for(int i=0; i<n; i++)
        fscanf(ptr,"%d",&arr[i]);

    quickSort(arr, 0, n-1);
    //bubbleSort(arr, n);

    //cout << arr[373] << endl;
    for(int i=0; i<n; i++)
        cout << arr[i] << " ";
    cout << endl;
    return 0;
}
