#include<stdio.h>
#include<stdlib.h>
#define M (1000000007)

int n,numberOfVerticalLines=0,numberOfLines=0,prev,now,prevAns,ele;
double leftLimit,rightLimit;
double leftPoints[100005],rightPoints[100005];
int leftSorted[100005],rightSorted[100005],done[100005],qp[100005];


void merge2(int arr[], int l, int m, int r)
{
    int i,j,k,n1=m-l+1,n2=r-m;
    int a1[n1],a2[n2];
    for(i=0; i<n1; i++)
        a1[i]=arr[l+i];
    for(i=0; i<n2; i++)
        a2[i]=arr[m+1+i];
    i=j=0;k=l;
    while(i<n1 && j<n2)
    {
        if(rightPoints[a1[i]]<rightPoints[a2[j]])
            arr[k++]=a1[i++];
        else if(rightPoints[a1[i]]==rightPoints[a2[j]] && leftPoints[a1[i]]<leftPoints[a2[j]])
            arr[k++]=a1[i++];
        else
            arr[k++]=a2[j++];
    }
    while(i<n1)
        arr[k++]=a1[i++];
    while(j<n2)
        arr[k++]=a2[j++];
}

void mergeSort2(int arr[], int l, int r)
{
    if(l<r)
    {
        int m = (r-l)/2+l;
        mergeSort2(arr, l, m);
        mergeSort2(arr, m+1, r);
        merge2(arr, l, m , r);
    }
}


void merge(int arr[], int l, int m, int r)
{
    int i,j,k,n1=m-l+1,n2=r-m;
    int a1[n1],a2[n2];
    for(i=0; i<n1; i++)
        a1[i]=arr[l+i];
    for(i=0; i<n2; i++)
        a2[i]=arr[m+1+i];
    i=j=0;k=l;
    while(i<n1 && j<n2)
    {
        if(leftPoints[a1[i]]<leftPoints[a2[j]])
            arr[k++]=a1[i++];
        else if(leftPoints[a1[i]]==leftPoints[a2[j]] && rightPoints[a1[i]]<rightPoints[a2[j]])
            arr[k++]=a1[i++];
        else
            arr[k++]=a2[j++];
    }
    while(i<n1)
        arr[k++]=a1[i++];
    while(j<n2)
        arr[k++]=a2[j++];
}

void mergeSort(int arr[], int l, int r)
{
    if(l<r)
    {
        int m = (r-l)/2+l;
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
        merge(arr, l, m , r);
    }
}

int rank(int ele)
{
    int i,ans;
    if(rightPoints[ele]<rightPoints[prev])
    {
        ans=0;
        i = qp[prev] - 1;
        while(i>=0 && rightPoints[rightSorted[i]]>=rightPoints[ele])
        {
            if(!done[rightSorted[i]])ans++;
            i--;
        }
        prev = ele;
        ans = prevAns - ans;
        prevAns = ans;
        return ans;
    }
    else if(rightPoints[prev]==rightPoints[ele])
    {
        prev = ele;
        return prevAns;
    }
    else
    {
        ans=0;
        i = qp[prev] + 1;
        while(i<numberOfLines && rightPoints[rightSorted[i]]<rightPoints[ele])
        {
            if(!done[rightSorted[i]])ans++;
            i++;
        }
        prev = ele;
        ans = prevAns + ans;
        prevAns = ans;
        return ans;
    }
}

int main()
{
    int i,j,k;
    double a,b,c;

    scanf("%d%lf%lf",&n,&leftLimit,&rightLimit);
    for(i=0; i<n; i++)
    {
        scanf("%lf%lf%lf",&a,&b,&c);
        if(((int)b)==0)
        {
            if(leftLimit<(-c/a) && rightLimit>(-c/a) )
                numberOfVerticalLines++;
            else;
        }
        else
        {
            done[numberOfLines] = 0;
            qp[numberOfLines]=numberOfLines;
            leftSorted[numberOfLines] = numberOfLines;
            rightSorted[numberOfLines] = numberOfLines;
            leftPoints[numberOfLines] = (-c-a*leftLimit)/b;
            rightPoints[numberOfLines] = (-c-a*rightLimit)/b;
            numberOfLines++;
        }
    }
    //printf("1\n");
    mergeSort(leftSorted, 0, numberOfLines-1);
    //printf("2\n");
    mergeSort2(rightSorted, 0, numberOfLines-1);
    //printf("3\n");

    for(i=0; i<numberOfLines; i++)
        qp[rightSorted[i]] = i;
    //printf("4\n");

    /*for(i=0; i<numberOfLines; i++)
        printf("%Lf ",leftPoints[i]);
    printf("\n");

    for(i=0; i<numberOfLines; i++)
        printf("%Lf ",rightPoints[i]);
    printf("\n");

    for(i=0; i<numberOfLines; i++)
        printf("%d ",leftSorted[i]);
    printf("\n");

    for(i=0; i<numberOfLines; i++)
        printf("%d ",rightSorted[i]);
    printf("\n");*/

    long long int ans=0;

    prev = ele = leftSorted[0];
    for(i=0; i<numberOfLines && rightPoints[ele]>rightPoints[rightSorted[i]]; i++);
    //    printf("%Lf %Lf\n",rightPoints[ele],rightPoints[rightSorted[i]]);

    prevAns = i;
    ans = i;
    done[ele] = 1;

    /*printf("%d %d\n",prev,prevAns);

    scanf("%d",&i);*/

    for(i=1; i<numberOfLines; i++)
    {
        ele = leftSorted[i];
        j = rank(ele);
        //printf("%d\n",j);
        ans = (ans+j)%M;
        done[ele] = 1;
    }
    ans= (ans + ((long long)numberOfVerticalLines*(long long)numberOfLines)%M)%M;
    printf("%lld\n",ans);
    return 0;
}
