#include<stdio.h>
#include<stdlib.h>

int id[1000];
int size[1000];

int root(int i)
{
	while(i!=id[i])
	{
		i=id[id[i]];
		i=id[i];
	}
	return i;
}

int isUnited(int a, int b)
{
	if(root(a)==root(b))
		return 1;
	else 
		return 0;
}

void mkunion(int a, int b)
{
	a=root(a);
	b=root(b);
	if(a==b)return;
	if(size[a]<size[b]){int temp=a;a=b;b=temp;}
	id[b]=a;
	size[a] += size[b];
	return;
}

int main()
{
	int i,j,k,l;
	for(i=0; i<1000; i++)
	{
		id[i]=i;
		size[i]=1;
	}
	
	scanf("%d",&j);
	while(j!=-1)
	{
		scanf("%d%d",&k,&l);
		if(j==1)
			mkunion(k,l);
		else if(j==2)
			printf("%s\n",(isUnited(k,l))?"Yes":"No");
		scanf("%d",&j);
	}
	
	return 0;
}
