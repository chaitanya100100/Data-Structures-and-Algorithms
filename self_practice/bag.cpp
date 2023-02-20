#include<iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;

template<class T>
struct node
{
    T val;
    node* next;
};

template<class T>
class Bag
{
    private:
        int size;
        int iter,iter2;
        node<T> * root;
    public:
        Bag()
        {
            iter=iter2=0;
            size=0;
            root=NULL;
        }
        void add(T v)
        {
            node<T>* pnew = new node<T>;
            pnew->val = v;
            pnew->next = NULL;
            size++;
            if(root==NULL)
            {
                root=pnew;
                return;
            }
            node<T>* cur=root;
            while(cur->next != NULL)
                cur=cur->next;
            cur->next = pnew;
            return;
        }
        int getSize()
        {
            return size;
        }
        int getIter()
        {
            return iter;
        }
        node<T>* getRoot()
        {
            return root;
        }
        void display()
        {
            node<T>* cur=root;
            while(cur!=NULL)
            {
                cout << cur->val << " ";
                cur = cur->next;
            }
            cout << endl;
        }
        /*void remove(int v)
        {
            node<T>* cur=root;
            while(cur!=NULL && cur->val!=v)
                cur = cur->next;
            if(cur==NULL)return;
            cur->val = -2;
        }
        void addon(int v)
        {
            node<T>* cur=root;
            while(cur!=NULL && cur->val!=-2)
                cur = cur->next;
            if(cur==NULL)return;
            cur->val = v;
        }*/
        T iterable()
        {
            node<T>* cur = root;
            if(iter == size)
            {
                iter=0;
                return -1;
            }
            for(int i=0; i<iter; i++)
                cur = cur->next;
            iter++;
            //cout << cur->val << " i" << endl;
            return cur->val;
        }
        /*T iterable2()
        {
            node<T>* cur = root;
            if(iter2 == size)
            {
                iter2=0;
                return -1;
            }
            for(int i=0; i<iter2; i++)
                cur = cur->next;
            iter2++;
            //cout << cur->val << " i" << endl;
            return cur->val;
        }*/
};

/*int main()
{
    Bag<int> bag1,bag2;
    int t,i;
    scanf("%d",&t);
    while(t!=-1)
    {
        bag1.add(t);
        bag2.add(t);
        scanf("%d",&t);
    }
    //bag.display();
    for(; i=bag1.iterable();)
    {
        cout << i << endl;
    }
    for(; i=bag2.iterable();)
    {
        cout << i << endl;
    }
    return 0;
}*/
