#include<stdio.h>
int arr[100005];

void swap(int *a, int *b)
{
	int t=*a;
	*a=*b;
	*b=t;
}

int sort(int arr[], int l, int n)
{
	int i,j;
	for(i=0; i<n-1; i++)
	for(j=0; j<n-1-i; j++)
		if(arr[l+j]>arr[l+j+1])
			swap(&arr[l+j],&arr[l+j+1]);
	return arr[l+n/2];
}

int partition(int arr[], int l, int r, int p)
{
	int i,j;
	for(i=l; i<=r; i++)
	if(arr[i]==p)
	{
		swap(&arr[l], &arr[i]);
		break;
	}
	i=l+1;
	j=r;

	while(i<=j)
	{
		while(arr[i]<p)i++;
		while(arr[j]>p)j--;
		if(i>=j)break;
		swap(&arr[i],&arr[j]);
		i++;
		j--;
	}
	swap(&arr[l],&arr[j]);
	return j;
}

int fairPivot(int arr[], int l, int r)
{
	int n=r-l+1;
	int i,j,m=n/5,c=(n+4)/5;
	int median[c];

	for(i=0; i<m; i++)
		median[i] = sort(arr, l+5*i, 5);
	if(i==c-1)
	{
		median[i] = sort(arr, l+5*i, n%5);
		i++;
	}
	int p;
	if(i==1) p = 0;
	else p = fairPivot(median, 0, i-1);
	
	return partition(arr, l, r, p);

	/*if(pos-l==k-1)
		return arr[pos];
	else if(pos-l > k-1)
		return kthsmallest(arr, l, pos-1, k);
	else
		return kthsmallest(arr, pos+1, r, k+l-pos-1);
	*/
}

void quickSort(int arr[], int l, int r)
{
	if(l<r)
	{
		int p = fairPivot(arr, l, r);
		printf("%d %d %d\n",l,r,p);
		quickSort(arr, l, p-1);
		quickSort(arr, p+1, r);
	}
}

int main()
{
	//scanf("%d",&n);
	int i,j,k,n;	
	n=100000;
	for(i=0; i<n; i++)
		arr[i] = i;
	//scanf("%d",&j);
	quickSort(arr, 0, n-1);
	
	return 0;
}
