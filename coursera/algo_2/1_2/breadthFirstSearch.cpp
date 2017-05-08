#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include "graph.cpp"
#include "queue.cpp"
using namespace std;


class BreadthFirstPaths
{
    private:
        bool* marked;
        int* edgeTo;
        int s;
    public:
        BreadthFirstPaths(Graph G, int u)
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
            bfs(G,s);
        }
        void bfs(Graph G, int s)
        {
            marked[s]=true;
            Queue<int> q;
            q.enqueue(s);

            while(!q.isEmpty())
            {
                int v = q.dequeue();
                for(List<int>::iterator i=G.getAdj(v).begin(); i!=NULL; ++i)
                {
                    if(!marked[*i])
                    {
                        marked[*i]=true;
                        edgeTo[*i]=v;
                        q.enqueue(*i);
                    }
                }
            }
        }
        void displayBFSResult(Graph G)
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
            for(int x=v; x!=s; x=edgeTo[x])
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
    BreadthFirstPaths d(G,j);
    d.displayBFSResult(G);

    cin >> w;
    d.pathTo(w);
    cin >> j;
    }

    return 0;
}
