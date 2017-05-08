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
int* com;
node** adj;
node** revadj;
int V,E,count=0, num=0;

void dfsTS(int v)
{
	visited[v]=1;
	node* cur = adj[v];
	while(cur!=NULL)
	{
		if(!visited[cur->v])
			dfsTS(cur->v);
		cur=cur->next;
	}
	TS[--count]=v;
}

int dfs(int v, int i)
{
	int x=i;
	visited[v]=1;
	node* cur = revadj[v];
	while(cur!=NULL)
	{
		if(!visited[cur->v])
		{
			if(cur->v<i)i=cur->v;
			x=dfs(cur->v,i);
		}
		cur=cur->next;
	}
	com[v]=x;
	return x;
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
	revadj = malloc(V*sizeof(node*));
	visited = (int*)malloc(V*sizeof(int));
	TS = (int*)malloc(V*sizeof(int));
	com = (int*)malloc(V*sizeof(int));
	count=V;

	for(i=0; i<V; i++)
	{
		visited[i]=0;
		adj[i]=NULL;
		revadj[i]=NULL;
	}

	for(i=0; i<E; i++)
	{
		scanf("%d %d",&u,&v);
		add(&adj[u],v);
		add(&revadj[v],u);
	}

	for(i=0; i<V; i++)
		visited[i]=0;
	for(i=0; i<V; i++)
		if(!visited[i])
			dfsTS(i);
	
//	for(i=0; i<V; i++)
//		printf("%d ",TS[i]);


	for(i=0; i<V; i++)
		visited[i]=0;
	for(i=0; i<V; i++)
	{
		if(!visited[TS[i]])
		{
			dfs(TS[i], TS[i]);			
		}
	}
	for(i=0; i<V; i++)
		printf("%d\n",com[i]);

	return 0;
}
