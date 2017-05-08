#include<stdio.h>

void swap(int* a, int *b)
{
	int t=*a;
	*a=*b;
	*b=t;
}

int partition(int arr[], int l, int r)
{
	int i=l+1,j=r,p=arr[l];

	while(i<=j)
	{
		while(arr[i]<p)i++;
		while(arr[j]>p)j--;
		if(i>=j)
			break;
		swap(&arr[i], &arr[j]);
		i++;
		j--;
	}
	swap(&arr[j],&arr[l]);
	return j;
}

void quickSelect(int arr[], int l, int r, int k)
{
	if(l<r)
	{
		int pivot = partition(arr, l, r);
		quickSelect(arr, l, pivot-1, k);
		if(k-1>pivot)
		quickSelect(arr, pivot+1, r, k);
	}
}

int main()
{
	int n=100000,arr[100005],i,j=15,k;
	//scanf("%d",&n);
	for(i=0; i<n; i++)
		scanf("%d",&arr[i]);
	scanf("%d",&j);
	quickSelect(arr, 0, n-1, j);
	for(i=0; i<j; i++)
		printf("%d ",arr[i]);
	printf("\n");
	return 0;
}
