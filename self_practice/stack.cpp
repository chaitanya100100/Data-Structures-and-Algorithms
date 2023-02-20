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
class Stack
{
    private:
        node<T>* head;
        int size;
    public:
        Stack()
        {
            head=NULL;
            size=0;
        }
        bool isEmpty()
        {
            return (size==0);
        }
        void push(T val)
        {
            node<T>* pnew = new node<T>;
            pnew->val = val;
            pnew->next = head;
            head = pnew;
            size++;
            return;
        }
        T pop()
        {
            if(size==0 || head==NULL)return NULL;

            node<T>* cur=head;
            head = head->next;
            T ans=cur->val;
            size--;
            delete cur;
            return ans;
        }
        void printStack()
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
    Stack<int> s;

    cin >> t;
    while(t!=-1)
    {
        if(t==1)
        {
            cin >> v;
            s.push(v);
        }
        else if(t==2)
        {
            v = s.pop();
            cout << v << " poped" << endl;
        }
        s.printStack();
        cin >> t;
    }
}*/
