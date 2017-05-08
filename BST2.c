#include<stdio.h>
#include<stdlib.h>
struct node
{
    int data;
    int count;
    struct node* left;
    struct  node* right;
};

typedef struct node node;

int size(node* root)
{
    if(root==NULL)return 0;
    return root->count;
}

node* insert(node* root, int k)
{
    if(root==NULL)
    {
        node* pnew = (node*)malloc(sizeof(node));
        pnew->data=k;
        pnew->left=NULL;
        pnew->right=NULL;
        pnew->count=1;
        return pnew;
    }
    if(root->data>k)
        root->left=insert(root->left,k);
    else
        root->right=insert(root->right,k);
    root->count = 1+size(root->left)+size(root->right);
    return root;
}
int collect;
node* delMin(node* root)
{
    if(root==NULL)return root;
    if(root->left==NULL)
    {
        node* tmp=root->right;
        collect=root->data;
        free(root);
        return tmp;
    }
    root->left=delMin(root->left);
    root->count = 1+size(root->left)+size(root->right);
    return root;
}

node* delByKey(node* root, int k)
{
    if(root==NULL)return root;

    if(root->data>k)root->left = delByKey(root->left,k);
    else if(root->data<k) root->right = delByKey(root->right,k);
    else // root->data==k
    {
        if(root->left==NULL)
        {
            node* tmp=root->right;
            collect=root->data;
            free(root);
            return tmp;
        }
        else if(root->right==NULL)
        {
            node* tmp=root->left;
            collect=root->data;
            free(root);
            return tmp;
        }
        else
        {
            root->right=delMin(root->right);
            collect=root->data;
        }
    }
    root->count=1+size(root->right)+size(root->left);
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
	//printf("2 - find\n");
	//printf("3 - delete max\n");
	printf("4 - delete min\n");
	printf("5 - delete by key\n");
	scanf("%d",&t);
	while(t!=-1)
	{
		if(t==1)
		{
			scanf("%d",&v);
			root = insert(root,v);
		}
		/*else if(t==2)
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
		}*/
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
		/*else if(t==6)
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
		}*/
		inorder(root);
		printf("\n");
		scanf("%d",&t);
	}
    return 0;
}
