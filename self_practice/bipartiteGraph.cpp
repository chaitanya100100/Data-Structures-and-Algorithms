#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include "graph.cpp"
using namespace std;

class BipartiteGraph
{
    private:
        bool * marked;
        bool * partition;
        bool isBipartite;
    public:
        BipartiteGraph(Graph G)
        {
            marked = new bool[G.getV()];
            partition = new bool[G.getV()];
            isBipartite = true;

            for(int i=0; i<G.getV(); i++)
            {
                if(!isBipartite)
                    break;
                if(!marked[i])
                    dfs(G, i, true);
            }
        }

        void dfs(Graph G, int v, bool part)
        {
            marked[v] = true;
            partition[v] = part;
            int j;

            for(;(j=G.getAdj(v).iterable())!=-1;)
            {
                if(!isBipartite)return;
                if(!marked[j])
                    dfs(G, j, !part);
                else if(partition[j]==part)
                {
                    isBipartite = false;
                    return;
                }
            }
        }
        bool getIsBipartite()
        {
            return isBipartite;
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

    BipartiteGraph bg(G);

    if(bg.getIsBipartite())
        cout << "Bipartite" << endl;
    else
        cout << "Not Bipartite" << endl;
    return 0;
}
