#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include "bag.cpp"
using namespace std;

class Graph
{
    private:
        int V;
        Bag<int> * adj;
    public:
        Graph(int v)
        {
            V=v;
            adj = new Bag<int> [v];
            //for(int i=0; i<v; i++)
            //    adj[i] = new Bag<int>;
        }
        int getV()
        {
            return V;
        }
        void addEdge(int v, int w)
        {
            adj[v].add(w);
            adj[w].add(v);
        }
        int degree(int v)
        {
            return adj[v].getSize();
        }
        int totalDegree()
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
                if(degree(i)>max)
                max=degree(i);
            return max;
        }
        double averageDegree()
        {
            return double(totalDegree())/double(V);
        }
        int getE()
        {
            return totalDegree()/2;
        }
        Bag<int>& getAdj(int v)
        {
            return adj[v];
        }
        void display()
        {
            for(int i=0; i<V; i++)
            {
                cout << i << " : " << "Total " << degree(i) << " : ";
                adj[i].display();
            }
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
    G.display();

    cout << "Total Degree : " << G.totalDegree() << endl;
    cout << "Max Degree : " << G.maxDegree() << endl;
    cout << "Average Degree : " << G.averageDegree() << endl;
    cout << "Edges : " << G.getE() << endl;
    return 0;
}*/
