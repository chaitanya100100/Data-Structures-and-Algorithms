#include<iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;

bool RED=true;
bool BLACK=false;

struct node
{
    int i;
    double val;
    bool color;
    node* left;
    node* right;
};

bool isRed(node* h)
{
    if(h==NULL)return false;
    return (h->color==RED);
}

node* rotateLeft(node* h)
{
    if(h==NULL)return h;
    node* x = h->right;
    h->right = x->left;
    x->left = h;
    x->color = h->color;
    h->color = RED;
    return x;
}
node* rotateRight(node* h)
{
    if(h==NULL)return h;
    node* x = h->left;
    h->left = x->right;
    x->right = h;
    x->color = h->color;
    h->color = RED;
    return x;
}
void flipColor(node* h)
{
    if(h==NULL || h->left==NULL || h->right==NULL)return;
    h->left->color = !h->left->color;
    h->right->color = !h->right->color;
    h->color = !h->color;
}
void balance(node* h)
{
    if(!isRed(h->left) && isRed(h->right)) h = rotateLeft(h);
    if(isRed(h->left) && isRed(h->left->left)) h = rotateRight(h);
    if(isRed(h->left) && isRed(h->right)) flipColor(h) ;
}
node* insert(node* h, int i, double val)
{
    if(h==NULL)
    {
        node* pnew = (node*)malloc(sizeof(node));
        pnew->i=i;
        pnew->val=val;
        pnew->left=NULL;
        pnew->right=NULL;
        pnew->color=RED;
        return pnew;
    }
    if(h->i>i) h->left=insert(h->left,i,val);
    else if(h->i<i) h->right=insert(h->right,i,val);
    else h->val=val;

    if(!isRed(h->left) && isRed(h->right)) h = rotateLeft(h);
    if(isRed(h->left) && isRed(h->left->left)) h = rotateRight(h);
    if(isRed(h->left) && isRed(h->right)) flipColor(h) ;

    return h;
}

double search(node* h, int i)
{
    if(h==NULL)return 0;
    if(h->i==i)return h->val;
    if(h->i>i) return search(h->left, i);
    if(h->i<i) return search(h->right, i);
}
void iter(node* h, int* a, int* num)
{
    if(h==NULL)return;
    iter(h->left, a, num);
    a[*num] = h->i;
    (*num)++;
    iter(h->right, a, num);
}

double dot(node* h, double b[],int n)
{
    double sum = 0.0;
    int* a = (int*)malloc(n*sizeof(int));
    int num=0;
    iter(h,a,&num);

    for(int i=0; i<num; i++)
    {
        //printf("%lf\n",search(h,a[i]));
        sum += search(h,a[i])*b[a[i]];
    }
    return sum;
}

double* matMul(node* a[], double b[], int n)
{
    double* ans=(double*)malloc(n*sizeof(double));
    for(int i=0; i<n; i++)
        ans[i] = dot(a[i],b,n);
    /*for(int i=0; i<n; i++)
        printf("%lf\n",ans[i]);*/
    return ans;
}

void display(node* h)
{
    if(h==NULL)return;
    display(h->left);
    printf("%d %.2lf ",h->i,h->val);
    display(h->right);
}

int main()
{
    int j,i,n=4;
    node* a[n];
    double k,b[n];

    for(i=0; i<n; i++)
        a[i]=NULL;

    printf("a:\n");
    for(i=0; i<n; i++)
    for(j=0; j<n; j++)
    {
        scanf("%lf",&k);
        if(k!=0)
        {
            a[i] = insert(a[i], j, k);
        }
    }
    printf("\n\nnow b:\n");
    for(i=0; i<n; i++)
        scanf("%lf",&b[i]);

    for(i=0; i<n; i++)
    {
        display(a[i]);
        printf("\n");
    }
    printf("\n");
    double* ans = matMul(a,b,n);
    for(int i=0; i<n; i++)
        printf("%.2lf\n",ans[i]);
    /*
    node* root=NULL;
    int i;
    double v;
    scanf("%d%lf", &i, &v);
    while(i!=-1)
    {
        root=insert(root, i, v);
        scanf("%d%lf", &i, &v);
    }
    display(root);
        printf("\n");*/
    return 0;
}
