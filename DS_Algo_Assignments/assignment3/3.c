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
node* adj[500005];
int in[500005];
int prime[10000000];
int V,E,count,queue[500005];
int check, num;
int ans[500005];


int main()
{
    int t,j,i,u,v,l,r;
    prime[1]=1;
    for(i=4; i<8000000; i+= 2)
        prime[i]=1;

    for(i=3; i<8000000; i++)
    {
        if(prime[i]==0)
        {
            for(j=3*i; j<8000000; j+=2*i)
                prime[j] = 1;
        }
    }
    prime[0]=0;
    num=1;
    for(i=2; i<8000000; i++)
    if(prime[i]==0)
    prime[num++]=i;

    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&V,&E);

        for(i=0; i<V; i++)
        {
            adj[i]=NULL;
            ans[i]=0;
            in[i]=0;
        }
        for(i=0; i<E; i++)
        {
            scanf("%d%d",&v,&u);
            adj[u] = add(adj[u], v);
            in[v]++;
        }
        check=count=0;
        l=r=0;
        ans[0]=0;
        queue[r++]=0;

        if(in[0]==0)
        {
        while(l!=r)
        {
            u=queue[l++];
            node* cur = adj[u];
            while(cur!=NULL)
            {
                in[cur->data]--;
                if(in[cur->data]==0)
                {
                    queue[r++]=cur->data;
                    ans[cur->data] = ans[u]+1;
                }
                cur = cur->next;
            }
        }

        for(i=1; i<V; i++)
            if(ans[i]==0)
                {check=1;break;}

        if(check!=1)
        {
        long long last=0;
        for(i=0; i<V; i++)
            last = last + (long long)(prime[ans[i]]);
        printf("%lld\n",last);
        }
        else
            printf("evil emperor loses\n");
        }
        else
        {
            printf("evil emperor loses\n");
        }
    }
    return 0;
}
