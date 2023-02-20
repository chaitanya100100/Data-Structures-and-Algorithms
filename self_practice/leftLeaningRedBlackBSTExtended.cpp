#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;

bool RED=true;
bool BLACK=false;
struct node
{
    int key;
    int val;
    bool color;
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
bool isRed(node* h)
{
    if(h==NULL)return false;
    return (h->color==RED);
}

int ceil_(node* root, int k)
{
    if(root==NULL)return -1;
    if(root->key==k)return k;
    if(root->key<k) return ceil_(root->right, k);

    int t = ceil_(root->left, k);
    if(t!=-1)return t;
    return root->key;
}
int floor_(node* root, int k)
{
    if(root==NULL)return -1;
    if(root->key==k)return k;
    if(root->key>k) return floor_(root->left, k);

    int t = floor_(root->right, k);
    if(t!=-1)return t;
    return root->key;
}
int rank(node* root, int k)
{
    if(root==NULL)return 0;
    if(root->key>k)return rank(root->left,k);
    if(root->key<k) return 1 + size(root->left) + rank(root->right, k);
    return size(root->left);
}
int search(node* root, int k)
{
    if(root==NULL)return -1;
    if(root->key==k)return root->val;
    if(root->key<k) return search(root->right,k);
    if(root->key>k) return search(root->left,k);
}

node* rotateRight(node* h)
{
    node* x = h->left;
    h->left = x->right;
    x->right = h;
    x->color = h->color;
    h->color = RED;
    x->count = h->count;
    h->count = 1 + size(h->left) + size(h->right);
    return x;
}
node* rotateLeft(node* h)
{
    node* x = h->right;
    h->right = x->left;
    x->left = h;
    x->color = h->color;
    h->color = RED;
    x->count = h->count;
    h->count = 1 + size(h->left) + size(h->right);
    return x;
}
void flipColor(node* h)
{
    h->left->color = !h->left->color;
    h->right->color = !h->right->color;
    h->color = !h->color;
}
node* insert(node* root, int k, int v)
{
    if(root==NULL)
    {
        node* pnew = (node*)malloc(sizeof(node));
        pnew->key = k;
        pnew->val = v;
        pnew->color = RED;
        pnew->count = 1;
        pnew->left = NULL;
        pnew->right = NULL;
        return pnew;
    }
    if(root->key>k) root->left = insert(root->left, k, v);
    else if(root->key<k) root->right = insert(root->right, k, v);
    else root->val=v;

    if(isRed(root->right) && !isRed(root->left)) root = rotateLeft(root);
    if(isRed(root->left) && isRed(root->left->left)) root = rotateRight(root);
    if(isRed(root->right) && isRed(root->left)) flipColor(root);
    root->count = 1 + size(root->left) + size(root->right);
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
    root->right = delMax(root->right);
    if(isRed(root->right) && !isRed(root->left)) root = rotateLeft(root);
    if(isRed(root->left) && isRed(root->left->left)) root = rotateRight(root);
    if(isRed(root->right) && isRed(root->left)) flipColor(root);
    root->count = 1 + size(root->left) + size(root->right);
    return root;
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
    root->left = delMin(root->left);
    if(isRed(root->right) && !isRed(root->left)) root = rotateLeft(root);
    if(isRed(root->left) && isRed(root->left->left)) root = rotateRight(root);
    if(isRed(root->right) && isRed(root->left)) flipColor(root);
    root->count = 1 + size(root->left) + size(root->right);
    return root;
}

int rangeCount(node* root, int lo, int hi)
{
    if(search(root,hi)!=-1) return rank(root,hi)-rank(root,lo)+1;
    return rank(root,hi)-rank(root,lo);
}
void rangeSearch(node* root, int lo, int hi)
{
    if(root==NULL)return;
    if(root->key > lo) rangeSearch(root->left, lo, hi);
    if(root->key>=lo && root->key<=hi) printf("%d ",root->key);
    if(root->key < hi) rangeSearch(root->right, lo, hi);
}

void display(node* root)
{
    if(root==NULL)return;
    display(root->left);
    printf("%d ",root->key);
    display(root->right);
}
void displayTree(node* root, int i)
{
    if(root==NULL)return;
    printf("%3d at level %2d with color %5s and count %2d\n",root->key,i,(root->color)?"Red":"Black",root->count);
    displayTree(root->left, i+1);
    displayTree(root->right, i+1);
}
int main()
{
    char arr[3];
    int i,v,k;
    node* root = NULL;

    /*for(i=254; i>=1; i--)
    {
        root = insert(root,i,rand()%100);
    }*/
    scanf("%d%d",&k,&v);
    while(k!=-1)
    {
        if(k==1)root=delMin(root);
        else if(k==2)root=delMax(root);
        else root = insert(root,k,v);
        display(root);
        printf("\n");
        scanf("%d%d",&k,&v);
    }
    scanf("%d%d",&k,&v);
    while(k!=-1)
    {
        rangeSearch(root,k,v);
        printf("\n");
        scanf("%d%d",&k,&v);
    }

    //displayTree(root,0);
    return 0;
}
