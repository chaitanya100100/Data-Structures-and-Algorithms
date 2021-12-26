#include<stdio.h>
#include<stdlib.h>
int a1[100005],a2[100005],a3[100005];
inline int input()
{
	int a=0;
	char c;
	c=getchar_unlocked();
	while(c>'9' || c<'0')
		c=getchar_unlocked();
	while(c>='0' && c<='9')
	{
		a = (a<<3) + (a<<1) + c - '0';
		c=getchar_unlocked();
	}
	return a;
}

int main()
{
	int t,n1,n2,n3,i,j,p1,p2,p3,count;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n1);
		for(i=0; i<n1; i++)
			a1[i]=input();
		scanf("%d",&n2);
		for(i=0; i<n2; i++)
			a2[i]=input();
		scanf("%d",&n3);
		for(i=0; i<n3; i++)
			a3[i]=input();
		p1=count=p2=p3=0;
		while(p1<n1 && p2<n2 && p3<n3)
		{
			if(a1[p1]==a2[p2] && a2[p2]==a3[p3])
				count++;
			if(a1[p1]<=a2[p2] && a1[p1]<=a3[p3])
				p1++;
			else if(a2[p2]<=a1[p1] && a2[p2]<=a3[p3])
				p2++;
			else
				p3++;

		}
		printf("%d\n",count);
	}
}
