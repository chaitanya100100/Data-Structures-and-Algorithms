#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#define M 1000000007
#define ll long long

struct node
{
    ll data;
    struct node* next;
};
typedef struct node node;

node* add(node* root, ll k)
{
    node* pnew = (node*)malloc(sizeof(node));
    pnew->data = k;
    pnew->next = root;
    root = pnew;
    return root;
}
node* adj[1000006];
int V,E,visited[1000006];
ll ans;

ll dfs(ll s)
{
    ll temp,atthis=1;
    visited[s] = 1;
    node* cur = adj[s];
    while(cur!=NULL)
    {
        if(!visited[cur->data])
        {
            temp = dfs(cur->data);
            atthis = ( atthis * (temp+1) )%M;
        }
        cur = cur->next;
    }
    ans = (ans + atthis)%M;
    return atthis;
}

int main()
{
    ll t,i,j,k,u,v,n;
    scanf("%lld",&t);
    while(t--)
    {
        scanf("%lld",&n);
        for(i=0; i<n; i++)
        {
            adj[i]=NULL;
            visited[i]=0;
        }
        for(i=0; i<n-1; i++)
        {
            scanf("%lld%lld",&u,&v);
            u--;v--;
            adj[u] = add(adj[u],v);
            adj[v] = add(adj[v],u);
        }
        ans=0;
        dfs(0);
        printf("%lld\n",ans);
    }
    return 0;
}
