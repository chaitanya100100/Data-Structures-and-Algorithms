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
        typename pNode::valueType operator*(){return cur->data;}
};

template<class T>
class Node
{
    private:
        T data;
        Node<T>* next;
        Node<T>* prev;
        friend class Iterator<Node<T> >;
        friend class List<T>;
    public:
        Node(){}
        Node(T v){data=v;prev=next=NULL;}
        Node(T v, Node<T>* _next){data=v;next=_next;prev=NULL;}
        Node(Node<T>* _prev, T v){data=v;prev=_prev;next=NULL;}
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
        void pushBack(T data)
        {
            if(root)
            {
                Node<T>* iter = root;
                for(;iter->next!=NULL;iter=iter->next);
                iter->next = new Node<T>(data);
                iter->next->prev = iter;
            }
            else
                root = new Node<T>(data);
            size++;
        }
        void pushFront(T data)
        {
            if(root)
            {
                Node<T>* temp = new Node<T>(data);
                temp->next = root;
                root = temp;
            }
            else
                root = new Node<T>(data);
            size++;
        }
        int getSize()
        {
            return size;
        }
        bool contains(T data)
        {
            for(Node<T>* iter = root; iter!=NULL; iter=iter->next)
            {
                if(iter->data==data)return true;
            }
            return false;
        }
        iterator begin(){return iterator(root);}
        iterator end(){return iterator(NULL);}
        void displayList()
        {
            Node<T>* cur=root;
            while(cur)
            {
                cout << cur->data << " ";
                cur=cur->next;
            }
            cout << endl;
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
