#include<bits/stdc++.h>
using namespace std;

struct Node
{
    int data;
    int height;
	int count;
    struct Node* left;
    struct Node* right;
};
typedef struct Node Node;

int max(int a, int b)
{
    if(a>b) return a;
    else    return b;
}

int getHeight(Node* root)
{
    if(root==NULL)
        return 0;
    else
        return root->height;
}

int getCount(Node* root)
{
	if(root==NULL)return 0;
	else return root->count;
}

int getBalance(Node* root)
{
    if(root==NULL)
        return 0;
    else
        return getHeight(root->left)-getHeight(root->right);
}

Node* rotateLeft(Node* x)
{
    Node* y = x->right;
    x->right = y->left;
    y->left = x;

    x->height = max(getHeight(x->right), getHeight(x->left)) + 1;
    y->height = max(getHeight(y->right), getHeight(y->left)) + 1;
    x->count = 1+getCount(x->left)+getCount(x->right);
    y->count = 1+getCount(y->left)+getCount(y->right);
	return y;
}

Node* rotateRight(Node* x)
{
    Node* y = x->left;
    x->left = y->right;
    y->right = x;

    x->height = max(getHeight(x->right), getHeight(x->left)) + 1;
    y->height = max(getHeight(y->right), getHeight(y->left)) + 1;
    x->count = 1+getCount(x->left)+getCount(x->right);
    y->count = 1+getCount(y->left)+getCount(y->right);
    return y;
}

Node* getMin(Node* root)
{
    if(root==NULL)  return root;
    Node* temp=root;
    while(temp->left!=NULL)
        temp = temp->left;
    return temp;
}

Node* insert(Node* root, int k)
{
    if(root==NULL)
    {
        Node* pnew = (Node*)malloc(sizeof(Node));
        pnew->data = k;
        pnew->height = 1;
        pnew->left = NULL;
        pnew->right = NULL;
        pnew->count = 1;
		return pnew;
    }
    if(root->data > k)
        root->left = insert(root->left, k);
    else if(root->data < k)
        root->right = insert(root->right, k);
    else
		return root;

    root->height = max(getHeight(root->right), getHeight(root->left)) + 1;

    int balance = getBalance(root);

    if(balance > 1 && k < root->left->data)
        root = rotateRight(root);
    else if(balance < -1 && k >= root->right->data)
        root = rotateLeft(root);
    else if(balance > 1 && k >= root->left->data)
    {
        root->left = rotateLeft(root->left);
        root = rotateRight(root);
    }
    else if(balance < -1 && k < root->right->data)
    {
        root->right = rotateRight(root->right);
        root = rotateLeft(root);
    }
	root->count = 1+getCount(root->left)+getCount(root->right);
    return root;
}

Node* deleteNode(Node* root, int k)
{
    if(root==NULL)  return root;
    if(root->data<k)
        root->right = deleteNode(root->right, k);
    else if(root->data>k)
        root->left = deleteNode(root->left, k);
    else
    {
        if(root->left==NULL)
        {
            Node* temp = root->right;
            free(root);
            return temp;
        }
        else if(root->right==NULL)
        {
            Node* temp = root->left;
            free(root);
            return temp;
        }
        else
        {
            Node* temp = getMin(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    }
    root->height = max(getHeight(root->right), getHeight(root->left)) + 1;
    
	int balance = getBalance(root);

    if(balance < -1 && getBalance(root->right)<=0)
        root = rotateLeft(root);
    else if(balance < -1 && getBalance(root->right)>0)
    {
        root->right = rotateRight(root->right);
        root = rotateLeft(root);
    }
    else if(balance > 1 && getBalance(root->left)>=0)
        root = rotateRight(root);
    else if(balance > 1 && getBalance(root->left)<0)
    {
        root->left = rotateLeft(root->left);
        root = rotateRight(root);
    }
	root->count = 1+getCount(root->left)+getCount(root->right);
    return root;
}

int kthsmallest(Node* root, int k)
{
	if(root==NULL)
		return INT_MIN;
	int c =	getCount(root->left);
	if(c==k-1)
		return root->data;
	else if(c>k-1)
		return kthsmallest(root->left,k);
	else
		return kthsmallest(root->right,k-c-1);	
}

int rank_(Node* root, int k)
{
	if(root==NULL)return 0;
	if(root->data==k)
		return getCount(root->left);
	else if(root->data>k)
		return rank_(root->left, k);
	else
		return 1+getCount(root->left)+rank_(root->right, k);
}

void inorder(Node* root)
{
    if(root==NULL)  return;
    inorder(root->left);
    printf("%d %d ||",root->data,root->count);
    inorder(root->right);
}

int main()
{
    Node* root=NULL;
    int p,k,t;
    char op[5];
    scanf("%d",&t);
    while(t--)
    {
        scanf("%s%d",op,&k);
		if(op[0]=='I')
			root = insert(root, k);
		else if(op[0]=='D')
			root = deleteNode(root, k);
		else if(op[0]=='K')
		{
			p=kthsmallest(root, k);
			//printf("%d %d\n",INT_MIN,p);	
			if(p==INT_MIN)
				printf("invalid\n");
			else
				printf("%d\n",p);
		}
		else if(op[0]=='C')
			printf("%d\n",rank_(root, k));
    	else
			printf("Fault\n");
		//inorder(root);
		//printf("\n");
	}
    return 0;
}
