#include<stdio.h>
#define ll long long
#include<stdlib.h>

struct node
{
	ll u,v,w;
};
typedef struct node node;

int mycmp(const void* a, const void* b)
{
	ll p = ((node*)a)->w - ((node*)b)->w;
	return (p>0)?1:-1;
}

ll id[100005],sz[100005];
ll V,E;
node arr[500005];

ll root(ll i)
{
	while(id[i]!=i)
	{
		id[i] = id[id[i]];
		i=id[i];
	}
	return i;
}

void mkunion(ll a, ll b)
{
	ll p=root(a),q=root(b);
	if(sz[p]>sz[q])
	{
		id[q] = p;
		sz[p] += sz[q];
	}
	else
	{
		id[p] = q;
		sz[q] += sz[p];
	}
}

ll isConnected(ll a, ll b)
{
	if(root(a)==root(b))
		return 1;
	else
		return 0;
}

void initialize()
{
	ll i;
	for(i=0; i<V; i++)
	{
		id[i]=i;
		sz[i]=1;
	}	
}

int main()
{
	ll ans,u,v,w,t,i,j,k;
	scanf("%lld",&t);
	while(t--)
	{
		scanf("%lld%lld",&V,&E);
		for(i=0; i<E; i++)
		{
			scanf("%lld%lld%lld",&u,&v,&w);
			arr[i].u=u-1;
			arr[i].v=v-1;
			arr[i].w=w;
		}
		
		qsort(arr, E, sizeof(node), mycmp);
		ans=0;
		initialize();
		for(i=0; i<E; i++)
		{
			u=arr[i].u;v=arr[i].v;w=arr[i].w;
			if(isConnected(u,v))
			{
				ans+=w;
			}
			else
			{
				mkunion(u,v);	
			}
		}
		printf("%lld\n",ans);	
	}	
	return 0;
}
