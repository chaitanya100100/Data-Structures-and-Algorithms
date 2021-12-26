#include<stdio.h>

void swap(int *a, int *b)
{
	int t=*a;
	*a=*b;
	*b=t;
}

int partition(int arr[], int l, int r)
{
	int i=l+1,j=r,pivot=arr[l];
	while(i<=j)
	{
		while(arr[i]<pivot)i++;
		while(arr[j]>pivot)j--;
		if(i>=j)break;
		swap(&arr[i],&arr[j]);
		i++;
		j--;
	}
	swap(&arr[j],&arr[l]);
	return j;
}

void quickSort(int arr[], int l, int r)
{
	if(l<r)
	{
		int pivot = partition(arr, l, r);
		quickSort(arr, l, pivot-1);
		quickSort(arr, pivot+1, r);
	}
}

int main()
{
	int i,n,arr[100];
	scanf("%d",&n);
	for(i=0; i<n; i++)
		scanf("%d",&arr[i]);
	quickSort(arr,0,n-1);
	for(i=0; i<n; i++)
		printf("%d ",arr[i]);
	printf("\n");
	return 0;
}
