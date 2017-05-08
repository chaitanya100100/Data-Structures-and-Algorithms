#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include "list.cpp"
using namespace std;

class WeightedGraph
{
    private:
        List<double>* adj;
        int V;
    public:
        WeightedGraph(int v)
        {
            adj = new List<double>[v];
            V=v;
        }
        void addEdge(int u, int v, double d)
        {
            adj[u].pushFront(u, v, d);
            adj[v].pushFront(v, u, d);
        }
        int getV()
        {
            return V;
        }
        int degree(int u)
        {
            return adj[u].getSize();
        }
        int totalDegreeOfGraph()
        {
            int sum = 0;
            for(int i=0; i<V; i++)
                sum+=degree(i);
            return sum;
        }
        int maxDegree()
        {
            int max = 0;
            for(int i=0; i<V; i++)
                if(degree(i)>max)max=degree(i);
            return max;
        }
        double averageDegree()
        {
            return (double(totalDegreeOfGraph())/double(V));
        }
        int getE()
        {
            return totalDegreeOfGraph()/2;
        }
        List<double>& getAdj(int u)
        {
            return adj[u];
        }
        void displayGraph()
        {
            for(int i=0; i<V; i++)
            {
                adj[i].displayList();
            }
        }
        /*WeightedGraph reverseGraph()
        {
            WeightedGraph RG(V);
            for(int i=0; i<V; i++)
            {
                for(List<double>::iterator it=adj[i].begin(); it!=NULL; ++it)
                RG.addEdge((*it)->other(u), (*it)->other(v), (*it)->getData());
            }
            return RG;
        }*/
};

/*int main()
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
    cout << "E = " << G.getE();
    return 0;
}*/
