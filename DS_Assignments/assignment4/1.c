#include<stdio.h>
int arr[100005];

int ceil_(int a)
{
	if(a%2==1)
		return a/2+1;
	else
		return a/2;
}

int mycmp(void const* a, void const* b)
{
	return *(int*)a - *(int*)b;
}

int main()
{
	int e,max,cur,t,n,i,j,k;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		for(i=0; i<n; i++)
			scanf("%d",&arr[i]);
		qsort(arr, n, sizeof(int), mycmp);
		max=0;e=-1;
		for(i=0; i<n; i++)
		{
			if(e==arr[i])
				cur++;
			else
			{
				cur=1;
				e=arr[i];
			}
			if(max<cur)
				max=cur;
		}
		int a=ceil_(n),ans;
		if(max<=a)
			ans=a;
		else
		{
			ans=(n-max);
			n = n-2*ans;
			ans+=n;
		}
		printf("%d\n",ans);
	}
	return 0;
}
