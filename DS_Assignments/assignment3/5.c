#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#define M 100000000
#define B 10000000000
#define ll long long

struct range
{
    ll in;
    ll out;
    ll val;
};
typedef struct range range;

range arr[100005];
ll pq[200010];
ll order[2000010];
ll process[1000005];
ll scheduledTask;

ll ccmmpp(ll a, ll b)
{
    if(a/B < b/B)
        return 1;
    else if(a/B > b/B)
        return 0;
    else if(a%M > b%M)
        return 1;
    return 0;
}

void merge(ll l, ll m, ll r)
{
    ll i,j,k,n1=(m-l+1),n2=(r-m);
    ll a1[n1],a2[n2];

    for(i=0; i<n1; i++)
        a1[i] = order[l+i];
    for(j=0; j<n2; j++)
        a2[j] = order[m+1+j];
    i=j=0;k=l;

    while(i<n1 && j<n2)
    {
        if(a1[i]<a2[j])
            order[k++]=a1[i++];
        else
            order[k++]=a2[j++];
    }
    while(i<n1)
        order[k++]=a1[i++];
    while(j<n2)
        order[k++]=a2[j++];
}

void mergeSort(ll l, ll r)
{
    if(l<r)
    {
        ll m=(r-l)/2+l;
        mergeSort(l, m);
        mergeSort(m+1, r);
        merge(l, m, r);
    }
}
ll N;
void insertInPQ(ll k)
{
    pq[++N] = k;
    ll i = N, temp;
    while(i>1 && pq[i]>pq[i/2])
    {
        temp = pq[i];
        pq[i] = pq[i/2];
        pq[i/2] = temp;
        i=i/2;
    }
}

void deleteInPQ()
{
    ll temp;
    temp = pq[1];
    pq[1] = pq[N];
    pq[N] = temp;
    N--;

    ll j,k=1;
    while(2*k<=N)
    {
        j=2*k;
        if(j<N && pq[j]<pq[j+1])j++;
        if(pq[k]>=pq[j])break;
        temp = pq[k];
        pq[k] = pq[j];
        pq[j] = temp;
        k=j;
    }
}

int main()
{
    ll t,i,j,x,y,z,max,k,n,val,prev,now, time, change, p;
    scanf("%lld",&t);
    while(t--)
    {
        scanf("%lld",&n);
        N=scheduledTask = 0;
        for(i=0; i<n; i++)
        {
            scanf("%lld%lld%lld",&arr[i].in,&arr[i].out,&arr[i].val);
            order[scheduledTask++] = arr[i].in*B  + arr[i].val;
            order[scheduledTask++] = arr[i].out*B + M + arr[i].val;
        }

        //for(i=0; i<scheduledTask; i++)
            //printf("%18lld\n",order[i]);

        for(i=0; i<=1000003; i++)
            process[i]=0;
        mergeSort(0, scheduledTask-1);

        prev=order[0]/B,p=max=0;
        for(i=0; i<scheduledTask; i++)
        {

            x = order[i]/M;
            now = order[i]/B;
            val = order[i]%M;
            //printf("now = %lld ::: val = %lld\n",now,val);

            if(now != prev)
            {
                if(N!=0 && pq[1]!=max)
                {
                    max=pq[1];
                    printf("%lld %lld\n",prev,max);
                }
                else if(N==0 && max!=0)
                {
                    max=0;
                    printf("%lld %lld\n",prev,max);
                }
            }

            if(x%2==1)
            {
                if(val==max)
                {
                    p=1;
                    deleteInPQ();
                    while(N!=0 && process[pq[1]]!=0)
                    {
                        process[pq[1]]--;
                        deleteInPQ();
                    }
                }
                else
                    process[val]++;

                /*if(N!=0 && pq[1]!=max)
                {
                    max=pq[1];
                    printf("%lld %lld\n",now,max);
                }
                else if(N==0 && max!=0)
                {
                    max=0;
                    printf("%lld %lld\n",now,max);
                }*/
            }
            else if(x%2==0)
            {
                insertInPQ(val);
                /*if(pq[1]>max)
                {
                    p=1;
                    max = pq[1];
                    change = max;
                    time = now;
                    //printf("%lld %lld\n",now,max);
                }*/
            }
            prev = now;
        }
        printf("%lld %lld\n",prev,0);
    }
    return 0;
}
