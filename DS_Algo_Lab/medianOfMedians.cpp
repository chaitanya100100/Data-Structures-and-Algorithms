#include<iostream>
#include<bits/stdc++.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
using namespace std;

void swap(int* a, int* b)
{
    int temp=*a;
    *a=*b;
    *b=temp;
}

int _sort(int arr[], int n)
{
    /*for(int i=0; i<n-1; i++)
    for(int j=0; j<n-1-i; j++)
    if(arr[l+j]>arr[l+j+1])
        swap(&arr[l+j], &arr[l+j+1]);*/
    sort(arr,arr+n);
    return arr[n/2];
}

/*int partition(int arr[], int l, int r, int pivot)
{
    int i,j;
    for(i=l; i<r; i++)
    if(arr[i]==pivot)
        break;

    swap(&arr[i],&arr[r]);
    i=l;

    for(j=l; j<r; j++)
    if(arr[j]<=pivot)
    {
        swap(&arr[i],&arr[j]);
        i++;
    }
    swap(&arr[i],&arr[r]);
    return i;
}*/

int partition(int arr[], int l, int r, int pivot)
{
    int i=l+1,j=r;

    for(int a=l; a<=r; a++)
    if(arr[a]==pivot)
    {
        swap(&arr[l],&arr[a]);
        break;
    }

    while(i<=j)
    {
        while(arr[i]<pivot)i++;
        while(arr[j]>pivot)j--;
        if(i>j)
            break;
        swap(&arr[i],&arr[j]);
        i++;
        j--;
    }
    swap(&arr[j],&arr[l]);
    return j;
}

int kthsmallest(int arr[], int l, int r, int k)
{
    /*if(l==r)
        return arr[l];*/

    int n = r-l+1, m=n/5,i,j;
    int c = ceil(double(n)/5.0);
    int median[c];

    for(i=0; i<m; i++)
        median[i] = _sort(arr+l+5*i, 5);
    if(5*i<n)
    {
        median[i] = _sort(arr+l+5*i, n%5);
        i++;
    }
    int pivot;
    if(i==1)pivot=median[0];
    else pivot = kthsmallest(median, 0, i-1, i/2);

    int pos = partition(arr, l, r, pivot);
    if(pos-l==k-1)return arr[pos];
    else if(pos-l>k-1) return kthsmallest(arr, l, pos-1, k);
    else return kthsmallest(arr, pos+1, r, l+k-pos-1);
}

int main()
{
    //int n=1000,arr[1005],i,j=374;
    //FILE* ptr = fopen("test.txt","r");
    //for(int i=0; i<n; i++)
    //    fscanf(ptr,"%d",&arr[i]);

    int j,arr[100],n;
    cin >> n;

    for(int i=0; i<n; i++)
        cin >> arr[i];
    cin >> j;

    cout << kthsmallest(arr, 0, n-1, j) << endl;
    return 0;
}
