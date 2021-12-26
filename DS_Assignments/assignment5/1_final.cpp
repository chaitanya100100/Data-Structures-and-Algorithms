#include<bits/stdc++.h>
#define ll long long
#define M 1000000007
using namespace std;

int mat[5005][5005];
int cnt[5005][5005];
ll l,ans[5005];
char str[5005];
ll freq[5005],temp[5005];

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

void nCr()
{
	ll i,k,j;

	for(i=0; i<5005; i++)
		temp[i] = power(i, M-2);
	for(i=1; i<5002; i++)
	{
		mat[i][0]=1;
		for(j=1; j<=i/2; j++)
			mat[i][j] = int(((((ll)(mat[i][j-1])*(i-j+1))%M)*temp[j])%M);	
		for(; j<=i; j++)
			mat[i][j] = mat[i][i-j];
	}
}

void ZAlgo(char* arr, int* Z, int l)
{
	int i,j,k,left=-1,right=-1;
	Z[0]=l;
	for(k=1; k<l; k++)
	{
		if(right<k)
		{
			right = left = k;
			while(right<l && arr[right]==arr[right-left])right++;
			Z[k]=right-left;
			right--;
		}
		else
		{
			j=k-left;
			if(Z[j] <= right-k)
			{
				Z[k]=Z[j];
			}
			else
			{
				left=k;
				while(right<l && arr[right-left]==arr[right])right++;
				Z[k]=right-left;
				right--;
			}
		}
	}	
}

void calculate()
{
	ll i,j,k;
	for(i=0; i<=l; i++)
		freq[i]=0;
	for(i=0; i<l; i++)
	{
		ZAlgo(str+i, cnt[i], int(l-i));
		
		for(j=0; j<=l-i; j++)	
			temp[j]=0;
		for(j=0; j<l-i; j++)
			temp[cnt[i][j]]++;
		
		cnt[i][l-i]=temp[l-i];
		for(j=l-i-1; j>=0; j--)
			cnt[i][j] = int(temp[j]) + cnt[i][j+1];
			
		for(j=0; j<=l-i; j++)	
			temp[j]=0;
		for(j=1; j<=l-i; j++)
			temp[cnt[i][j]]++;
		

		for(j=1; j<l-i; j++)
			freq[j] += temp[j]-temp[j+1];
		freq[j] += temp[j];			
	}
	/*for(i=0; i<=l ;i++)
		printf("%lld ",freq[i]);
	printf("\n");*/
	for(i=1; i<=l; i++)
	{
		ans[i]=0;
		for(j=i; j<=l; j++)
			ans[i] = (ans[i] + ((ll)(mat[j][i])*freq[j])%M)%M; 
	}
}

int main()
{
	ll q,j;
	scanf("%lld%lld",&l,&q);
	scanf("%s",str);
	nCr();
	calculate();

	while(q--)
	{
		scanf("%lld",&j);
		if(j>l)printf("0\n");
		else printf("%lld\n",ans[j]);
	}
	
	return 0;
}
