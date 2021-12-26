#include<stdio.h>
#include<stdlib.h>

int V,E,count;

struct node
{
    int v;
    struct node* next;
};
typedef struct node node;

node* adj[100005];
int in[100005],out[100005],visited[100005];

void add(int a, int b)
{
    in[b]++;
    out[a]++;
    node* pnew=(node*)malloc(sizeof(node));
    pnew->next=adj[a];
    pnew->v=b;
    adj[a]=pnew;
}

void clearStart()
{
    int i;
    for(i=0; i<V; i++)
    {
        in[i]=out[i]=visited[i]=0;
        adj[i]=NULL;
    }
}

void dfs(int s)
{
    visited[s]=1;
    node* cur = adj[s];
    while(cur!=NULL)
    {
        count++;
        if(!visited[cur->v])
            dfs(cur->v);
        cur=cur->next;
    }
}

int countEdge()
{
    count=0;
    dfs(0);
    return count==E;
}

void clearEnd()
{
    int i;
    node* cur;
    node* temp;
    for(i=0; i<V; i++)
    {
         cur=adj[i];
         while(cur!=NULL)
         {
             temp=cur;
             cur=cur->next;
             free(temp);
         }
    }
}

int main()
{
    int flag,t,i,j,k,a,b;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&V,&E);
        clearStart();

        for(i=0; i<E; i++)
        {
            scanf("%d%d",&a,&b);
            a--;b--;
            add(a,b);
        }
        flag=1;
        for(i=0; i<V; i++)
            if(in[i]!=out[i])
            {
                flag=0;
                break;
            }
        if(flag==1 && countEdge())
            printf("Yes\n");
        else
            printf("No\n");
        clearEnd();
    }
    return 0;
}
