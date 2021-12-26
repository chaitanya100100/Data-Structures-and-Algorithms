#include<bits/stdc++.h>
using namespace std;

#define PB push_back

int V;
vector<int> adj[200005];
int visited[200005];
int arr[200005];

void initialize()
{
	int i;
	for(i=0; i<V; i++)
	{
		adj[i].clear();
		visited[i]=0;
	}
}

int dfs(int s, int t)
{
	visited[s]=1;
	int ans=arr[s];
	if(ans!=-1)
		return ans;
	
	if(t)
		ans=INT_MAX;
	else
		ans=INT_MIN;
	
	for(vector<int>::iterator it=adj[s].begin(); it!=adj[s].end(); it++)
	{
		if(!visited[*it])
		{
			if(t)
				ans = min(ans, dfs(*it, !t) );
			else
				ans = max(ans, dfs(*it, !t) );
		}
	}
	return ans;
}

int main()
{
	int t,i,j,k,u,v;
	cin >> t;
	while(t--)
	{
		cin >> V;
		initialize();
		for(i=0; i<V-1; i++)
		{
			scanf("%d%d",&u,&v);
			u--;v--;
			adj[u].PB(v);
			adj[v].PB(u);
		}
		for(i=0; i<V; i++)
			scanf("%d",&arr[i]);

		cout << dfs(0, 0) << endl;
	}
	return 0;
}
