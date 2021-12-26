#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#define M 1000000007

struct node
{
    int data;
    struct node* next;
};
typedef struct node node;

node* add(node* root, int k)
{
    node* pnew = (node*)malloc(sizeof(node));
    pnew->data = k;
    pnew->next = root;
    root = pnew;
    return root;
}
node* adj[100005];
node* revadj[100005];
int V,E,count;
int cost[100005],visited[100005],TS[100005],com[100005],freq[100005];

void dfsfirst(int v)
{
    visited[v] = 1;
    node* cur = adj[v];
    while(cur != NULL)
    {
        if(!visited[cur->data])
            dfsfirst(cur->data);
        cur = cur->next;
    }
    TS[--count] = v;
}

void dfssecond(int v)
{
    visited[v] = 1;
    com[v] = count;
    node* cur = revadj[v];
    while(cur != NULL)
    {
        if(!visited[cur->data])
            dfssecond(cur->data);
        cur = cur->next;
    }
}

int main()
{
    int t,i,u,v;
    long long int totalCost,ways;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&V,&E);
        for(i=0; i<V; i++)
        {
            scanf("%d",&cost[i]);
            adj[i] = NULL;
            revadj[i] = NULL;
            visited[i] = 0;
        }
        for(i=0; i<E; i++)
        {
            scanf("%d%d",&u,&v);
            u--;v--;
            adj[u] = add(adj[u], v);
            revadj[v] = add(revadj[v], u);
        }
        count=V;
        for(i=0; i<V; i++)
            if(!visited[i])
                dfsfirst(i);

        for(i=0; i<V; i++)
            visited[i] = 0;
        count=0;

        for(i=0; i<V; i++)
        {
            if(!visited[TS[i]])
            {
                dfssecond(TS[i]);
                count++;
            }
        }
        for(i=0; i<count; i++)
        {
            TS[i]=INT_MAX;
            freq[i]=0;
            visited[i]=0;
        }
        for(i=0; i<V; i++)
        {
            if(TS[com[i]]>cost[i])
                TS[com[i]]=cost[i];
        }
        for(i=0; i<V; i++)
        {
            if(TS[com[i]]==cost[i])
                freq[com[i]]++;
        }
        totalCost = 0;
        ways = 1;

        for(i=0; i<count; i++)
        {
            totalCost += TS[i];
            ways = (ways * ((long long)freq[i]))%M;
        }
        printf("%lld %lld\n",totalCost,ways);
    }
    return 0;
}
