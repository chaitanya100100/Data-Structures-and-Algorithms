//algo is wrong but still got accepted

#include<bits/stdc++.h>
#define PB push_back
#define MP make_pair
#define F first
#define S second
using namespace std;

int N,n;
vector<pair<int, int> > Qpre,Qin;
vector<pair<int, int> > Tpre,Tin;
bool done[5005];

int bsp(int k, int l, int r)
{
    if(l>r)return -1;
    int m=(l+r)/2;
    if(Qpre[m].F==k)return Qpre[m].S;
    if(Qpre[m].F>k) return bsp(k,l,m-1);
    if(Qpre[m].F<k) return bsp(k,m+1,r);
}
int bsi(int k, int l, int r)
{
    if(l>r)return -1;
    int m=(l+r)/2;
    if(Qin[m].F==k)return Qin[m].S;
    if(Qin[m].F>k) return bsi(k,l,m-1);
    if(Qin[m].F<k) return bsi(k,m+1,r);
}

int main()
{
    int p,i,j,k,f;
    cin >> N;
    for(i=0; i<N; i++)
    {cin >> k;Qpre.PB(MP(k,i));}
    for(i=0; i<N; i++)
    {cin >> k;Qin.PB(MP(k,i));}
    sort(Qpre.begin(), Qpre.end());
    sort(Qin.begin(), Qin.end());
    for(i=0;i<5005;i++)done[i]=false;
    while(cin >> n)
    {
        Tpre.clear();
        Tin.clear();
        if(n<0)break;
        for(i=0; i<n; i++)
        {cin >> k;Tpre.PB(MP(k,i));}
        for(i=0; i<n; i++)
        {cin >> k;Tin.PB(MP(k,i));}
        p=INT_MIN;
        f=1;
        for(i=0; f && i<n; i++)
        {
            j=bsp(Tpre[i].F, 0, N-1);
            if(j==-1 || j<=p){f=0;break;}
            else{p=j;}
        }
        p=INT_MIN;
        for(i=0; f && i<n; i++)
        {
            j=bsi(Tin[i].F, 0, N-1);
            if(j==-1 || j<=p){f=0;break;}
            else{p=j;}
        }
        if(f==0)continue;
        for(i=0; i<n; i++)
        {done[bsp(Tpre[i].F, 0, N-1)]=true;}
    }
    f=1;
    for(i=0; i<N; i++)
    if(done[i]==false){f=0;break;}
    printf("%s\n",(f)?"Yes":"No");
    return 0;
}
