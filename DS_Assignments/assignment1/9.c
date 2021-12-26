#include<stdio.h>
#include<stdlib.h>
#define ll long long

ll arr[100005],stack[100005],r,l;

int main()
{
    ll t,i,j,k,n;
    scanf("%lld",&t);
    while(t--)
    {
        scanf("%lld%lld",&n,&k);
        for(i=0; i<n; i++)
            scanf("%lld",&arr[i]);
        l=r=0;
        stack[r++]=0;
        for(i=1; i<=k; i++)
            arr[i] += arr[stack[l]];
        for(i=1; i<=k; i++)
        {
            while(l!=r && arr[i]<arr[stack[r-1]])r--;
            stack[r++]=i;
        }
        for(j=0;i<n; i++,j++)
        {
            if(stack[l]==j)
                l++;
            arr[i] += arr[stack[l]];
            while(l!=r && arr[i]<arr[stack[r-1]])r--;
            stack[r++]=i;
        }
        printf("%lld\n",arr[n-1]);
    }
    return 0;
}
