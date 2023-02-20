#include<stdio.h>
#include<stdlib.h>

struct node
{
    int key;
    int val;
    int count;
    struct node* left;
    struct node* right;
};
typedef struct node node;

int size(node* root)
{
    if(root==NULL)return 0;
    return root->count;
}

int search(node* root, int k)
{
    if(root==NULL)return -1;
    if(root->key==k)return root->val;
    if(root->key<k) return search(root->right,k);
    if(root->key>k) return search(root->left,k);
}

node* delMin(node* root)
{
    if(root==NULL)return root;
    if(root->left==NULL)
    {
        node* temp = root->right;
        //free(root);
        return temp;
    }
    root->left=delMin(root->left);
    root->count = 1+size(root->left)+size(root->right);
    return root;
}
node* delMax(node* root)
{
    if(root==NULL)return root;
    if(root->right==NULL)
    {
        node* temp = root->left;
        //free(root);
        return temp;
    }
    root->right=delMax(root->right);
    root->count = 1+size(root->left)+size(root->right);
    return root;
}
node* findMin(node* root)
{
    if(root==NULL || root->left==NULL)return root;
    return findMin(root->left);
}

node* deleteByKey(node* root, int k)
{
    if(root==NULL)return root;
    else if(root->key>k) root->left = deleteByKey(root->left,k);
    else if(root->key<k) root->right = deleteByKey(root->right,k);
    else
    {
        if(root->left==NULL)return delMin(root);
        if(root->right==NULL)return delMax(root);
        node* m=findMin(root->right);
        root->right=delMin(root->right);
        m->left=root->left;
        m->right=root->right;
        root=m;
    }
    root->count= 1 + size(root->left) + size(root->right);
    return root;
}

node* insert(node* root, int k, int v)
{
    if(root==NULL)
    {
        node* pnew= (node*)malloc(sizeof(node));
        pnew->key=k;
        pnew->val=v;
        pnew->count=1;
        pnew->left=NULL;
        pnew->right=NULL;
        return pnew;
    }
    if(root->key<k)
        root->right = insert(root->right,k,v);
    else if(root->key>k)
        root->left = insert(root->left,k,v);
    else
        root->val=v;
    root->count = 1+size(root->left)+size(root->right);
    return root;
}

int floor_(node* root, int k)
{
    if(root==NULL)return -1;
    if(root->key==k) return k;
    if(root->key>k) return floor_(root->left, k);

    int t = floor_(root->right,k);
    if(t!=-1)return t;
    return root->key;
}

int ceil_(node* root, int k)
{
    if(root==NULL) return -1;
    if(root->key==k) return k;
    if(root->key<k) return ceil_(root->right, k);

    int t = ceil_(root->left, k);
    if(t!=-1)return t;
    return root->key;
}

int rank(node* root, int k)
{
    if(root==NULL)return 0;
    if(root->key==k) return size(root->left);
    if(root->key>k) return rank(root->left, k);
    return 1 + size(root->left) + rank(root->right, k);
}

void display(node* root)
{
    if(root==NULL)return;
    display(root->left);
    printf("%d ",root->key);
    display(root->right);
}

int main()
{
    int k,v,t;
    node* root=NULL;
    scanf("%d%d",&k,&v);
    while(k!=-1)
    {
        root=insert(root,k,v);
        scanf("%d%d",&k,&v);
    }
    display(root);
    printf("\n");
    /*scanf("%d",&k);
    while(k!=-1)
    {
        printf("%d %d\n",k,search(root,k));
        scanf("%d",&k);
    }*/
    do
    {
        printf("1-del min\t2-del max\t3-del by key\t4-ceil\t5-floor\t6-rank\telse-insert\n");
        scanf("%d%d",&t,&k);
        if(t==1) root=delMin(root);
        else if(t==2) root=delMax(root);
        else if(t==3) root=deleteByKey(root,k);
        else if(t==4) printf("%d\n",ceil_(root, k));
        else if(t==5) printf("%d\n",floor_(root, k));
        else if(t==6) printf("%d\n",rank(root, k));
        else root=insert(root,t,k);
        display(root);
        printf("\n");
    }while(t!=-1);
    return 0;
}
