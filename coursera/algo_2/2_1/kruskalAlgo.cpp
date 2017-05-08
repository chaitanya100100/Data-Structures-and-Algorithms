#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "weightedGraph.cpp"
#include "UF.cpp"
using namespace std;

class MSTWithKruskal
{
    private:
        List<double> mst;
    public:
        MSTWithKruskal(WeightedGraph G)
        {
            int v = G.getV();
            int e = G.getE();
            bool am[v][v];
            Edge<double> arr[e];
            for(int i=0; i<v; i++)
            for(int j=0; j<v; j++)
                am[i][j]=false;

            int i,j=0;
            for(i=0; i<v; i++)
            for(List<double>::iterator it=G.getAdj(i).begin(); it!=NULL; ++it)
            {
                int u = (*it)->either();
                int w = (*it)->other(u);

                if(!am[u][w])
                {
                    am[u][w] = am[w][u] = true;
                    arr[j++].set(u,w,(*it)->getData());
                }
            }
            if(j!=e)cout << "something wrong\n";

            Edge<double> temp;
            for(i=0; i<e-1; i++)
            for(j=0; j<e-1-i; j++)
            if(arr[j].getData()>arr[j+1].getData())
            {
                temp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
            }

            //for(int i=0; i<e; i++)
            //    cout << arr[i].getData() << endl;

            UnionFind uf(v);
            j=0;
            for(i=0; i<e; i++)
            {
                int u = arr[i].either();
                int w = arr[i].other(u);

                if(!uf.connected(u,w))
                {
                    uf.makeUnion(u,w);
                    mst.pushFront(u,w,arr[i].getData());
                }
            }
        }
        void displayKruskalResult()
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

    MSTWithKruskal mk(G);
    mk.displayKruskalResult();

    return 0;
}
