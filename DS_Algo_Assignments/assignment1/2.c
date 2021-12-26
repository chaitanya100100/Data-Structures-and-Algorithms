#include<stdio.h>
#include<limits.h>
#define M 1000000007
#define ll long long

int power(int _x, int _y)
{
    ll x=_x,y=_y;
    ll ans=1;

    while(y)
    {
        if(y&1)
            ans = (ans*x)%M;
        x=(x*x)%M;
        y=y/2;
    }
    ans = ans%M;
    return (int)ans;
}

char arr[200005];
long long int stack[200005],n;

int main()
{
    long long int ans,t,i,j,k;
    scanf("%lld",&t);
    while(t--)
    {
        scanf("%s",arr);
        i=0,n=0;
        while(arr[i]!='\0')
        {
            if(arr[i]<='9' && arr[i]>='0')
                stack[n++]=arr[i]-'0';
            else
            {
                j=stack[--n];
                k = stack[--n];
                if(arr[i]=='+')
                    ans = (k+j)%M;
                else if(arr[i]=='*')
                    ans = (k*j)%M;
                else if(arr[i]=='-')
                    ans = (k-j+M)%M;
                else
                    ans = (k*power(j,M-2))%M;
                stack[n++]=ans;
            }
            /*for(j=0; j<n; j++)
                    printf("%lld ",stack[j]);
                printf("\n");
            */
            i++;
        }
        printf("%lld\n",stack[0]);
    }
    return 0;
}
