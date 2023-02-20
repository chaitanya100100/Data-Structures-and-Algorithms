#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include "graph.cpp"
using namespace std;

class CycleInGraph
{
    private:
        bool * marked;
        int * edgeTo;
        bool isCycle;
        int V;
    public:
        CycleInGraph(Graph G)
        {
            marked = new bool[G.getV()];
            edgeTo = new int[G.getV()];
            isCycle=false;
            V = G.getV();
            for(int i=0; i<G.getV(); i++)
            {
                marked[i]=false;
                edgeTo[i]=-1;
            }
            for(int i=0; i<G.getV(); i++)
            {
                if(isCycle)
                    break;
                if(!marked[i])
                {
                    marked[i]=true;
                    dfs(G, i);
                }
            }
        }
        void dfs(Graph G, int v)
        {
            int j;
            for(; (j=G.getAdj(v).iterable())!=-1;)
            {
                if(isCycle)
                    return;
                if(!marked[j])
                {
                    marked[j] = true;
                    edgeTo[j] = v;
                    dfs(G,j);
                }
                else if(edgeTo[v]!=j && isAllVisited())
                {
                    isCycle=true;
                    return;
                }
            }
        }
        bool isAllVisited()
        {
            for(int i=0; i<V; i++)
                if(!marked[i])return false;
            return true;
        }
        bool getIsCycle()
        {
            return isCycle;
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

    CycleInGraph cy(G);

    if(cy.getIsCycle())
        cout << "Yes, There is a Cycle!" << endl;
    else
        cout << "No, There isn't a Cycle!" << endl;

    return 0;
}
