#include<iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;

template<class T>
class Queue
{
    private:
        T* arr;
        int r;
        int f;
        int N;
    public:
        Queue(int s=3)
        {
            N = s;
            arr = new T[N];
            r=f=0;
        }
        int getSize()
        {
            return (N + r - f)%N;
        }
        bool isEmpty()
        {
            return r==f;
        }
        bool isFull()
        {
            return ((r+1)%N==f);
        }
        void resize(int n)
        {
            T* temp = new T[n];
            int s=getSize();
            for(int i=f,j=0; j<s; i=(i+1)%N,j++)
                temp[j] = arr[i];
            f=0;
            r=s;
            N = n;
            T* temp2 = arr;
            arr = temp;
            free(temp2);
        }
        void enqueue(T q)
        {
            if(isFull())
                resize(2*N);
            arr[r] = q;
            r = (r+1)%N;
        }
        T dequeue()
        {
            if(isEmpty())
                return -1;
            if(getSize()<N/4)
                resize(N/2);
            T ret=arr[f];
            f=(f+1)%N;
            return ret;
        }
        void printQueue()
        {
            //cout << N << " : " << f << " " << r << endl;
            for(int j=getSize(),i=f; j>0; i=(i+1)%N,j--)
                cout << arr[i] << " ";
            cout << endl;
        }
};

int main()
{
    int t,n,i,j;
    Queue<int> q;

    cin >> t;
    while(t!=-1)
    {
        if(t==1)
        {
            cin >> j;
            q.enqueue(j);
        }
        else
        {
            j = q.dequeue();
            //cout << j << " dequeued." << endl;
        }
        q.printQueue();
        cin >> t;
    }
    return 0;
}
