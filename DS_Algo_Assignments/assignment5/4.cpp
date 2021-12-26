#include<bits/stdc++.h>
using namespace std;

int n,f;
char arr[505][505];

int adj[29][29];
int parent[28],child[28];

int check(int p, int c)
{
	//printf("%d\n",adj[p][c]);
	if(adj[p][c]!=-1)
		return adj[p][c];
	
	int i,j,pc,cc;
	pc=cc=0;

	parent[pc++]=p;	
	child[cc++]=c;	

	for(i=0; i<26; i++)
	if(adj[i][p]==1)
	parent[pc++]=i;	
	
	for(i=0; i<26; i++)
	if(adj[c][i]==1)
	child[cc++]=i;	

	for(i=0; i<pc; i++)
	for(j=0; j<cc; j++)
	{
		adj[parent[i]][child[j]]=1;
		adj[child[j]][parent[i]]=0;
	}
	return 1;
}

int mycmp(int p)
{
	int i=0,s;
	char* b=arr[p];
	char* a=arr[p-1];
	
	while(1)
	{
		if(a[i]=='\0')
		{s=1;break;}	
		if(b[i]=='\0')
		{s=2;break;}
		if(a[i]!=b[i])
		{s=3;break;}
		i++;
	}
	//printf("s = %d\n",s);
	if(s==1)return 1;
	if(s==2)return 0;
	if(s==3)
	{
		int x=a[i]-'a',y=b[i]-'a';
		return check(y,x);
	}
}

void printmat()
{
	int i,j;
	printf("----------------------------\n");
	for(i=0; i<9; i++)
	{
		for(j=0; j<9; j++)
			printf("%d ",adj[i][j]);
		printf("\n");
	}
}

int main()
{
	int t,i,j,k;
	cin >> t;
	while(t--)
	{
		scanf("%d",&n);
		f=1;
		for(i=0; i<n; i++)
			scanf("%s",arr[i]);
		for(i=0; i<29; i++)
		for(j=0; j<29; j++)
			adj[i][j]=-1;
		
		for(i=1; i<n; i++)
		{
			if(mycmp(i)==0)
			{
				f=0;
				break;
			}
			//printmat();
		}
		printf("%s\n",(f)?"Possible":"Impossible");
	}
	return 0;
}
