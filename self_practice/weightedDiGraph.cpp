#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include "list.cpp"
using namespace std;

class WeightedDiGraph
{
    private:
        List<double>* adj;
        int V;
    public:
        WeightedDiGraph(int v)
        {
            adj = new List<double>[v];
            V=v;
        }
        void addEdge(int u, int v, double d)
        {
            adj[u].pushFront(u, v, d);
        }
        int getV()
        {
            return V;
        }
        int outDegree(int u)
        {
            return adj[u].getSize();
        }
        int inDegree(int u)
        {
            int count=0;
            for(int i=0; i<V; i++)
            if(adj[i].contains(u))count++;
            return count;
        }
        int totalDegree(int u)
        {
            return inDegree(u)+outDegree(u);
        }
        int totalDegreeOfGraph()
        {
            int sum = 0;
            for(int i=0; i<V; i++)
                sum+=outDegree(i);
            return sum*2;
        }
        int maxOutDegree()
        {
            int max = 0;
            for(int i=0; i<V; i++)
                if(outDegree(i)>max)max=outDegree(i);
            return max;
        }
        int maxInDegree()
        {
            int j,max = 0;
            for(int i=0; i<V; i++)
                if((j=inDegree(i))>max)max=j;
            return max;
        }
        int maxTotalDegree()
        {
            int max = 0;
            for(int i=0; i<V; i++)
                if(totalDegree(i)>max)max=totalDegree(i);
            return max;
        }
        double averageTotalDegree()
        {
            return (double(totalDegreeOfGraph())/double(V));
        }
        double averageInDegree()
        {
            return (averageTotalDegree()/2.0);
        }
        double averageOutDegree()
        {
            return (averageTotalDegree()/2.0);
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
        WeightedDiGraph reverseGraph()
        {
            WeightedDiGraph RG(V);
            for(int i=0; i<V; i++)
            {
                for(List<double>::iterator it=adj[i].begin(); it!=NULL; ++it)
                RG.addEdge((*it)->to(), (*it)->from(), (*it)->getData());
            }
            return RG;
        }
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
    cout << "E = " << G.getE() << endl;
    return 0;
}*/
