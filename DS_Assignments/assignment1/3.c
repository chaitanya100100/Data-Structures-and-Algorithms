#include<stdio.h>
#include<string.h>

char arr[200005],n;
int ans;

void push(int i)
{
    if(n>100005)
    {
        ans=0;
        return;
    }
    arr[n++]=i;
}
int pop()
{
    if(n==0)
        return -1;
    return arr[--n];
}

int main()
{
    int t,i,j,k;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%s",arr);
        ans = 1;
        i=0;
        n=0;
        while(ans && arr[i]!='\0')
        {
            if(arr[i]=='(')
                push(1);
            else if(arr[i]=='[')
                push(2);
            else if(arr[i]=='{')
                push(3);
            else if(arr[i]==')')
            {
                j=pop();
                if(j!=1)
                    ans=0;
            }
            else if(arr[i]==']')
            {
                j=pop();
                if(j!=2)
                    ans=0;
            }
            else if(arr[i]=='}')
            {
                j=pop();
                if(j!=3)
                    ans=0;
            }
            i++;
        }
        if(ans && n==0)
            printf("Yes\n");
        else
            printf("No\n");
    }
    return 0;
}
