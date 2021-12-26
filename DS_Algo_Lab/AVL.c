#include<stdio.h>
#include<stdlib.h>

struct Node
{
	int key;
	int height;
	struct Node* left;
	struct Node* right;
};
typedef struct Node Node;

int max(int a, int b)
{
	if(a>b)	return a;
	else	return b;
}

int getHeight(Node* root)
{
	if(root==NULL)	return 0;
	else		return root->height;
}

int getBalance(Node* root)
{
	return getHeight(root->left) - getHeight(root->right);
}

Node* rotateRight(Node* x)
{
	Node* y = x->left;
	x->left = y->right;
	y->right = x;

	x->height = 1 + max( getHeight(x->right), getHeight(x->left) );
	y->height = 1 + max( getHeight(y->right), getHeight(y->left) );
	return y;
}
Node* rotateLeft(Node* x)
{
	Node* y = x->right;
	x->right = y->left;
	y->left = x;

	x->height = 1 + max( getHeight(x->right), getHeight(x->left) );
	y->height = 1 + max( getHeight(y->right), getHeight(y->left) );
	return y;
}

void inorder(Node* root)
{
	if(root==NULL)	return;
	inorder(root->left);
	printf("%d ",root->key);
	inorder(root->right);
}

Node* insert(Node* root, int k)
{
	if(root==NULL)
	{
		Node* pnew = (Node*)malloc(sizeof(Node));
		pnew->key=k;
		pnew->height=1;
		pnew->left=NULL;
		pnew->right=NULL;
		return pnew;
	}
	if(root->key > k)
		root->left = insert(root->left, k);
	else
		root->right = insert(root->right, k);
	
	root->height = 1 + max( getHeight(root->left), getHeight(root->right));

	int balance = getBalance(root);

	if(balance>1 && root->left->key>k)
		root = rotateRight(root);
	else if(balance>1 && root->left->key<=k)
	{
		root->left = rotateLeft(root->left);
		root = rotateRight(root);
	}
	else if(balance<-1 && root->right->key<=k)
		root = rotateLeft(root);
	else if(balance<-1 && root->right->key>k)
	{
		root->right = rotateRight(root->right);
		root = rotateLeft(root);
	}
	return root;
}

Node* getMin(Node* root)
{
	if(root==NULL)return root;
	while(root->left!=NULL)
		root = root->left;
	return root;
}

Node* deleteNode(Node* root, int k)
{
	if(root==NULL)	return;
	if(root->key > k)
		root->left = deleteNode(root->left, k);
	else if(root->key < k)
		root->right = deleteNode(root->right, k);
	else
	{
		Node* tmp;
		if(root->left==NULL)
		{
			tmp = root->right;
			free(root);
			return tmp;
		}
		else if(root->right==NULL)
		{
			tmp = root->left;
			free(root);
			return tmp;
		}
		else
		{
			tmp = getMin(root->right);
			root->key = tmp->key;
			root->right = deleteNode(root->right, tmp->key);
		}
	}
	root->height = 1 + max( getHeight(root->left), getHeight(root->right) );		
	int balance = getBalance(root);
	if(balance > 1 && getBalance(root->left)>=0)
		root = rotateRight(root);
	else if(balance < -1 && getBalance(root->right)<=0)
		root = rotateLeft(root);
	else if(balance > 1 && getBalance(root->left)<0)
	{
		root->left = rotateLeft(root->left);
		root = rotateRight(root);
	}
	else if(balance < -1 && getBalance(root->right)>0)
	{
		root->right = rotateRight(root->right);
		root = rotateLeft(root);
	}
	return root;
}

int main()
{
	Node* root=NULL;
	int i,j,k;
	scanf("%d",&k);
	while(k!=-1)
	{
		scanf("%d",&j);
		if(k==1)
			root = insert(root, j);
		else if(k==2)
			root = deleteNode(root, j);
		inorder(root);
		printf("\nroot :- %d     height :- %d\n",root->key,getHeight(root));
		scanf("%d",&k);
	}
	return 0;
}
