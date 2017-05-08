#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include "graph.cpp"
using namespace std;

class DepthFirstPaths
{
    private:
        bool* marked;
        int* edgeTo;
        int s;
    public:
        DepthFirstPaths(Graph G, int u)
        {
            int v=G.getV();
            marked = new bool[v];
            edgeTo = new int[v];
            for(int i=0; i<v; i++)
            {
                marked[i]=false;
                edgeTo[i]=-1;
            }
            s=u;
            dfs(G, s);
        }
        void dfs(Graph G, int v)
        {
            marked[v]=true;
            for(List<int>::iterator iter=G.getAdj(v).begin(); iter!=NULL; ++iter)
            if(!marked[*iter])
            {
                dfs(G,*iter);
                edgeTo[*iter]=v;
            }
        }
        void displayDFSResult(Graph G)
        {
            cout << "connected to " << s << " : ";
            for(int i=0; i<G.getV(); i++)
            {
                if(marked[i])
                    cout << i << " ";
            }
            cout << endl;
        }
        bool hasPathTo(int v)
        {
            return marked[v];
        }
        void pathTo(int v)
        {
            if(!hasPathTo(v))return;
            for(int x = v; x!=s; x=edgeTo[x])
                cout << x << " ";
            cout << s << endl;
        }
};

int main()
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

    cin >> j;
    while(j!=-1){
    DepthFirstPaths d(G,j);
    d.displayDFSResult(G);

    cin >> w;
    d.pathTo(w);
    cin >> j;
    }

    return 0;
}
