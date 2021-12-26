#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define M 1000000007
#define P 31
#define ll long long

char** str;
ll hash[3][100005],h[3][100005],l[3],invMod,power[100005];

ll max(ll a, ll b)
{
    if(a>b)return a;
    return b;
}

void generate()
{
    ll i;
    power[0]=1;
    for(i=1; i<100005; i++)
        power[i] = (power[i-1]*invMod)%M;
}

ll _pow(ll x, ll y)
{
    ll ans=1;
    while(y)
    {
        if(y&1)
            ans=(ans*x)%M;
        x=(x*x)%M;
        y=y/2;
    }
    return ans;
}

ll isSubstring(ll a, ll b)
{
    ll i,j,k=1,hb=hash[b][l[b]],ha;

    for(i=0; i<=l[a]-l[b]; i++)
    {
        ha = (hash[a][l[b]+i]-hash[a][i]+M)%M;
        ha = (ha*k)%M;
        k=(k*invMod)%M;
        if(ha==hb)
            return 1;
    }
    return 0;
}

ll overlap(ll a, ll b)
{
    ll i,j,hb,ha,ans=0;
    for(i=0; i<=l[b]&&i<=l[a]; i++)
    {
        ha=hash[a][i];
        hb=(hash[b][l[b]]-hash[b][l[b]-i]+M)%M;
        hb=(hb*power[l[b]-i])%M;
        if(ha==hb)
            ans=i;
    }
    return ans;
}

int main()
{
    ll ans=0,i,j,k,temp;
    char* ptr;

    invMod=_pow(P,M-2);
    generate();
    str = (char**)malloc(3*sizeof(char*));
    for(i=0; i<3; i++)
        str[i] = (char*)malloc(100005*sizeof(char));

    scanf("%s",str[0]);l[0]=strlen(str[0]);
    scanf("%s",str[1]);l[1]=strlen(str[1]);
    scanf("%s",str[2]);l[2]=strlen(str[2]);

    for(i=0; i<2; i++)
    for(j=0; j<2-i; j++)
        if(l[j]>l[j+1])
        {
            ptr = str[j];
            str[j] = str[j+1];
            str[j+1] = ptr;
            temp = l[j];
            l[j] = l[j+1];
            l[j+1] = temp;
        }

    for(j=0; j<3; j++)
    {
        temp=1;
        hash[j][0]=h[j][0]=0;
        for(i=1; i<=l[j]; i++)
        {
            h[j][i]=(temp*(str[j][i-1]-'a'+1))%M;
            hash[j][i] = (hash[j][i-1]+h[j][i])%M;
            temp=(temp*P)%M;
        }
    }

    //printf("%s %s %s\n",str[0],str[1],str[2]);
    /*while(1)
    {
        scanf("%lld%lld",&i,&j);
        printf("%lld\n",isSubstring(i,j));
        printf("%lld %lld\n",overlap(i,j),overlap(j,i));
    }*/
    ll AinB=isSubstring(1,0),AinC=isSubstring(2,0),BinC=isSubstring(2,1);

    if(BinC)
    {
        //printf("loop : 1\n");
        if(AinC)
            ans=l[2];
        else
            ans=l[0]+l[2]-max(overlap(0,2),overlap(2,0));
        printf("%lld\n",ans);
    }
    else if(AinB || AinC)
    {
        //printf("loop : 2\n");
        ans=l[1]+l[2]-max(overlap(1,2),overlap(2,1));
        printf("%lld\n",ans);
    }
    else
    {
        //printf("loop : 3\n");
        ans = max(ans,overlap(1,0)+overlap(2,1));
        ans = max(ans,overlap(2,0)+overlap(1,2));
        ans = max(ans,overlap(0,1)+overlap(2,0));
        ans = max(ans,overlap(2,1)+overlap(0,2));
        ans = max(ans,overlap(0,2)+overlap(1,0));
        ans = max(ans,overlap(1,2)+overlap(0,1));
        /*ans = max(ans,max(overlap(0,1),overlap(1,0))+max(overlap(1,2),overlap(2,1)));
        ans = max(ans,max(overlap(0,2),overlap(2,0))+max(overlap(1,2),overlap(2,1)));
        ans = max(ans,max(overlap(0,1),overlap(1,0))+max(overlap(0,2),overlap(2,0)));
        ans = max(ans,max(overlap(2,1),overlap(1,2))+max(overlap(0,2),overlap(2,0)));
        ans = max(ans,max(overlap(2,1),overlap(1,2))+max(overlap(0,1),overlap(1,0)));
        ans = max(ans,max(overlap(2,0),overlap(0,2))+max(overlap(0,1),overlap(1,0)));*/
        printf("%lld\n",l[0]+l[1]+l[2]-ans);
    }
    return 0;
}
