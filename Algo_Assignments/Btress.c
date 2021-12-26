#include<stdio.h>
#include<stdlib.h>

struct Node
{
	int v[3];
	struct Node* ptr[4];
};
typedef struct Node Node;
int check;
Node* left;
Node* right;

void split(Node* root)
{
	Node* p1=(Node*)malloc(sizeof(Node));
	Node* p2=(Node*)malloc(sizeof(Node));
	p1->v[0]=root->v[0];
	p2->v[0]=root->v[2];
	p1->v[1]=p1->v[2]=p2->v[1]=p2->v[2]=-1;
	p1->ptr[0]=root->ptr[0];
	p1->ptr[1]=root->ptr[1];
	p2->ptr[0]=root->ptr[2];
	p2->ptr[1]=root->ptr[3];
	p1->ptr[2]=p1->ptr[3]=NULL;
	p2->ptr[2]=p2->ptr[3]=NULL;
	left=p1;
	right=p2;
	free(root);
}

Node* insert(Node* root, int k)
{
	if(root==NULL)
	{
		Node* pnew = (Node*)malloc(sizeof(Node));
		pnew->v[0] = k;
		pnew->v[1] = pnew->v[2] = -1;
		int i;
		for(i=0; i<4; i++)
			pnew->ptr[i] = NULL;
		return pnew;
	}
	if(root->v[0]>k)
	{
		if(root->ptr[0]==NULL)
		{
			root->v[2]=root->v[1];
			root->v[1]=root->v[0];
			root->v[0]=k;
		}
		else
			root->ptr[0] = insert(root->ptr[0], k);
	}
	else if((root->v[1]==-1)||(root->v[1]!=-1 && k<root->v[1]))
	{
		if(root->ptr[1]==NULL)
		{
			root->v[2]=root->v[1];
			root->v[1]=k;
		}
		else
			root->ptr[1] = insert(root->ptr[1], k);
	}
	else
	{
		if(root->ptr[2]==NULL)
			root->v[2]=k;
		else
			root->ptr[2] = insert(root->ptr[2], k);
	}
	if(check)
	{
		if(root->ptr[0]->v[2]!=-1)
		{
			root->v[2]=root->v[1];
			root->v[1]=root->v[0];
			root->v[0]=root->ptr[0]->v[1];
			root->ptr[3]=root->ptr[2];
			root->ptr[2]=root->ptr[1];
			split(root->ptr[0]);
			root->ptr[0]=left;
			root->ptr[1]=right;
		}
		else if(root->ptr[1]->v[2]!=-1)
		{
			root->v[2]=root->v[1];
			root->v[1]=root->ptr[1]->v[1];
			root->ptr[3]=root->ptr[2];
			split(root->ptr[1]);
			root->ptr[1]=left;
			root->ptr[2]=right;
		}
		else if(root->ptr[2]->v[2]!=-1)
		{
			root->v[2]=root->ptr[2]->v[1];
			split(root->ptr[2]);
			root->ptr[2]=left;
			root->ptr[3]=right;
		}
		else
		{
			printf("Fault logical\n\n\n\n\n");
		}
	}
	if(root->v[2]!=-1)
		check=1;
	else
		check=0;
	return root;
}

Node* specialForRoot(Node* root)
{
	check=0;
	Node* pnew = (Node*)malloc(sizeof(Node));
	pnew->v[0] = root->v[1];
	pnew->v[1] = pnew->v[2]=-1;
	split(root);
	pnew->ptr[0]=left;
	pnew->ptr[1]=right;
	pnew->ptr[2]=pnew->ptr[3]=NULL;
	return pnew;	
}

/*int isdel;
Node* del(Node* root, int k)
{
	if(root==NULL)return root;
	
	if(root->v[0]==k)
	{
		if(root->ptr[0]==NULL)
		{
			isdel = ;	
		}
	}
}*/


void inorder(Node* root)
{
	if(root==NULL)
		return;
	printf("%d %d\n",root->v[0],root->v[1]);
	inorder(root->ptr[0]);
	inorder(root->ptr[1]);
	inorder(root->ptr[2]);
}



int main()
{
	check  =  0;
	isdel = -1;
	Node* root=NULL;
	int i,j,k;

	scanf("%d",&i);
	while(i!=-1)
	{
		root = insert(root, i);
		if(check)root=specialForRoot(root);
		
		inorder(root);
		scanf("%d",&i);
	}
	return 0;
}
