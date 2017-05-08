#include<stdio.h>
#include<stdlib.h>
struct node
{
	int data;
	int count;
	struct node* left;
	struct node* right;
};
typedef struct node node;

//node* collect;

int size(node* root)
{
	if(root==NULL)
		return 0;
	else
		return root->count;
}

node* insert(node* root, int k)
{
	if(root==NULL)
	{
		node* pnew = (node*) malloc(sizeof(node));
		pnew->left=NULL;
		pnew->right=NULL;
		pnew->count=1;
		pnew->data=k;
		return pnew;
	}
	if(root->data < k)
		root->right = insert(root->right,k);
	else if(root->data > k)
		root->left = insert(root->left,k);
	else
		root->data = k;
	root->count = 1+size(root->right)+size(root->left);
	return root;
}

node* find(node* root, int k)
{
	if(root==NULL)
		return root;
	else if(root->data == k)
		return root;
	else if(root->data > k)
		return find(root->left,k);
	else
		return find(root->right,k);
}
int collect;
node* delMax(node* root)
{
	if(root==NULL)
		return root;
	if(root->right==NULL)
	{
		node* cur = root->left;
		collect = root->data;
		free(root);
		return cur;
	}
	root->right = delMax(root->right);
	root->count = 1+size(root->right)+size(root->left);
	return root;
}
node* delMin(node* root)
{
	if(root==NULL)
		return root;
	if(root->left==NULL)
	{
		node* cur = root->right;
		collect = root->data;
		free(root);
		return cur;
	}
	root->left = delMin(root->left);
	root->count = 1+size(root->right)+size(root->left);
	return root;
}
int ceil_(node* root, int k)
{
	if(root==NULL)
		return -1;
	else if(root->data==k)
		return k;
	else if(root->data < k)
		return ceil_(root->right, k);
	else
	{
		int t = ceil_(root->left,k);
		if(t!=-1)
			return t;
		else
			return root->data;
	}
}
int floor_(node* root, int k)
{
	if(root==NULL)
		return -1;
	else if(root->data==k)
		return k;
	else if(root->data>k)
		return floor_(root->left, k);
	else
	{
		int t = floor_(root->right,k);
		if(t!=-1)
			return t;
		else
			return root->data;
	}
}
int smallerThan(node* root, int k)
{
	if(root==NULL)
		return 0;
	else if(root->data==k)
		return size(root->left);
	else if(root->data>k)
		return smallerThan(root->left,k);
	else //(root->data<k)
		return size(root->left)+1+smallerThan(root->right,k);
}
node* delByKey(node* root, int k)
{
	if(root==NULL)
	{
		collect = -10000000;
		return root;
	}
	if(root->data > k)
		root->left = delByKey(root->left,k);
	else if(root->data < k)
		root->right = delByKey(root->right,k);
	else //(root->data==k)
	{
		if(root->left==NULL)
		{
			node* tmp = root->right;
			collect=root->data;
			free(root);
			return tmp;
		}
		else if(root->right==NULL)
		{
			node* tmp = root->left;
			collect=root->data;
			free(root);
			return tmp;
		}
		else
		{
			root->right = delMin(root->right);
			int te=root->data;
			root->data = collect;
			collect = te;
		}
	}
	root->count = 1 + size(root->left) + size(root->right);
	return root;
}
void inorder(node* root)
{
	if(root==NULL)
		return;
	inorder(root->left);
	printf("%d ",root->data);
	inorder(root->right);
}

int main()
{
	node* root=NULL;
	int t,v,k,j,i;
	printf("1 - insert\n");
	printf("2 - find\n");
	printf("3 - delete max\n");
	printf("4 - delete min\n");
	printf("5 - delete by key\n");
	printf("6 - smaller than k\n");
	printf("7 - floor of k\n");
	printf("8 - ceilling of k\n");
	scanf("%d",&t);
	while(t!=-1)
	{
		if(t==1)
		{
			scanf("%d",&v);
			root = insert(root,v);						
		}
		else if(t==2)
		{
			scanf("%d",&v);
			if(find(root,v)!=NULL)
				printf("YES\n");
			else
				printf("NO\n");
		}
		else if(t==3)
		{
			root=delMax(root);
			printf("%d deleted\n",collect);
		}
		else if(t==4)
		{
			root=delMin(root);
			printf("%d deleted\n",collect);
		}
		else if(t==5)
		{
			scanf("%d",&v);
			root = delByKey(root, v);
			printf("%d deleted\n",collect);
		}
		else if(t==6)
		{
			scanf("%d",&v);
			printf("%d elements are smaller than %d\n",smallerThan(root,v),v);
		}
		else if(t==7)
		{
			scanf("%d",&v);
			printf("%d is just smaller or equal to %d\n",floor_(root,v),v);
		}
		else if(t==8)
		{
			scanf("%d",&v);
			printf("%d is just bigger or equal to %d\n",ceil_(root,v),v);	
		}
		inorder(root);
		printf("\n");
		scanf("%d",&t);
	}
	return 0;
}
