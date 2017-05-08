#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<math.h>
#include<limits.h>
using namespace std;

bool HOR=false;
bool VER=true;

struct node
{
    int x;
    int y;
    int val;
    bool part;
    struct node* left;
    struct node* right;
};
typedef struct node node;

struct point
{
    int x;
    int y;
};
typedef struct point point;
int i;
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
double distance(int x, int y, point p)
{
    return sqrt((p.x-x)*(p.x-x) + (p.y-y)*(p.y-y));
}

node* insert(node* h, int x, int y, int val, bool part)
{
    if(h==NULL)
    {
        node* pnew = (node*)malloc(sizeof(node));
        pnew->x = x;
        pnew->y = y;
        pnew->val = val;
        pnew->left = NULL;
        pnew->right = NULL;
        pnew->part = part;
        return pnew;
    }
    if(h->x==x && h->y==y) h->val = val;
    else if((part)?(h->x>x):(h->y>y)) h->left = insert(h->left, x, y, val, !part);
    else h->right = insert(h->right, x, y, val, !part);
    return h;
}

void searchInRectangle(node* h, point p1, point p2)
{
    if(h==NULL)return;
    if(((h->part)?h->x:h->y) >= min(((h->part)?p1.x:p1.y),((h->part)?p2.x:p2.y))) searchInRectangle(h->left, p1, p2);
    if((p2.x-h->x)*(h->x-p1.x) >= 0 && (p2.y-h->y)*(h->y-p1.y) >= 0)printf("(%d,%d) ",h->x,h->y);
    if(((h->part)?h->x:h->y) <= max(((h->part)?p1.x:p1.y),((h->part)?p2.x:p2.y))) searchInRectangle(h->right, p1, p2);
}
node* nearestPoint(node* h, point q, double* champDist)
{
    if(h==NULL)return h;
    node* ans=NULL;
    node* temp;
    bool y;
    if(distance(h->x,h->y,q)<*champDist) {ans = h;*champDist=distance(h->x,h->y,q);}
    //printf("%d ",i++);
    i++;
    if(((h->part)?h->x:h->y)>((h->part)?q.x:q.y))
    {
        y = true;
        temp = nearestPoint(h->left, q, champDist);
        if(temp!=NULL)
        {
            ans=temp;
            *champDist = distance(ans->x,ans->y,q);
        }
    }
    else
    {
        y = false;
        temp = nearestPoint(h->right, q, champDist);
        if(temp!=NULL)
        {
            ans=temp;
            *champDist = distance(ans->x,ans->y,q);
        }
    }
    if(y && abs(((h->part)?h->x:h->y)- ((h->part)?q.x:q.y))<*champDist)
    {
        temp = nearestPoint(h->right, q, champDist);
        if(temp!=NULL)
        {
            ans=temp;
            *champDist = distance(ans->x,ans->y,q);
        }
    }
    if(!y && abs(((h->part)?h->x:h->y)- ((h->part)?q.x:q.y))<*champDist)
    {
            temp = nearestPoint(h->left, q, champDist);
            if(temp!=NULL)
            {
                ans=temp;
                *champDist = distance(ans->x,ans->y,q);
            }
    }
    return ans;
}

void display(node* h)
{
    if(h==NULL)return;
    display(h->left);
    printf("(%d,%d) ",h->x,h->y);
    display(h->right);
}

int main()
{
    int x,y;
    double a,s=0;
    point p1,p2;
    node* root=NULL;
    node* ans;
    /*scanf("%d%d",&x,&y);
    while(x!=-1)
    {
        root = insert(root, x, y, rand()%100, VER);
        scanf("%d%d",&x,&y);
    }*/
    for(x=0;x<500; x++)
    {
        root = insert(root, rand()%1000, rand()%1000, rand()%100, VER);
    }
    for(x=0;x<500; x++)
    {
        a = 999999.99;
        i=1;
        p1.x = rand()%1000;
        p1.y = rand()%1000;
        ans = nearestPoint(root, p1, &a);
        s += i;
    }
    printf("%f %f\n",s,s/500.0);
    /*display(root);
    printf("\n");
    scanf("%d%d",&p1.x,&p1.y);
    while(p1.x!=-1)
    {
        a = 999999.99;
        i=1;
        ans = nearestPoint(root, p1, &a);
        printf("(%d,%d)\n",ans->x,ans->y);
        scanf("%d%d",&p1.x,&p1.y);
    }*/
    /*scanf("%d%d%d%d",&p1.x,&p1.y,&p2.x,&p2.y);
    while(p1.x!=-1)
    {
        searchInRectangle(root, p1, p2);
        printf("\n");
        scanf("%d%d%d%d",&p1.x,&p1.y,&p2.x,&p2.y);
    }*/
}
