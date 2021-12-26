#include<stdio.h>
#include<limits.h>

char arr[1005][1005];

int queue[1000061],l,r,done[1005][1005];

int main()
{
    int max,t,m,n,i,j,k,v,x,y,a,isr;
    scanf("%d",&t);
    while(t--)
    {
        l=r=isr=0;
        scanf("%d%d",&m,&n);
        for(i=0; i<m; i++)
            scanf("%s",arr[i]);
        for(i=0; i<m; i++)
        for(j=0; j<n; j++)
        {
            if(arr[i][j]=='f')
                done[i][j] = INT_MAX;
            else if(arr[i][j]=='r')
            {
                isr=1;
                done[i][j] = 0;
                queue[r++]=i*n+j;
            }
        }
        while(r!=l)
        {
            v = queue[l++];
            y = v%n;
            x = v/n;
            a = done[x][y];

            if(x!=0 && arr[x-1][y]=='f' && done[x-1][y]==INT_MAX){queue[r++]=(x-1)*n+y;done[x-1][y]=a+1;}
            if(x!=m-1 && arr[x+1][y]=='f' && done[x+1][y]==INT_MAX){queue[r++]=(x+1)*n+y;done[x+1][y]=a+1;}
            if(y!=0 && arr[x][y-1]=='f' && done[x][y-1]==INT_MAX){queue[r++]=x*n+y-1;done[x][y-1]=a+1;}
            if(y!=n-1 && arr[x][y+1]=='f' && done[x][y+1]==INT_MAX){queue[r++]=x*n+y+1;done[x][y+1]=a+1;}
        }
        a=1;
        max = (isr)?0:-1;
        for(i=0; i<m && a; i++)
        for(j=0; j<n && a; j++)
        if(arr[i][j]=='f')
        {
            if(done[i][j]==INT_MAX)
            {
                max=-1;
                a=0;
                break;
            }
            else if(max < done[i][j])
                max = done[i][j];
        }
        printf("%d\n",max);
    }
    return 0;
}
