#include<stdio.h>
#include<stdlib.h>

int* key;
int* pq;
int* qp;
int n=0;

void swap(int a, int b)
{
	int temp = pq[a];
	pq[a] = pq[b];
	pq[b] = temp;
	qp[pq[a]] = a;
	qp[pq[b]] = b;
}

void freeTheKey(int k)
{
	int temp,a=qp[k],b=qp[n+1];
	temp = key[k];
	key[k] = key[n+1];
	key[n+1] = temp;
	temp = pq[a];
	pq[a] = pq[b];
	pq[b] = temp;
	qp[pq[a]]=a;
	qp[pq[b]]=b;
}

void swim(int k)
{
	while(k>1 && key[pq[k]]>key[pq[k/2]])
	{
		swap(k,k/2);
		k=k/2;
	}
}

void sink(int k)
{
	int j;
	while(2*k<=n)
	{
		j=2*k;
		if(j<n && key[pq[j]]<key[pq[j+1]])j++;
		if(key[pq[j]]<=key[pq[k]])break;
		swap(k,j);
		k=j;
	}
}

void insert(int k)
{
	key[++n] = k;
	pq[n] = n;
	qp[n] = n;
	swim(n);
}

void delMax()
{
	swap(1,n);
	n--;
	sink(1);
	freeTheKey(pq[n+1]);
}

void delByKey(int k)
{
	k=qp[k];
	swap(k,n);
	sink(k);
	swim(k);
	freeTheKey(k);
}

void print()
{
	int i;
	for(i=1; i<=n; i++)
		printf("%d ",key[pq[i]]);
	printf("\n");
	for(i=1; i<=n; i++)
		printf("%d ",key[i]);
	printf("\n");
	for(i=1; i<=n; i++)
		printf("%d ",qp[i]);
	printf("\n");
}

int main()
{
	int i,j,k;
	
	pq = (int*) malloc(100*sizeof(int));
	qp = (int*) malloc(100*sizeof(int));
	key = (int*) malloc(100*sizeof(int));
	
	scanf("%d",&j);
	while(j!=-1)
	{
		if(j==1)
		{
			scanf("%d",&k);
			insert(k) ;
		}
		else if(j==2)
		{
			delMax();
		}
		print();
		scanf("%d",&j);
	}
	return 0;
}
