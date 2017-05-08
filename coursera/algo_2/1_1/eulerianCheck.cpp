#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "graph.cpp"
using namespace std;

class EulerianCheck
{
    private:
        Graph* G;
    public:
        EulerianCheck(Graph P)
        {
            G = &P;
            int u=0;
            for(int i=0; i<G->getV(); i++)
                if(G->getAdj(i).getSize() & 1)
                {
                    u=i;
                    break;
                }
            printEulerPath(G,u);
            cout << endl;
        }
        void printEulerPath(Graph* G, int u)
        {
            //cout << u << endl;
            int j;
            //G->getAdj(u).display();

            for(;(j=G->getAdj(u).iterable())!=-1;)
            {
                if(j!=-2 && isValid(G,u,j))
                {
                    cout << u << "-" << j << " ";
                    removeEdge(G,u,j);
                    printEulerPath(G,j);
                }
            }
        }
        bool isValid(Graph* G, int u, int v)
        {
            int j,count=0;
            //G->getAdj(u).display();
            for(;(j=G->getAdj(u).iterable2())!=-1;)
            {
                cout << j << endl;
                if(j!=-2)count++;
            }
            if(count==1)return true;
            cout << count;
            //cin >> j;
            bool visited[G->getV()];
            memset(visited,false,G->getV());

            int c1 = dfs(G,u,visited);
            removeEdge(G,u,v);
            int c2 = dfs(G,u,visited);
            addEdge(G,u,v);
            return (c1>c2)?false:true;
        }
        void addEdge(Graph* G,int u,int v)
        {
            G->getAdj(u).addon(v);
            G->getAdj(v).addon(u);
        }
        void removeEdge(Graph* G, int u, int v)
        {
            G->getAdj(u).remove(v);
            G->getAdj(v).remove(u);
            //cout << u << " " << v << " removed\n";
        }
        int dfs(Graph* G, int u, bool visited[])
        {
            visited[u] = true;
            int j,count=1;
            for(;(j=G->getAdj(u).iterable2())!=-1;)
            {
                if(j!=-2 && !visited[j])
                    count+=dfs(G,j,visited);
            }
            return count;
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
    G.display();

    EulerianCheck ec(G);

}
