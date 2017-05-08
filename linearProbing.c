#include<stdio.h>
#include<stdlib.h>

int* arr;
int which,fun[10]={3,11,31,65};
int N,M;

int hash(int k)
{
	return k%N;
}

void rehash()
{
	which++;
	int h,i,j,k,oldN=N;
	N=fun[which];
	int* newarr=(int*)malloc(N*sizeof(int));
	
	for(i=0; i<N; i++)
		newarr[i]=0;
	M=0;
	for(j=0; j<oldN; j++)
	{

		if(arr[j]!=-1 && arr[j]!=0)
		{
			h=hash(arr[j]),i;
			i=h;
			while(newarr[i]!=-1 && newarr[i]!=0)
				i=(i+1)%N;
			newarr[i]=arr[j];
			M++;
		}
	}
	arr=newarr;
}

void add(int k)
{
	int h=hash(k),i;
	i=h;
	//printf("%d %d\n",i,arr[i]);
	while(arr[i]!=-1 && arr[i]!=0)
		i=(i+1)%N;
//	printf("%d\n",i);
	arr[i]=k;
	M++;
	if(M>N/2)
		rehash();
//		printf("added\n");
}

int find(int k)
{
	int h=hash(k),i;
	i=h;
	while(arr[i]!=0)
	{
		if(arr[i]==k)
			return 1;
		i=(i+1)%N;
	}
	return 0;
}

void del(int k)
{
	int h=hash(k),i;
	i=h;
	while(arr[i]!=0)
	{
		if(arr[i]==k)
		{
			arr[i]=-1;
			M--;
			return;
		}
		i=(i+1)%N;
	}
}
void print()
{
	int i;
	for(i=0; i<N; i++)
		printf("%d ",arr[i]);
	printf("\n");
}

int main()
{
	which=0;
	N=fun[which];
	M=0;
	arr=(int*)malloc(N*sizeof(int));

	int i,j,k;
	for(i=0; i<N; i++)
		arr[i]=0;

	scanf("%d%d",&i,&j);
	while(i!=-1)
	{
		if(i==1)
			add(j);
		else if(i==2)
			del(j);
		else
			printf("%d\n",find(j));
		printf("-----\n");
		print();
		scanf("%d%d",&i,&j);
	}

	return 0;
}
