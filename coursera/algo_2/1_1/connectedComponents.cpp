#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include "graph.cpp"
using namespace std;

class ConnectedComponents
{
    private:
        bool * marked;
        int * id;
        int count;
    public:
        ConnectedComponents(Graph G)
        {
            marked = new bool[G.getV()];
            for(int i=0; i<G.getV(); i++)
                marked[i]=false;
            id = new int[G.getV()];
            count = 0;

            for(int i=0; i<G.getV(); i++)
            {
                if(!marked[i])
                {
                    dfs(G, i);
                    count++;
                }
            }
        }
        void dfs(Graph G, int v)
        {
            marked[v] = true;
            id[v] = count;
            int j;
            for(; (j=G.getAdj(v).iterable())!=-1;)
            {
                if(!marked[j])
                    dfs(G, j);
            }
        }
        int getCount()
        {
            return count;
        }
        int getId(int v)
        {
            return id[v];
        }
        bool isConnected(int u, int v)
        {
            return (id[u]==id[v]);
        }
};

int main()
{
    int j,e,v,w,u;
    scanf("%d%d",&v,&e);
    Graph G(v);
    for(int i=0; i<e; i++)
    {
        scanf("%d%d",&u,&w);
        G.addEdge(u,w);
    }
    G.display();

    ConnectedComponents cc(G);
    cout << cc.getCount() << endl;

    cin >> u >> v;
    while(u!=-1)
    {
        if(cc.isConnected(u,v))
            cout << "connected" << endl;
        else
            cout << "not connected" << endl;
        cin >> u >> v;
    }
}
