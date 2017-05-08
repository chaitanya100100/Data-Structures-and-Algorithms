#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define M 1000000007
#define ll long long
#define P 31

ll power(ll x, ll y)
{
    ll a=1;
    while(y)
    {
        if(y&1)
            a=(a*x)%M;
        x=(x*x)%M;
        y=y/2;
    }
    return a;
}

ll numberOfPalin(char arr[])
{
    ll ans=0,i,j,k,a,b;
    ll l=strlen(arr),invMod=power(P,M-2);
    ll front[l+5],back[l+5];

    front[0]=back[l]=0,k=1;
    for(i=1; i<=l; i++)
    {
        front[i]=(front[i-1]+((arr[i-1]-'0')*k)%M)%M;
        back[l-i]=(back[l-i+1]+((arr[l-i]-'0')*k)%M)%M;
        k=(k*P)%M;
    }
    /*for(i=1; i<=l; i++)
        printf("%lld ",front[i]);
    printf("\n");
    for(i=0; i<l; i++)
        printf("%lld ",back[i]);
    printf("\n");*/

    for(i=1; i<=l; i++)
    {
        for(j=0; j<l-i+1; j++)
        {
            a = (((front[j+i]-front[j]+M)%M)*power(invMod,j))%M;
            b = (((back[j]-back[j+i]+M)%M)*power(invMod,l-i-j))%M;
            //printf("%lld %lld\n",a,b);
            if(a==b)
                ans++;
        }
    }
    return ans;
}

int main()
{

    char arr[100];
    scanf("%s",arr);
    printf("%lld\n",numberOfPalin(arr));
    return 0;
}
