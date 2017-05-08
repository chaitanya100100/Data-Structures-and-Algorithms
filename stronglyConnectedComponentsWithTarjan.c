#include<stdio.h>
#include<stdlib.h>

struct node
{
	int v;
	struct node* next;
};
typedef struct node node;

int T=0;
int* visited;
int* lis;
node** adj;
int V,E,count=0;
int* arr;

void dfs(int v)
{
	visited[v]=1;
	lis[v]=T++;
	int temp = lis[v];
	node* cur = adj[v];
	while(cur!=NULL)
	{
		if(visited[cur->v] == 0)
		{
			dfs(cur->v);
			if(lis[cur->v]<lis[v])
				lis[v]=lis[cur->v];
		}
		if(lis[cur->v]<lis[v] && visited[cur->v]!=2)
			lis[v]=lis[cur->v];
		cur=cur->next;
	}
	if(lis[v]==temp)
		arr[count++]=v;
	visited[v] = 2;
}

void add(node** root, int a)
{
	node* pnew = malloc(sizeof(node));
	pnew->next=*root;
	pnew->v=a;
	*root=pnew;
}


void printList(node* root)
{
	node* cur=root;
	while(cur!=NULL)
	{
		printf("%d ",cur->v);
		cur=cur->next;
	}
	printf("\n");
}

int main()
{
	int flag,j,u,v,i;

	scanf("%d %d",&V,&E);
	adj = malloc(V*sizeof(node*));
	visited = (int*)malloc(V*sizeof(int));
	lis = (int*)malloc(V*sizeof(int));
	arr = (int*)malloc(V*sizeof(int));

	for(i=0; i<V; i++)
	{
		visited[i]=0;
		adj[i]=NULL;
	}

	for(i=0; i<E; i++)
	{
		scanf("%d %d",&u,&v);
		add(&adj[u],v);
		//add(&adj[v-1],u-1);
	}

	for(i=0; i<V; i++)
		visited[i]=0;
	for(i=0; i<V; i++)
		if(!visited[i])
			dfs(i);

	for(i=0; i<V; i++)
		printf("%d\n",lis[i]);
	
	return 0;
}
