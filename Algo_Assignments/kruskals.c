#include<stdio.h>
#include<stdlib.h>

struct node
{
	int u;
	int v;
	int w;
};
typedef struct node node;
int* id;
int* size;
node* arr;

int mycmp(const void* a, const void* b)
{
	return (*(node*)a).w - (*(node*)b).w;
}

int root(int i)
{
	while(id[i]!=i)
	{
		id[i]=id[id[i]];
		i=id[i];
	}
	return i;
}

void mkunion(int a, int b)
{
	a=root(a);
	b=root(b);
	if(a==b)return;
	
	if(size[a]<size[b]){int temp=a;a=b;b=temp;}
	id[b]=a;
	size[a]+=size[b];
}

int isCon(int a, int b)
{
	if(root(a)==root(b))
		return 1;
	else
		return 0;
}

int main()
{
	int i,u,v,w,V,E,j,k;
	scanf("%d%d",&V,&E);

	id = (int*)malloc(sizeof(int)*(V+2));
	size = (int*)malloc(sizeof(int)*(V+2));
	arr = (node*)malloc(sizeof(node)*(E+2));

	for(i=0; i<E; i++)
		scanf("%d%d%d",&arr[i].u,&arr[i].v,&arr[i].w);
	
	for(i=0; i<=V; i++)
	{
		size[i]=1;
		id[i]=i;
	}

	qsort(arr, E, sizeof(node), mycmp);
	k=0;
	printf("\n");
	for(i=0; i<E; i++)
	{
		u = arr[i].u;			
		v = arr[i].v;			
		w = arr[i].w;
		if(root(u)!=root(v))
		{
			mkunion(u,v);
			printf("%d %d : %d\n",u,v,w);
			k+=w;
		}
	}
	printf("\ntotal weight : %d\n",k);

	return 0;
}
