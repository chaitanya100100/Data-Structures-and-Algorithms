#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<math.h>
#include<limits.h>
using namespace std;

struct node
{
    int lo;
    int hi;
    int val;
    int maxHi;
    node* left;
    node* right;
};

int max(int a, int b)
{
    if(a>b)return a;
    return b;
}
int min(int a, int b)
{
    if(a<b)return a;
    return b;
}
node* insert(node* h, int lo, int hi, int val)
{
    if(h==NULL)
    {
        node* pnew = (node*)malloc(sizeof(node));
        pnew->lo = lo;
        pnew->hi = hi;
        pnew->val = val;
        pnew->left = NULL;
        pnew->right = NULL;
        pnew->maxHi = hi;
        return pnew;
    }
    if(h->lo==lo && h->hi==hi) h->val=val;
    else if(h->lo>lo) h->left = insert(h->left, lo, hi, val);
    else h->right = insert(h->right, lo, hi, val);
    if(h->maxHi<hi)h->maxHi=hi;
    return h;
}
int searchForIntersection(node* h, int lo, int hi)
{
    int i =0;
    while(h!=NULL)
    {
        if(max(h->lo, lo)<=min(h->hi, hi))
        {
            printf("(%d,%d)\n",h->lo, h->hi);
            return h->val;
        }
        if(h->left==NULL)   h=h->right;
        else if(h->left->maxHi<lo)h = h->right;
        else h=h->left;
    }
    return 0;
}


int main()
{
    node* root=NULL;
    int i,hi,lo;
    scanf("%d%d",&lo,&hi);
    while(lo!=-1)
    {
        root = insert(root, lo, hi, rand()%100);
        scanf("%d%d",&lo,&hi);
    }
    scanf("%d%d",&lo,&hi);
    while(lo!=-1)
    {
        i = searchForIntersection(root, lo, hi);
        scanf("%d%d",&lo,&hi);
    }
    return 0;
}
