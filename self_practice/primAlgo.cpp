#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "weightedGraph.cpp"
#include "indexMinPQ.cpp"
using namespace std;

class MSTWithPrim
{
    private:
        List<double> mst;
        bool* marked;
        bool* added;
        int* edgeTo;
    public:
        MSTWithPrim(WeightedGraph G)
        {
            int v = G.getV();
            marked = new bool[v];
            added = new bool[v];
            edgeTo = new int[v];
            for(int i=0; i<v; i++)
            {marked[i]=added[i]=false;edgeTo[i]=-1;}
            IndexMinPQ<double> pq(v+1);
            int u=0;
            marked[u]=true;
            do
            {
                added[u]=true;
                for(List<double>::iterator it=G.getAdj(u).begin(); it!=NULL; ++it)
                {
                    int w = (*it)->other(u);
                    if(!marked[w])
                    {
                        pq.insert(w, (*it)->getData());
                        marked[w]=true;
                        edgeTo[w] = u;
                    }
                    else if( (*it)->getData() < pq.keyAt(w) && !added[w])
                    {
                        pq.change(w, (*it)->getData());
                        edgeTo[w] = u;
                    }
                }
                cout << "--------\n";
                    mst.displayList();
                    pq.displayIndexMinPQ();
                cout << "--------\n";

                int a = pq.delMin();
                mst.pushFront(a, edgeTo[a], pq.keyAt(a));
                u=a;
            }while(!pq.isEmpty());
        }
        void displayPrimResult()
        {
            mst.displayList();
        }
};


int main()
{
    int j,e,v,w,u;
    double d;
    scanf("%d",&v);
    WeightedGraph G(v);

    cin >> u >> v >> d;
    while(u!=-1)
    {
        G.addEdge(u,v,d);
        cin >> u >> v >> d;
    }
    G.displayGraph();

    MSTWithPrim mk(G);
    mk.displayPrimResult();

    return 0;
}
