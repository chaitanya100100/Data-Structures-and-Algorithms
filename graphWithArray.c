#include<stdio.h>
#include<stdlib.h>

int** adj;
int* visited;
int* count;
int* com;
int V,E,num=0;
int input[1000];


void dfs(int u)
{
	int i;
	visited[u]=1;
	com[u]=num;
	for(i=0; i<count[u]; i++)
	{
		if(!visited[adj[u][i]])
			dfs(adj[u][i]);
	}
}

int main()
{
	int i,j,u,v;
	scanf("%d %d",&V,&E);
	adj = (int**)malloc(V*sizeof(int*));
	count = (int*)malloc(V*sizeof(int));
	com = (int*)malloc(V*sizeof(int));

	for(i=0; i<V; i++)
		count[i]=0;
	for(i=0,j=0; i<E; i++)
	{
		scanf("%d %d",&input[j++],&input[j++]);
		count[--input[j-2]]++;
		count[--input[j-1]]++;
	}
	//printf("hi\n\n");
	for(i=0; i<V; i++)
		adj[i] = (int*)malloc(sizeof(int)*count[i]);
	//printf("hi\n\n");
	for(i=0; i<V; i++)
		count[i]=0;
	//printf("hi\n\n");
	for(i=0,j=0; i<E; i++,j+=2)
	{
		*(*(adj+input[j])+count[j])=input[j+1];
		count[j]++;
		*(*(adj+input[j+1])+count[j+1])=input[j];
		count[j+1]++;
	}
	printf("hi\n\n");

	for(i=0; i<V; i++)
		visited[i]=0;
	for(i=0; i<V; i++)
		if(!visited[i])
		{
			dfs(i);
			num++;
		}

	printf("%d components\n",num);
	for(i=0; i<num; i++)
	{
		for(j=0; j<V; j++)
		{
			if(com[j]==i)
				printf("%d ",j);
		}
		printf("\n");
	}

	return 0;
}
