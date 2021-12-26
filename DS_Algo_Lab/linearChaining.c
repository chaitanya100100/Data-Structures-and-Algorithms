#include<stdio.h>
#include<stdlib.h>
struct node
{
	int v;
	struct node* next;
};
typedef struct node node;
node** adj;
int* count;
int N;
int fun[10]={3,5,7,11,13};
int which=0;

int hash(int h)
{
	return h%N;
}
void rehash()
{
	which++;
	int oldN=N;
	N=fun[which];

	node** newadj = (node**)malloc(N*sizeof(node*));
	int* newcount = (int*)malloc(N*sizeof(int));
	int h,i,j,k;
	for(i=0; i<N; i++)
	{
		newadj[i]=NULL;
		newcount[i]=0;
	}
		
	node* temp;
	for(i=0; i<oldN; i++)
	{
		node* cur=adj[i];
		while(cur!=NULL)
		{
		
			k=cur->v;	
			node* pnew = (node*)malloc(sizeof(node));
			h=hash(k);
			pnew->next=newadj[h];
			pnew->v=k;
			newadj[h]=pnew;
			newcount[h]++;		

			temp=cur;
			cur=cur->next;
			free(temp);
		}
	}
	adj=newadj;
	count=newcount;
}

void add(int k)
{
	node* pnew = (node*)malloc(sizeof(node));
	int h=hash(k);
	pnew->next=adj[h];
	pnew->v=k;
	adj[h]=pnew;
	count[h]++;
	if(count[h]>N)
		rehash();
}
void print()
{
	int i;
	node* cur;
	for(i=0; i<N; i++)
	{
		cur=adj[i];
		printf("%d : ",i);
		while(cur!=NULL)
		{
			printf("%d ",cur->v);
			cur=cur->next;
		}
		printf("\n");
	}
}
int find(int k)
{
	int h=hash(k);
	node* cur = adj[h];
	while(cur!=NULL)
	{
		if(cur->v==k)
			return 1;
		cur=cur->next;
	}
	return 0;
}
node* del_(node* root, int k, int h)
{
	if(root==NULL)
		return root;
	if(root->v==k)
	{
		count[h]--;
		return root->next;
	}
	if(root->next==NULL)
	{
		if(root->v==k)
		{
			count[h]--;
			return root->next;
		}
		else
			return root;
	}
	node* cur=root;
	while(cur->next!=NULL && cur->next->v!=k)
		cur=cur->next;
	if(cur->next==NULL)
		return root;
	cur->next=cur->next->next;
	count[h]--;
	return root;
}
void del(int k)
{
	int h=hash(k);
	adj[h] = del_(adj[h],k,h);
}

int main()
{
	int i,j,k;
	N=fun[which];
	adj = (node**) malloc(N*sizeof(node*));
	count = (int*) malloc(N*sizeof(int));
	for(i=0; i<N; i++)
	{
		adj[i]=NULL;
		count[i]=0;
	}
	scanf("%d%d",&j,&k);
	while(j!=-1)
	{
		if(j==1)
			add(k);
		else if(j==2)
			del(k);
		else
			printf("%d\n",find(k));
		print();
		scanf("%d%d",&j,&k);
	}
	return 0;
}
