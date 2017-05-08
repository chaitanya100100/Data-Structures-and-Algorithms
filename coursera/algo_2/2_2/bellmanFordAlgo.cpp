#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include "weightedDigraph.cpp"
using namespace std;

class BellmanFordSP
{
    private:
        int* edgeTo;
        double* distTo;
        int s;
        int v;
    public:
        BellmanFordSP(WeightedDiGraph G, int _s)
        {
            s = _s;
            v = G.getV();
            edgeTo = new int[v];
            distTo = new double[v];
            for(int i=0; i<v; i++)
            {
                edgeTo[i] = -1;
                distTo[i] = INT_MAX;
            }
            distTo[s] = 0;

            for(int i=0; i<v; i++)
            for(int j=0; j<v; j++)
            for(List<double>::iterator it=G.getAdj(j).begin(); it!=NULL; ++it)
            {
                int u = (*it)->from();
                int v = (*it)->to();
                if(distTo[v] > distTo[u] + (*it)->getData())
                {
                    distTo[v] = distTo[u] + (*it)->getData();
                    edgeTo[v] = u;
                }
            }

        }
        void displayPathTo(int i)
        {
            for(;i>=0 && i!=s; i=edgeTo[i])
                cout << i << " ";
            cout << s;
        }
        void displayBellmanFordResult()
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
    while(j!=-1)
    {
        BellmanFordSP sp(G, j);
        sp.displayBellmanFordResult();
        cin >> j;
        delete &sp;
    }
    return 0;
}
