#include<iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;

/*template<class T>
struct node
{
    T val;
    node* next;
};*/

template<class T>
class Queue
{
    private:
        node<T>* head;
        node<T>* tail;
        int size;
    public:
        Queue()
        {
            head=NULL;
            tail=NULL;
            size=0;
        }
        bool isEmpty()
        {
            return (size==0);
        }
        void enqueue(T val)
        {
            node<T>* pnew = new node<T>;
            pnew->val = val;
            pnew->next = NULL;

            if(tail == NULL)
            {
                head = tail = pnew;
                size++;
                return;
            }
            tail->next = pnew;
            tail = pnew;
            size++;
            return;
        }
        T dequeue()
        {
            if(size==0 || head==NULL)return NULL;
            node<T>* cur = head;
            if(head==tail)tail=tail->next;
            head=head->next;
            T ans = cur->val;
            delete cur;
            size--;
            return ans;
        }
        void printQueue()
        {
            node<T>* cur = head;
            while(cur!=NULL)
            {
                cout << cur->val << " ";
                cur= cur->next;
            }
            cout << endl;
        }
};

/*int main()
{
    int t,v,j;
    Queue<int> q;

    cin >> t;
    while(t!=-1)
    {
        if(t==1)
        {
            cin >> v;
            q.enqueue(v);
        }
        else if(t==2)
        {
            v = q.dequeue();
            cout << v << " dequeued" << endl;
        }
        q.printQueue();
        cin >> t;
    }
}*/
