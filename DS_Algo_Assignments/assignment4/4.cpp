#include<bits/stdc++.h>
#define PB push_back
#define MP make_pair
#define ll long long
using namespace std;

int n;
vector< pair<int,int> > adj[200005];
int visited[200005];
ll ans[200005];

void initialize()
{
	int i;
	for(i=0; i<=n; i++)
	{
		visited[i]=0;
		adj[i].clear();
	}
}

int dfs(int s, int e)
{
	int a=0;
	visited[s]=1;
	for(vector< pair<int,int> >::iterator it=adj[s].begin(); it!=adj[s].end(); it++)
	{
		if(!visited[it->first])
			a += dfs(it->first, it->second);		
	}
	ans[e]=((ll)(a+1))*((ll)(n-a-1));
	return a+1;
}

int main()
{
	int t,i,j,k,u,v;
	cin >> t;
	while(t--)
	{
		cin >> n;
		initialize();
		for(i=1; i<n; i++)
		{
			scanf("%d%d",&u,&v);
			adj[u].PB(MP(v,i));
			adj[v].PB(MP(u,i));
		}
		k = dfs(1, 0);
		for(i=1; i<n; i++)
			printf("%lld ",ans[i]);
		printf("\n");
	}
	return 0;
}
