#include<stdio.h>
#include<stdlib.h>

struct node
{
	int v;
	struct node* next;
};
typedef struct node node;

int* visited;
int* TS;
node** adj;
int V,E,count;

void dfs(int v)
{
	visited[v]=1;
	node* cur = adj[v];
	while(cur!=NULL)
	{
		if(!visited[cur->v])
			dfs(cur->v);
		cur=cur->next;
	}
	TS[--count]=v;
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
	TS = (int*)malloc(V*sizeof(int));
	count=V;

	for(i=0; i<V; i++)
	{
		visited[i]=0;
		adj[i]=NULL;
	}

	for(i=0; i<E; i++)
	{
		scanf("%d %d",&u,&v);
		add(&adj[u-1],v-1);
		//add(&adj[v-1],u-1);
	}

	for(i=0; i<V; i++)
		visited[i]=0;
	for(i=0; i<V; i++)
		if(!visited[i])
			dfs(i);
	for(i=0; i<V; i++)
		printf("%d ",TS[i]+1);
	printf("\n");
	return 0;
}
