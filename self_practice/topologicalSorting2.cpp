#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include "graph.cpp"
#include "stack.cpp"
using namespace std;

class TopologicalSorting
{
    private:
        bool* marked;
        Stack<int> order;
    public:
        TopologicalSorting(Graph G)
        {
            int v;
            marked = new bool[v];
            for(int i=0; i<v; i++)
                marked[i]=false;
            for(int i=0; i<v; i++)
                if(!marked[i])
                    dfs(G,i);
        }
        void dfs(Graph G, int v)
        {
            marked[v]=true;
            for(List<int>::iterator i=G.getAdj(v).begin(); i!=NULL; ++i)
            if(!marked[*i])
                dfs(G,*i);
            order.push(v);
        }
        void printTSResult()
        {
            order.printStack();
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
    G.displayGraph();

    TopologicalSorting TS(G);
    TS.printTSResult();
    return 0;
}
