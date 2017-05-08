#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<math.h>
#include<limits.h>
using namespace std;

struct point
{
    int x;
    int y;
};

struct node
{
    char c;
    point p1;
    point p2;
};
struct PQ
{
    int i;
    int x;
};
struct structForBST
{
    int y;
    int count;
    struct structForBST* left;
    struct structForBST* right;
};
node lineSegs[1000];
PQ pq[1000];
int numInPQ;


int min(int a, int b)
{
    if(a<b)return a;
    return b;
}
int max(int a, int b)
{
    if(a>b)return a;
    return b;
}
int size(structForBST* h)
{
    if(h==NULL)return 0;
    return h->count;
}

void swapInPQ(int a, int b)
{
    PQ t = pq[a];
    pq[a] = pq[b];
    pq[b] = t;
}

void swim(int k)
{
    while(k>1 && pq[k].x<pq[k/2].x)
    {
        swapInPQ(k,k/2);
        k = k/2;
    }
}
void sink(int k)
{
    int j,i;
    while(2*k<=numInPQ)
    {
        j = 2*k;
        if(j<numInPQ && pq[j+1].x<pq[j].x)j++;
        if(pq[j].x>=pq[k].x)break;
        swapInPQ(j,k);
        /*for(i=1; i<=numInPQ; i++)
        printf("%d %d\n",pq[i].i, pq[i].x);
        printf("\n");*/
        k = j;
    }
}

int delMin()
{
    swapInPQ(1,numInPQ--);
    sink(1);
    return pq[numInPQ+1].i;
}

void createHeap()
{
    int i=numInPQ/2;
    while(i>=1)
    {
        sink(i);
        i--;
    }
}

int search(structForBST* root, int k)
{
    if(root==NULL)return -1;
    if(root->y==k)return 1;
    if(root->y<k) return search(root->right,k);
    if(root->y>k) return search(root->left,k);
}
int rank(structForBST* h, int k)
{
    if(h==NULL)return 0;
    if(h->y==k) return size(h->left);
    if(h->y>k) return rank(h->left, k);
    return 1 + size(h->left) + rank(h->right, k);
}
int rangeCount(structForBST* h, int lo, int hi)
{
    if(search(h,hi)!=-1) return rank(h,hi)-rank(h,lo)+1;
    return rank(h,hi)-rank(h,lo);
}
structForBST* delMin(structForBST* root)
{
    if(root==NULL)return root;
    if(root->left==NULL)
    {
        structForBST* temp = root->right;
        //free(root);
        return temp;
    }
    root->left=delMin(root->left);
    root->count = 1+size(root->left)+size(root->right);
    return root;
}
structForBST* findMin(structForBST* root)
{
    if(root==NULL || root->left==NULL)return root;
    return findMin(root->left);
}
structForBST* deleteByKey(structForBST* root, int k)
{
    if(root==NULL)return root;
    else if(root->y>k) root->left = deleteByKey(root->left,k);
    else if(root->y<k) root->right = deleteByKey(root->right,k);
    else
    {
        if(root->left==NULL)return root->right;
        if(root->right==NULL)return root->left;
        structForBST* m=findMin(root->right);
        root->right=delMin(root->right);
        m->left=root->left;
        m->right=root->right;
        root=m;
    }
    root->count= 1 + size(root->left) + size(root->right);
    return root;
}
structForBST* insert(structForBST* h, int k)
{
    if(h==NULL)
    {
        structForBST* pnew = (structForBST*)malloc(sizeof(structForBST));
        pnew->y = k;
        pnew->count = 1;
        pnew->left = NULL;
        pnew->right = NULL;
        return pnew;
    }
    if(h->y<k) h->right = insert(h->right, k);
    else h->left = insert(h->left, k);
    h->count = 1+size(h->left)+size(h->right);
    return h;
}
void display(structForBST* root)
{
    if(root==NULL)return;
    display(root->left);
    printf("%d ",root->y);
    display(root->right);
}

int main()
{
    int i,a,b,c,d,e,n=3;
    structForBST* root=NULL;

    for(i=0; i<n; i++)
    {
        scanf("%d%d%d%d",&d,&a,&b,&c);
        lineSegs[i].c = (d)?'H':'V';
        /*a = rand()%n;
        b = rand()%n;
        c = rand()%n;*/
        if(lineSegs[i].c=='H')
        {
            lineSegs[i].p1.y = lineSegs[i].p2.y = a;
            lineSegs[i].p1.x = b;
            lineSegs[i].p2.x = c;
        }
        else if(lineSegs[i].c=='V')
        {
            lineSegs[i].p1.x = lineSegs[i].p2.x = a;
            lineSegs[i].p1.y = b;
            lineSegs[i].p2.y = c;
        }
        printf("(%d,%d) (%d,%d) %c\n",lineSegs[i].p1.x,lineSegs[i].p1.y,lineSegs[i].p2.x,lineSegs[i].p2.y,lineSegs[i].c);
    }
    i=0;numInPQ=0;
    while(i<n)
    {
        if(lineSegs[i].c=='V')
        {
            pq[++numInPQ].x=lineSegs[i].p1.x;
            pq[numInPQ].i=i;
        }
        else if(lineSegs[i].c=='H')
        {
            pq[++numInPQ].i=i;
            pq[numInPQ].x=lineSegs[i].p1.x;
            pq[++numInPQ].i=i;
            pq[numInPQ].x=lineSegs[i].p2.x;
        }
        i++;
    }
    for(i=1; i<=numInPQ; i++)
        printf("%d %d\n",pq[i].i, pq[i].x);
    printf("\n");
    createHeap();
    for(i=1; i<=numInPQ; i++)
        printf("%d %d\n",pq[i].i, pq[i].x);
    printf("\n\n\n");
    a=0;
    while(numInPQ!=0)
    {
        i = delMin();
        if(lineSegs[i].c=='H')
        {
            if(search(root,lineSegs[i].p1.y)==1)
                root = deleteByKey(root,lineSegs[i].p1.y);
            else
                root=insert(root,lineSegs[i].p1.y);
        }
        else
        {
            a += rangeCount(root, min(lineSegs[i].p1.y,lineSegs[i].p2.y), max(lineSegs[i].p1.y,lineSegs[i].p2.y));
        }
        printf("BST:\n");
        display(root);
        printf("\n\n");
        printf("PQ:\n");
        for(i=1; i<=numInPQ; i++)
        printf("%d %d\n",pq[i].i, pq[i].x);
        printf("\na = %d\n\n",a);
    }
    printf("intersections = %d\n",a);
}
