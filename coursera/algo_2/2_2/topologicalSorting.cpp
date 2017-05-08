#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include "weightedDiGraph.cpp"
using namespace std;

class TopologicalSorting
{
    private:
        bool* marked;
        List<int> order;
    public:
        TopologicalSorting(WeightedDiGraph G)
        {
            int v = G.getV();
            marked = new bool[v];
            for(int i=0; i<v; i++)
                marked[i]=false;
            for(int i=0; i<v; i++)
                if(!marked[i])
                    dfs(G,i);
        }
        void dfs(WeightedDiGraph G, int v)
        {
            marked[v]=true;
            for(List<double>::iterator i=G.getAdj(v).begin(); i!=NULL; ++i)
            if(!marked[(*i)->to()])
                dfs(G,(*i)->to());
            order.pushFront(v, v, 0);
        }
        void printTSResult()
        {
            order.displayList();
        }
        friend class ShortestPathInDAG;
};

/*int main()
{
    int j,e,v,w,u;
    double d;
    scanf("%d",&v);
    WeightedDiGraph G(v);

    cin >> u >> v >> d;
    while(u!=-1)
    {
        G.addEdge(u,v,d);
        cin >> u >> v >> d;
    }

    G.displayGraph();


    TopologicalSorting ts(G);
    cout << "done\n";
    ts.printTSResult();
    return 0;
}*/
