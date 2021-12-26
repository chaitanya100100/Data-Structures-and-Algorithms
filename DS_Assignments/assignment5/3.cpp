#include<bits/stdc++.h>
using namespace std;

int N,Q;
struct node
{
	int v;
	int value;
	int ans;
};
node arr[500005];
int visited[500005];
vector<node*> adj[500005];
int pp,jj;

int dfs(int i)
{
	visited[i]=1;
	node* l;
	int ans=arr[i].value;
	for(vector<node*>::iterator it=adj[i].begin(); it != adj[i].end(); it++)
	{
		l=*it;	
		if(!visited[l->v])
			ans = min(ans, dfs(l->v));
	}
	arr[i].ans = ans;
	return ans;
}

int dfs2(int i, int u, int p)
{
	if(i==u)
	{
		jj=0;
		return arr[i].ans;
	}
	node* l;
	int ans=arr[i].ans;
	int old=ans;
	for(vector<node*>::iterator it=adj[i].begin(); pp && jj && it != adj[i].end(); it++)
	{
		l=*it;
		if(l->v != p)
		{
			ans=min(ans, dfs2(l->v, u, i) );
		}
	}
	if(old==ans && !jj)pp=0;
	arr[i].ans=ans;
	return ans;
}

int main()
{
	int u,v,i,j,k;
	cin >> N >> Q;
	for(i=0; i<N; i++)
	{
		arr[i].v=i;
		adj[i].clear();
		visited[i]=0;
	}
	for(i=0; i<N-1; i++)
	{
		scanf("%d%d",&u,&v);
		u--;v--;
		adj[u].push_back(&arr[v]);			
		adj[v].push_back(&arr[u]);			
	}
	for(i=0; i<N; i++)
		scanf("%d",&(arr[i].value));
	dfs(0);
	while(Q--)
	{
		scanf("%d%d",&k,&u);
		if(k==0)
		{
			scanf("%d",&v);
			if(arr[u-1].value > v)
			{
				arr[u-1].value = v;
				if(arr[u-1].ans > v)
				{
					jj=pp=1;
					arr[u-1].ans = v;
					dfs2(0,u-1,-1);
				}
			}
			//for(i=0; i<N; i++)
			//	printf("%d ",arr[i].ans);
			//printf("\n");
		}
		else
		{
			printf("%d\n",arr[u-1].ans);
		}
	}

}
