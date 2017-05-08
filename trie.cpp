#include<bits/stdc++.h>
using namespace std;

#define M 26

struct node
{
        struct node* ptr[M];
        bool isLeaf;
};

node* root;

node* newNode()
{
        node* pnew = new node;
        pnew->isLeaf = false;
        for(int i=0; i<M; i++)
                pnew->ptr[i]=NULL;
        return pnew;
}

void insert(char* str)
{
        int i,j,l=strlen(str);
        node* cur=root;

        for(i=0; i<l; i++)
        {
                j=str[i]-'a';
                if(!cur->ptr[j])
                        cur->ptr[j] = newNode();
                cur = cur->ptr[j];
        }
	cur->isLeaf=true;
}

void delete_word(char* str)
{
	int i,j,l=strlen(str);
	node* cur=root;
	for(i=0; i<l; i++)
	{
		j=str[i]-'a';
		cur=cur->ptr[j];	
	}
	cur->isLeaf=false;
		
}

bool find(char* str)
{
	int i,j,l=strlen(str);
	node* cur=root;
	
	for(i=0; i<l; i++)
	{
		if(cur==NULL)return false;
		j=str[i]-'a';
		if(cur->ptr[j]==NULL)return false;
		cur = cur->ptr[j];
	}
	return cur->isLeaf==true;
}

int main()
{
	int i,j,k;
	char arr[100];
	root = new node;
	cin >> j;
	while(j!=-1)
	{
		cin >> arr;
		if(j==0)insert(arr);
		else if(j==1)cout << find(arr) << endl;
		else if(j==2) delete_word(arr);
		cin >> j;
	}
}
