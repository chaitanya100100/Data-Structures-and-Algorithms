#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include "list.cpp"
using namespace std;

class Graph
{
    private:
        List<int>* adj;
        int V;
    public:
        Graph(int v)
        {
            adj = new List<int>[v];
            V=v;
        }
        void addEdge(int u, int v)
        {
            adj[u].pushFront(v);
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
        List<int>& getAdj(int u)
        {
            return adj[u];
        }
        void displayGraph()
        {
            for(int i=0; i<V; i++)
            {
                cout << i << " : " << "Total-" << outDegree(i) << " : ";
                adj[i].displayList();
            }
        }
        Graph reverseGraph()
        {
            Graph RG(V);
            for(int i=0; i<V; i++)
            {
                for(List<int>::iterator it=adj[i].begin(); it!=NULL; ++it)
                RG.addEdge(*it,i);
            }
            return RG;
        }
};

/*int main()
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
    Graph RG=G.reverseGraph();
    RG.displayGraph();
    cout << "Total Degree : " << G.totalDegreeOfGraph() << endl;
    cout << "Max total-Degree : " << G.maxTotalDegree() << endl;
    cout << "Max in-Degree : " << G.maxInDegree() << endl;
    cout << "Max out-Degree : " << G.maxOutDegree() << endl;
    cout << "Average total-Degree : " << G.averageTotalDegree() << endl;
    cout << "Average in-Degree : " << G.averageInDegree() << endl;
    cout << "Average out-Degree : " << G.averageOutDegree() << endl;
    cout << "Edges : " << G.getE() << endl;
    return 0;
}*/
