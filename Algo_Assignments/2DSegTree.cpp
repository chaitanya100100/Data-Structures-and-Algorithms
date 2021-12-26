#include<bits/stdc++.h>
using namespace std;

#define M 1000000007
#define LL long long
#define PB push_back
#define MP make_pair
#define F first
#define S second
#define VI vector<int>
#define SZ(a) int(a.size())
#define TR(c, it) for(typeof((c).begin()) it=(c).begin(); it!=(c).end(); it++ )
#define PR(arr, a, b) {for(int ii=a; ii<b; ii++)printf("%d ",arr[ii]);printf("\n");}
#define AL 100

int arr[AL][AL],n,m;
int rowSeg[AL][4*AL+2];
int colSeg[4*AL+2][4*AL+2];
int yaad[AL];
int T=0;

void buildSeg(int arr[], int seg[], int id, int l, int r)
{
	if(l==r){seg[id]=arr[l];return;}
	int m=(l+r)/2;
	buildSeg(arr, seg, 2*id, l, m);
	buildSeg(arr, seg, 2*id+1, m+1, r);
	seg[id] = min(seg[2*id], seg[2*id+1]);
	return;
}

void buildSegSeg(int idx, int arr[][4*AL+2], int seg[], int id, int l, int r)
{
	if(l==r){seg[id]=arr[l][idx];return;}
	int m=(l+r)/2;
	buildSegSeg(idx, arr, seg, 2*id, l, m);
	buildSegSeg(idx, arr, seg, 2*id+1, m+1, r);
	seg[id] = min(seg[2*id], seg[2*id+1]);
	return;
}

int queryRow(int seg[], int id, int l, int r, int L, int R)
{
	if(L<=l && r<=R) return seg[id];
	if(l>R || r<L) return INT_MAX;
	int m=(l+r)/2;
	return min(queryRow(seg, 2*id, l, m, L, R), queryRow(seg, 2*id+1, m+1, r, L, R));
}

int queryCol(int id, int l, int r, int R1, int C1, int R2, int C2)
{
	if(C1<=l && r<=C2)return queryRow(colSeg[yaad[id]], 1, 0, n-1, R1, R2);
	if(C2<l || C1>r)return INT_MAX;
	int m=(l+r)/2;
	return min( queryCol(2*id, l, m, R1, C1, R2, C2), queryCol(2*id+1, m+1, r, R1, C1, R2, C2) );
}

void updateSecond(int seg[], int id, int l, int r, int R, int V)
{
	if(l==r)
	{
		if(l==R)
			seg[id] = V;
		return;
	}
	int m=(l+r)/2;
	if(R<=m)
		updateSecond(seg, 2*id, l, m, R, V);
	else
		updateSecond(seg, 2*id+1, m+1, r, R, V);
	seg[id] = min(seg[2*id], seg[2*id+1]);
}

void updateFirst(int seg[], int id, int l, int r, int R, int C, int V)
{
	if(l==r)
	{
		if(l==C)
		{
			seg[id] = V;
			updateSecond(colSeg[yaad[id]], 1, 0, n-1, R, V);
		}
		return;
	}
	int m=(l+r)/2;
	if(C<=m)
		updateFirst(seg, 2*id, l, m, R, C, V);
	else
		updateFirst(seg, 2*id+1, m+1, r, R, C, V);

	seg[id] = min(seg[2*id], seg[2*id+1]);
	updateSecond(colSeg[yaad[id]], 1, 0, n-1, R, seg[id]);
}

void display()
{
	int i,j;
	printf("\n");
	for(i=0; i<n; i++,printf("\n"))
		for(j=0; j<m; j++)
			printf("%d ",arr[i][j]);
	printf("\n");
	for(i=0; i<n; i++)
		PR(rowSeg[i], 0, 4*m+2)
	printf("\n");
	PR(yaad, 0, 4*n+2)
	printf("\n");
	for(i=0; i<T; i++)
		PR(colSeg[i], 0, 4*n+2);
	printf("\n\n------------------------------\n\n");
}

int main()
{
	int i,j,k;
	cin >> n >> m;
	for(i=0; i<n; i++)
		for(j=0; j<m; j++)
			cin >> arr[i][j];
	
	for(i=0; i<n; i++)
		for(j=0; j<4*m+2; j++)
			rowSeg[i][j]=-1;

	for(i=0; i<n; i++)
		buildSeg(arr[i], rowSeg[i], 1, 0, m-1);
	
	for(i=0; i<4*m+2; i++)
		if(rowSeg[0][i]!=-1)
		{
			yaad[i] = T;
			buildSegSeg(i, rowSeg, colSeg[T++], 1, 0, n-1);
		}
	int op,r1,r2,c1,c2;
	while(1)
	{
		cin >> op;
		if(op==1)
		{
			cin >> r1 >> c1 >> r2 >> c2;
			cout << queryCol(1, 0, m-1, r1, c1, r2, c2) << endl;
		}
		else if(op==2)
		{
			cin >> r1 >> c1 >> r2;
			arr[r1][c1] = r2;
			updateFirst(rowSeg[r1], 1, 0, m-1, r1, c1, r2);
			//display();
		}
	}
	return 0;
}

