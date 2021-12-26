#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#define M 1000000007
#define ll long long

struct node
{
    ll data;
    ll weight;
    struct node* next;
};
typedef struct node node;

struct pnode
{
    ll v;
    ll val;
};
typedef struct pnode pnode;

node* add(node* root, ll k, ll w)
{
    node* pnew = (node*)malloc(sizeof(node));
    pnew->data = k;
    pnew->weight = w;
    pnew->next = root;
    root = pnew;
    return root;
}
node* adj[100005];
ll V,E,count,N,S,D,visited[100005],ans[100005],pq[2000010];

pnode arr[2000010];

ll max(ll a, ll b)
{
    if(a>b)return a;
    return b;
}

void swap(ll* a, ll* b)
{
    ll t = *a;
    *a=*b;
    *b=t;
}

void insertInPQ(ll zz, ll yy)
{
    pq[++N] = N;
    arr[N].v = zz;
    arr[N].val = yy;
    ll i=N;
    while(i>1 && arr[pq[i]].val < arr[pq[i/2]].val)
    {
        swap(&pq[i], &pq[i/2]);
        i=i/2;
    }

}

ll delete_()
{
    swap(&pq[1],&pq[N]);
    N--;
    ll i=1,j;
    while(2*i<=N)
    {
        j=2*i;
        if(j<N && arr[pq[j]].val>arr[pq[j+1]].val)j++;
        if(arr[pq[i]].val<=arr[pq[j]].val)break;
        swap(&pq[i], &pq[j]);
        i=j;
    }
    return arr[pq[N+1]].v;
}

ll isEmpty()
{
    if(N==0)
        return 1;
    else
        return 0;
}

void dijikstra()
{
    N=0;
    ll con=S,temp;
    ans[S] = 0;
    while(1)
    {
        //printf("%lld\n",con);
        node* cur = adj[con];
        visited[con] = 1;
        while(cur!=NULL)
        {
            temp = max(ans[con], cur->weight);
            if(ans[cur->data]>temp)
            {
                //printf("%lld inserted\n",cur->data);
                ans[cur->data]=temp;
                insertInPQ(cur->data, temp);
            }
            cur=cur->next;
        }
        do
        {
            if(isEmpty())return;
            con = delete_();
        }while(visited[con]==1);
    }
}

int main()
{
    ll t,u,v,w,i;
    scanf("%lld",&t);
    while(t--)
    {
        scanf("%lld%lld",&V,&E);

        for(i=0; i<V; i++)
        {
            ans[i]=LLONG_MAX;
            adj[i] = NULL;
            visited[i] = 0;
        }

        for(i=0; i<E; i++)
        {
            scanf("%lld%lld%lld",&u,&v,&w);
            u--;v--;
            adj[u] = add(adj[u], v, w);
        }
        scanf("%lld%lld",&S,&D);
        S--;D--;
        dijikstra();

        if(ans[D]==LLONG_MAX)
            printf("NO PATH\n");
        else
            printf("%lld\n",ans[D]);
    }
    return 0;
}
