#include<stdio.h>
#include<stdlib.h>
#define ll long long

ll w[100005],c[100005],q,k,n;

inline int isFair(ll l, ll m, ll r)
{
    if(r-m<=0 || m-l<0)
        return 0;
    ll on,hang;
    on=(w[m]-w[l-1])*q;
    hang=w[r]-w[m];

    if(on>=hang)
        return 1;
    return 0;
}

int main()
{
    ll a,b,max,left,right,i,j,t,go=1,l,m,r,ans,prev,prevAns;
    scanf("%lld",&t);
    while(t--)
    {
        scanf("%lld%lld%lld",&n,&k,&q);
        w[0]=c[0]=ans=0;
        for(i=1; i<=n; i++)
        {
            scanf("%lld",&j);
            w[i]=w[i-1]+j;
        }
        for(i=1; i<=n; i++)
            scanf("%lld",&c[i]);

        l=1;r=n;m=n-k;go=1;
        while(1)
        {
            left = isFair(l+1,m,r);
            right = isFair(l,m-1,r-1);

            if(left && right)
            {
            max = 0;
            for(j=1; isFair(l,m-j,r-j); j++)
                max += c[r-j+1];
            a = l;
            b = prev = r-j+1;
            prevAns = max;

            for(i=1; isFair(l+i,m,r); i++)
            {
                prevAns+=c[l+i-1];
                for(; !isFair(l+i,prev-k,prev); prev++)
                    prevAns-=c[prev+1];
                if(prevAns > max)
                {
                    max = prevAns;
                    a = l+i;
                    b = prev;
                }
            }
            ans += max;
            l=a;
            r=b;
            m=r-k;
            }
            else if(left)
            {
                ans += c[l];
                l++;
            }
            else if(right)
            {
                ans += c[r];
                r--;m--;
            }
            else
                break;
        }
        printf("%lld\n",ans);
    }
    return 0;
}
