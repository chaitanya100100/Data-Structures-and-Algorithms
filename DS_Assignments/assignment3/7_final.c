#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#define M 1000000007

struct node
{
    int data;
    int weight;
    struct node* next;
};
typedef struct node node;

node* add(node* root, int k, int w)
{
    node* pnew = (node*)malloc(sizeof(node));
    pnew->data = k;
    pnew->weight = w;
    pnew->next = root;
    root = pnew;
    return root;
}

int n,subTreeSum[10004],visited[10004];
node* adj[10004];

int dfs(int s)
{
    visited[s] = 1;
    node* cur = adj[s];
    int sum=0;
    while(cur != NULL)
    {
        if(!visited[cur->data])
        {
            sum += dfs(cur->data);
            sum += cur->weight;
        }
        cur = cur->next;
    }
    subTreeSum[s] = sum;
    return sum;
}


int main()
{
    int i,u,v,k;
    scanf("%d",&n);
    for(i=0; i<n; i++)
    {
        adj[i]=NULL;
        visited[i] = 0;
    }
    for(i=0; i<n-1; i++)
    {
        scanf("%d%d%d",&u,&v,&k);
        u--;v--;
        adj[u] = add(adj[u], v, k);
        adj[v] = add(adj[v], u, k);
    }

    dfs(0);
    for(i=0; i<n; i++)
    {
        visited[i] = 0;
    }
    int c,max,temp,control=0,ans=0,go,b;

    while(adj[control]!=NULL)
    {
        node* cur = adj[control];
        visited[control] = 1;
        max=0;
        temp=0;
        c=0;
        while(cur!=NULL)
        {
            if(!visited[cur->data])
            {
                c=1;
                visited[cur->data]=1;
                if(cur->weight + subTreeSum[cur->data] > max)
                {
                    max = cur->weight + subTreeSum[cur->data];
                    go = cur->data;
                    b = cur->weight;
                }
                temp += cur->weight + subTreeSum[cur->data];
            }
            cur = cur->next;
        }
        if(!c)break;
        ans += 2*(temp - max) + b;
        control = go;
    }
    printf("%d\n",ans);
    return 0;
}
