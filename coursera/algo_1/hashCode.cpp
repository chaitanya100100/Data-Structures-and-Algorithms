#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<math.h>
#include<string.h>
#include<limits.h>
#include<functional>
#define M (1000000007)
using namespace std;

int hash(int a)
{
    return a;
}
int hash(long int a)
{
    return (int)((a>>16)^a);
}
int hash(long long int a)
{
    return (int)((a>>16)^a);
}
int hash(char a)
{
    return a;
}
int hash(float a)
{
    return (int)((long long)a%M);
}
int hash(double a)
{
    return (int)((long long)a%M);
}
int hash(int arr[],int n)
{
    int ans=17,i;
    for(i=0; i<n; i++)
        ans = ans*31 + hash(arr[i]);
    return ans;
}
int hash(char arr[])
{
    int ans=17,i,l=strlen(arr);
    for(i=0; i<l; i++)
        ans = ans*31 + hash(arr[i]);
    return ans;
}

int main()
{
    int i;
    char c[3];
    double d;
    long long l;

    while(1)
    {
        printf("i c d l\n");
        scanf("%d%s%lf%ld",&i,c,&d,&l);
        printf("%d = %d\n",i,hash(i));
        printf("%c = %d\n",c[0],hash(c[0]));
        printf("%lf = %d\n",d,hash(d));
        printf("%lld = %d\n\n",l,hash(l));
    }
}
