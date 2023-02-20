#include<iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;

template<class T>
class List;
template<class T>
class Node;
template<class T>
class FlowEdge;

template <class pNode>
class Iterator
{
    private:
        friend class List<typename pNode::valueType>;
        pNode* cur;
    public:
        Iterator(pNode* t){cur = t;}
        void operator++(){cur = cur->next;}
        bool operator!=(Iterator<pNode> r){return (r.cur!=cur);}
        bool operator==(Iterator<pNode> r){return (r.cur==cur);}
        typename pNode::dataType operator*(){return cur->data;}
};

template <class T>
class Node
{
    private:
        FlowEdge<T>* data;
        Node<T>* next;
        friend class FlowEdge<T>;
        friend class Iterator<Node<T> >;
        friend class List<T>;
    public:
        //Node<T>& getPtr(){return data};
        typedef T valueType;
        typedef FlowEdge<T>* dataType;
};


template<class T>
class FlowEdge
{
    private:
        int u;
        int v;
        T capacity;
        T flow;
        FlowEdge<T>* next;
        friend class Iterator<Node<T> >;
        friend class List<T>;
    public:
        FlowEdge(){}
        FlowEdge(int _u, int _v, T cap){u=_u;v=_v;capacity=cap;flow=0;}
        int to(){return v;}
        int from(){return u;}
        int other(int a){if(u==a)return v;return u;}
        T getCapacity(){return capacity;}
        T getFlow(){return flow;}

        void addResidualFlowTo(int a, T delta)
        {
            if(u==a)
                flow -= delta;
            else if(v==a)
                flow += delta;
        }
        T residualCapacityTo(int a)
        {
            if(u==a)
                return flow;
            else if(v==a)
                return capacity-flow;
        }

        void displayEdge(){cout << u << "->" << v << ":" << flow << " / " << capacity;}
        typedef T valueType;
};

template <class T>
class List
{
    private:
        Node<T>* root;
        int size;
    public:
        typedef Iterator<Node<T> > iterator;
        typedef T valueType;
        List()
        {
            root=NULL;
            size=0;
        }
        void pushFront(FlowEdge<T>* ptr)
        {
            Node<T>* temp = new Node<T>;
            temp->data = ptr;
            temp->next = NULL;
            if(root)
            {
                temp->next = root;
                root = temp;
            }
            else
                root = temp;
            size++;
        }
        int getSize()
        {
            return size;
        }
        iterator begin(){return iterator(root);}
        iterator end(){return iterator(NULL);}
        void displayList()
        {
            Node<T>* cur=root;
            while(cur)
            {
                cur->data->displayEdge();
                cout << endl;
                cur=cur->next;
            }
            //cout << endl;
        }
};

/*int main()
{
    List<int> ll;
    int p,t;
    cin >> t >> p;
    while(t!=-1)
    {
        if(t==1)
            ll.pushBack(p);
        else
            ll.pushFront(p);
        ll.displayList();
        cin >> t >> p;
    }
    for(List<int>::iterator iter=ll.begin();iter != ll.end(); ++iter)
        cout << *iter << " ";
    return 0;
}*/
