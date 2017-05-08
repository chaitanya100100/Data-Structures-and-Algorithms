#include<stdio.h>
#include<stdlib.h>

struct node
{
	int v;
	struct node* next;
};
typedef struct node node;

int* visited;
int* com;
node** adj;
int V,E,count=0;

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
	com[v]=count;
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
	int j,u,v,i;

	scanf("%d %d",&V,&E);
	adj = malloc(V*sizeof(node*));
	visited = (int*)malloc(V*sizeof(int));
	com = (int*)malloc(V*sizeof(int));

	for(i=0; i<V; i++)
	{
		visited[i]=0;
		adj[i]=NULL;
	}

	for(i=0; i<E; i++)
	{
		scanf("%d %d",&u,&v);
		add(&adj[u-1],v-1);
		add(&adj[v-1],u-1);
	}

	/*for(i=0; i<V; i++)
	{
		printf("%d : ",i);
		printList(adj[i]);
	}*/

	//printf("Running\n");

	for(i=0; i<V; i++)
	if(!visited[i])
	{
		dfs(i);
		count++;
	}
	//printf("Running\n");

	printf("%d components\n",count);

	for(i=0; i<count; i++)
	{
		for(j=0; j<V; j++)
		if(com[j]==i)
			printf("%d ",j);
		printf("\n");
	}

	return 0;
}
