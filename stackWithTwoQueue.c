#include<stdio.h>
#define N 100

int fair=1,q[2][N],l[2],r[2];

void enqueue(int i, int ele)
{
	q[i][r[i]]=ele;
	r[i]=(r[i]+1)%N;
}
int dequeue(int i)
{
	if(l[i]==r[i])
		return -1;
	int ans=q[i][l[i]];
	l[i] = (l[i]+1)%N;
	return ans;
}
/*void change()
{
	if(fair==0)
		fair=1;
	else
		fair=0;
}*/
void push(int p)
{
	enqueue(0,p);
}
int pop()
{
	if(l[0]==r[0])return -1;
	while(l[0]!= (r[0]-1+N)%N)
		enqueue(1,dequeue(0));
	int ans = dequeue(0);
	while(l[1]!=r[1])
		enqueue(0,dequeue(1));
	return ans;
}


int main()
{
	int n,p;
	l[0]=l[1]=r[1]=r[0]=0;


	scanf("%d",&n);
	while(n!=-1)
	{
		if(n==1)
		{
			scanf("%d",&p);
			push(p);			
		}
		else
		{
			printf("%d popped\n",pop());
		}
		scanf("%d",&n);
	}

	return 0;
}
