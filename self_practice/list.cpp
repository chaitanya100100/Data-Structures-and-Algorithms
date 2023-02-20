#include<iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;

template<class T>
class List;

template <class pNode>
class Iterator
{
    private:
        friend class List<typename pNode::valueType>;
        pNode* cur;
    public:
        Iterator(pNode* t){cur = t;}
        void operator++(){cur = cur->next;}
        void operator--(){cur = cur->prev;}
        bool operator!=(Iterator<pNode> r){return (r.cur!=cur);}
        bool operator==(Iterator<pNode> r){return (r.cur==cur);}
        pNode* operator*(){return cur;}
};

template<class T>
class Edge
{
    private:
        int u;
        int v;
        T data;
        Edge<T>* next;
        Edge<T>* prev;
        friend class Iterator<Edge<T> >;
        friend class List<T>;
    public:
        Edge(){}
        Edge(int _u, int _v, T d){data=d;u=_u;v=_v;prev=next=NULL;}
        Edge(int _u, int _v, T d, Edge<T>* _next){data=d;u=_u;v=_v;next=_next;prev=NULL;}
        Edge(Edge<T>* _prev, int _u, int _v, T d){data=d;u=_u;v=_v;prev=_prev;next=NULL;}
        int to(){return v;}
        int from(){return u;}
        T getData(){return data;}
        int compareTo(Edge e)
        {
            if(data<e.data)return -1;
            if(data>e.data)return 1;
            return 0;
        }
        void set(int _u, int _v, T d){u=_u;v=_v;data=d;}
        typedef T valueType;
};

template <class T>
class List
{
    private:
        Edge<T>* root;
        int size;
    public:
        typedef Iterator<Edge<T> > iterator;
        typedef T valueType;
        List()
        {
            root=NULL;
            size=0;
        }
        void pushBack(int u, int v, T data)
        {
            if(root)
            {
                Edge<T>* iter = root;
                for(;iter->next!=NULL;iter=iter->next);
                iter->next = new Edge<T>(u, v, data);
                iter->next->prev = iter;
            }
            else
                root = new Edge<T>(u,v,data);
            size++;
        }
        void pushFront(int u, int v, T data)
        {
            if(root)
            {
                Edge<T>* temp = new Edge<T>(u, v, data);
                temp->next = root;
                root = temp;
            }
            else
                root = new Edge<T>(u, v, data);
            size++;
        }
        int getSize()
        {
            return size;
        }
        bool containsData(T data)
        {
            for(Edge<T>* iter = root; iter!=NULL; iter=iter->next)
            {
                if(iter->data==data)return true;
            }
            return false;
        }
        bool contains(int t)
        {
            for(Edge<T>* iter = root; iter!=NULL; iter=iter->next)
            {
                if(iter->v==t)return true;
            }
            return false;
        }
        iterator begin(){return iterator(root);}
        iterator end(){return iterator(NULL);}
        void displayList()
        {
            Edge<T>* cur=root;
            while(cur)
            {
                cout << cur->u << "-" << cur->v << " : " << cur->data << endl;
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
