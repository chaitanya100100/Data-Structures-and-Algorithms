#include<iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;

template <class T>
class MaxHeap
{
    private:
        T* key;
        int* pq;
        int* qp;
        int n;
    public:
        MaxHeap(int size)
        {
            key = new T[size+1];
            pq = new int[size+1];
            qp = new int[size+1];
            n = 0;
        }
        void swap(int a, int b)
        {
            int temp;
            temp = pq[a];
            pq[a] = pq[b];
            pq[b] = temp;
            qp[pq[a]]=a;
            qp[pq[b]]=b;
            //cout << pq[a] << " " << pq[b] << endl;
        }
        void swim(int k)
        {
            while(k>1 && key[pq[k]] > key[pq[k/2]])
            {
                swap(k/2,k);
                k=k/2;
            }
        }
        void sink(int k)
        {
            int j;
            while(2*k<=n)
            {
                j=2*k;
                if(j<n && key[pq[j+1]]>key[pq[j]])j++;
                if(key[pq[j]]<=key[pq[k]])break;
                swap(j,k);
                k=j;
            }
        }
        void add(T ele)
        {
            n++;
            key[n] = ele;
            pq[n] = n;
            qp[n] = n;
            swim(n);
        }
        T delMax()
        {
            swap(1,n);
            n--;
            sink(1);
            key[pq[n+1]]=key[n+1];
            pq[qp[n+1]]=pq[n+1];
            qp[pq[n+1]]=1;
            return key[n+1];
        }
        T delByKey(int i)
        {
            /*i = qp[i];
            swap(i,n);
            n--;

            sink(i);
            swim(i);
            return key[pq[n+1]];*/

            i = qp[i];
            swap(i,n);
            n--;
            sink(i);
            swim(i);
            key[pq[n+1]]=key[n+1];
            pq[qp[n+1]]=pq[n+1];
            qp[pq[n+1]]=i;
            return key[n+1];
        }
        void displayHeap()
        {
            for(int i=1; i<=n; i++)
                cout << key[pq[i]] << " ";
            cout << endl;
            /*for(int i=1; i<=n; i++)
                cout << key[i] << " ";
            cout << endl;*/
            /*for(int i=1; i<=n; i++)
                cout << qp[i] << " ";
            cout << endl;*/
        }
};

int main()
{
    MaxHeap<int> mh(100);
    int t,a;
    cin >> t;
    while(t!=-1)
    {
        if(t==1)
        {
            cin >> a;
            mh.add(a);
        }
        if(t==2)
        {
            mh.delMax();
        }
        if(t==3)
        {
            cin >> a;
            mh.delByKey(a);
        }
        mh.displayHeap();
        cin >> t;
    }
    return 0;
}
