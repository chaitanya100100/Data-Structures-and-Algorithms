#include<stdio.h>

typedef struct
{
    int x;
    int y;
} Point;
Point point[100],hull[100];


void swap(Point* p, Point*q)
{
        Point t;
        t = *p; *p = *q; *q = t;
}

int ccw(Point * p, Point * q, Point * r)
{
    return((r->y-q->y)*(q->x-p->x)-(q->y-p->y)*(r->x-q->x));
}

void print(Point point[], int n)
{
    int i;
    for(i=0; i<n; i++)
        printf("%d %d\n",point[i].x,point[i].y);
}

int check(Point * p, Point * q, Point * r)
{
    int a = p->y - r->y;
    int b = q->y - r->y;
    if(a==0 && b==0)return 0;
    if(a<0 && b>=0)return 0;
    if(b<0 && a>=0)return 1;
    if(ccw(r,p,q)>=0)return 0;
    return 1;
}

void sort_by_y(Point point[], int n)
{
    int i,j;
    for(i=0; i<n; i++)
    for(j=i; j<n-1; j++)
    {
        if((point[j].y > point[j+1].y) || ((point[j].y == point[j+1].y) &&(point[j].x > point[j+1].x)))
        {
            //printf("swap %d %d\n",j,j+1);
            swap(&point[j],&point[j+1]);
        }
    }
}

void sort_by_polar_angle(Point point[], int n)
{
    int i,j;
    Point temp;
    for(i=1; i<n; i++)
    {
        for(j=i; j<n-1; j++)
        {
            if(check(&point[j],&point[j+1],&point[0]))
            {
                //printf("swap %d %d\n",j,j+1);
                swap(&point[j+1],&point[j]);
            }
        }
    }
}

void convex_hull(Point point[], int n, Point hull[])
{
    sort_by_y(point,n);
    //print(point,n);
    sort_by_polar_angle(point,n);
    //print(point,n);

    Point temp;
    hull[0]=point[0];
    hull[1]=point[1];
    int i=2,j,k;
    for(j=2; j<n; j++)
    {
        temp = hull[--i];
        //k=i;
        //printf("hull-%d hull-%d p-%d\n",i-1,k,j);
        while(ccw(&hull[i-1],&temp,&point[j])<=0)
            temp=hull[--i];
        hull[i++]=temp;
        hull[i++]=point[j];
    }
    print(hull,i);
}

int main()
{
    int n,i;
    scanf("%d",&n);
    for(i=0; i<n; i++)
        scanf("%d%d",&point[i].x,&point[i].y);
    //print(point,n);
    convex_hull(point,n,hull);

    return 0;
}
