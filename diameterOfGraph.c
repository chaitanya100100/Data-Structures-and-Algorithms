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
int V,E,ans=0;

int dfs(int v)
{
    int m1=0,a,m2=0;
	visited[v]=1;
	node* cur = adj[v];
	while(cur!=NULL)
	{
		if(!visited[cur->v])
        {
            a=dfs(cur->v);
            if(a>m1)m1=a;
            else if(a>m2)m2=a;
        }
		cur=cur->next;
	}
	if(m1+m2+1>ans)ans=m1+m2+1;
	return m1+1;
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

	dfs(0);
	printf("%d\n",ans);

	return 0;
}
