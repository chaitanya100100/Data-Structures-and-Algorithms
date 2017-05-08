#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
using namespace std;

class UnionFind
{
    private:
        int* id;
        int n;
    public:
        UnionFind(int v)
        {
            n=v;
            id = new int[v];
            for(int i=0; i<v; i++)
                id[i]=i;
        }
        int root(int i)
        {
            while(id[i]!=i)
            {
                id[i]=id[id[i]];
                i = id[i];
            }
            return i;
        }
        void makeUnion(int a, int b)
        {
            id[root(b)]=root(a);
        }
        bool connected(int a, int b)
        {
            return (root(a)==root(b));
        }
};

/*int main()
{
    UnionFind uf(20);
    int t,a,b;
    cin >> t;
    while(t!=-1)
    {
        cin >> a >> b;
        if(t==1)
            uf.makeUnion(a,b);
        else if(t==2)
            cout << uf.connected(a,b) << endl;
        cin >> t;
    }
    return 0;
}*/
