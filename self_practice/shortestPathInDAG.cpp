#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include "topologicalSorting.cpp"
using namespace std;

class ShortestPathInDAG
{
    private:
        int* edgeTo;
        double* distTo;
        int s;
        int v;
    public:
        ShortestPathInDAG(WeightedDiGraph G, int _s)
        {
            s=_s;
            v = G.getV();
            edgeTo = new int[v];
            distTo = new double[v];
            for(int i=0; i<v; i++)
            {
                edgeTo[i] = -1;
                distTo[i] = INT_MAX;
            }
            distTo[s]=0;
            TopologicalSorting ts(G);

            for(List<int>::iterator it=ts.order.begin(); it!=NULL; ++it)
            {
                int a = (*it)->to();
                for(List<double>::iterator it2=G.getAdj(a).begin(); it2!=NULL; ++it2)
                {
                    int p = (*it2)->from();
                    int q = (*it2)->to();
                    if(distTo[q] > distTo[p] + (*it2)->getData())
                    {
                        edgeTo[q] = p;
                        distTo[q] = distTo[p] + (*it2)->getData();
                    }
                }
            }
        }
        void displayPathTo(int i)
        {
            for(; i!=s; i=edgeTo[i])
                cout << i << " ";
            cout << s;
        }
        void displaySPInDAGResult()
        {
            for(int i=0; i<v; i++)
            {
                cout << i << " : " << distTo[i] << " : ";
                displayPathTo(i);
                cout << endl;
            }
        }
};

int main()
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

    cin >> j;
    ShortestPathInDAG sp(G, j);
    sp.displaySPInDAGResult();
    return 0;
}
