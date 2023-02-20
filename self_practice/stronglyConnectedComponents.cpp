#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include "topologicalSorting.cpp"

using namespace std;

class StronglyConnectedComponents
{
    private:
        bool* marked;
        int* id;
        int count;
    public:
        StronglyConnectedComponents(Graph G)
        {
            int v = G.getV();
            marked = new bool[v];
            id = new int[v];
            count = 0;

            TopologicalSorting TS(G.reverseGraph());

            for(List<int>::iterator it = TS.order.begin(); it!=NULL; ++it)
            {
                if(!marked[*it])
                {
                    dfs(G,*it);
                    count++;
                }
            }
        }
        void dfs(Graph G, int s)
        {
            marked[s]=true;
            id[s]=count;
            for(List<int>::iterator it=G.getAdj(s).begin(); it!=NULL; ++it)
                if(!marked[*it])
                    dfs(G,*it);
        }
        int getCount()
        {
            return count;
        }
        bool isStronglyConnected(int u, int v)
        {
            return (id[u]==id[v]);
        }
};

int main()
{
    int j,e,v,w,u;
    scanf("%d",&v);
    Graph G(v);
    scanf("%d%d",&u,&w);
    while(u!=-1)
    {
        G.addEdge(u,w);
        scanf("%d%d",&u,&w);
    }
    G.displayGraph();

    StronglyConnectedComponents cc(G);
    cout << cc.getCount() << endl;

    cin >> u >> v;
    while(u!=-1)
    {
        if(cc.isStronglyConnected(u,v))
            cout << "connected" << endl;
        else
            cout << "not connected" << endl;
        cin >> u >> v;
    }
}
