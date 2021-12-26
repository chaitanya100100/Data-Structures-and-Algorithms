#include<stdio.h>
#define M 1000000007
long long int div[100005];

int main()
{
    long long int sum,t,n,i,j,k,ans;
    scanf("%lld",&t);
    while(t--)
    {
        for(i=0; i<100005; i++)
            div[i]=0;
        scanf("%lld%lld",&n,&k);
        sum=0;
        ans=0;
        for(i=1; i<=n; i++)
        {
            scanf("%lld",&j);
            sum = sum + j;
            div[sum%k]++;
        }
	div[0]++;
        for(i=0; i<k; i++)
            ans = (ans + (div[i]*(div[i]-1))/2)%M;
        printf("%lld\n",ans);
    }
    return 0;
}
