#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include "weightedDigraph.cpp"
#include "indexMinPQ.cpp"
using namespace std;

class DijkstraShortestPath
{
    private:
        int* edgeTo;
        double* distTo;
        int s;
        int v;
    public:
        DijkstraShortestPath(WeightedDiGraph G, int _s)
        {
            s = _s;
            v = G.getV();
            IndexMinPQ<double> pq(v+1);
            edgeTo = new int[v];
            distTo = new double[v];
            for(int i=0; i<v; i++)
            {
                edgeTo[i] = -1;
                distTo[i] = INT_MAX;
            }
            distTo[s] = 0;
            pq.insert(s, 0);
            while(!pq.isEmpty())
            {
                int a = pq.delMin();
                for(List<double>::iterator it=G.getAdj(a).begin(); it!=NULL; ++it)
                {
                    int u = (*it)->from();
                    int w = (*it)->to();
                    if(distTo[u] + (*it)->getData() < distTo[w])
                    {
                        distTo[w] = distTo[u] + (*it)->getData();
                        edgeTo[w] = u;
                        if(pq.contains(w)) pq.change(w, (*it)->getData());
                        else               pq.insert(w, (*it)->getData());
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
        void displayDijkstraResult()
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
        DijkstraShortestPath sp(G, j);
        sp.displayDijkstraResult();
        cin >> j;
        delete &sp;
    }
    return 0;
}
