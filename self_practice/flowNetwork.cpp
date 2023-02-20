#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include "listForFF.cpp"
using namespace std;

class FlowNetwork
{
    private:
        int V;
        List<int>* adj;
    public:
        FlowNetwork(int v)
        {
            V=v;
            adj = new List<int>[V];
        }

        int getV(){return V;}

        void addEdge(int u, int v, int cap)
        {
            FlowEdge<int>* temp = new FlowEdge<int>(u,v,cap);
            adj[u].pushFront(temp);
            adj[v].pushFront(temp);
        }

        void displayFlowNetwork()
        {
            for(int i=0; i<V; i++)
            {
                cout << "----" << i << "----" << endl;
                adj[i].displayList();
                cout << endl;
            }
        }
        List<int>& getAdj(int t){return adj[t];}
};

/*int main()
{
    int i,j,k,u,v,w,t;

    cin >> i;
    FlowNetwork G(i);

    cin >> u >> v >> t;
    while(u!=-1)
    {
        G.addEdge(u,v,t);
        cin >> u >> v >> t;
    }
    G.displayFlowNetwork();
}
*/
