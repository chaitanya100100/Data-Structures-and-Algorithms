#include<stdio.h>
#include<stdlib.h>

struct node
{
	int v;
	struct node* next;
};
typedef struct node node;

int* visited;
node** adj;
int V,E,ans=0,maxLevel=0;

void dfs(int v, int l)
{
	visited[v]=1;
	node* cur = adj[v];
	while(cur!=NULL)
	{
		if(!visited[cur->v])
        {
            dfs(cur->v,l+1);
        }
		cur=cur->next;
	}
	if(l>maxLevel){maxLevel=l;ans=v;}
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

	dfs(0,0);

    for(i=0; i<V; i++)
		visited[i]=0;

    dfs(ans,0);
    printf("%d\n",maxLevel);

	return 0;
}
