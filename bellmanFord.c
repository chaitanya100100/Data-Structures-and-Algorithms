#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

struct node
{
	int u,v,w;
};
typedef struct node node;

int special[1005],ans[1005][1005];
node arr[100005];


int main()
{
	int u,v,w,i,j,k,V,E,K;
	
	scanf("%d%d%d",&V,&E,&K);
	for(i=0; i<K; i++)
	{
		scanf("%d",&special[i]);
		special[i]--;
	}
	for(i=0; i<E; i++)
	{
		scanf("%d%d%d",&arr[i].u,&arr[i].v,&arr[i].w);	
		arr[i].u--;
		arr[i].v--;
	}

	for(i=0; i<K; i++)
		for(j=0; j<V; j++)
			ans[i][j]=INT_MAX;
	for(i=0; i<K; i++)
		ans[i][special[i]]=0;

	for(i=0; i<K; i++)
	{
		for(k=0; k<V; k++){
		for(j=0; j<E; j++)
		{
			u=arr[j].u;		
			v=arr[j].v;		
			w=arr[j].w;
			if(ans[i][u]!=INT_MAX && ans[i][u]+w<ans[i][v])
				ans[i][v] = ans[i][u]+w;
		}
		}
	}
	int min=INT_MAX;
	for(i=0; i<K; i++)
		for(j=0; j<K; j++)
		{
			if(i!=j && ans[i][special[j]]<min)
				min = ans[i][special[j]];
		}
	printf("%d\n",min);
	return 0;
}
