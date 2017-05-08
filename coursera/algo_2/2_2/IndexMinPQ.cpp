#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
using namespace std;

template<class T>
class IndexMinPQ
{
    private:
        T* keys;
        int* pq;
        int* qp;
        int n;
    public:
        IndexMinPQ(int m)
        {
            keys = new T[m];
            for(int i=0; i<m; i++)
                keys[i]=-1;
            pq = new int[m+1];
            qp = new int[m];
            n=0;
        }
        void swap(int a, int b)
        {
            int tt=pq[a];pq[a]=pq[b];pq[b]=tt;
            qp[pq[a]]=a;
            qp[pq[b]]=b;
        }
        void swim(int k)
        {
            while(k>1)
            {
                if(keys[pq[k]] < keys[pq[k/2]])
                    swap(k,k/2);
                k = k/2;
            }
        }
        void sink(int k)
        {
            int j;
            while(2*k<=n)
            {
                j = 2*k;
                if(j<n && keys[pq[j]]>keys[pq[j+1]])j++;
                if(keys[pq[k]]<=keys[pq[j]])break;
                swap(k,j);
                k=j;
            }
        }
        void insert(int i, T k)
        {
            keys[i]=k;
            pq[++n] = i;
            qp[i] = n;
            swim(n);
        }
        void change(int i, T k)
        {
            keys[i]=k;
            swim(qp[i]);
        }
        int delMin()
        {
            swap(1,n);
            n--;
            sink(1);
            return pq[n+1];
        }
        bool isEmpty()
        {
            return n==0;
        }
        int size()
        {
            return n;
        }
        bool contains(int i)
        {
            return (keys[i]!=-1);
        }
        T keyAt(int i)
        {
            return keys[i];
        }
        void displayIndexMinPQ()
        {
            for(int i=1; i<=n; i++)
            {
                cout << keys[pq[i]] << " of " << pq[i] << endl;
            }
            cout << endl;
        }
};

/*int main()
{
    int i,j,k,t,v,w;
    double d;

    IndexMinPQ<double> pq(100);

    cin >> t;
    while(t!=-1)
    {
        if(t==1)
        {
            cin >> i >> d;
            pq.insert(i, d);
        }
        else if(t==2)
        {
            cin >> i >> d;
            pq.change(i, d);
        }
        else if(t==3)
        {
            int i = pq.delMin();
            cout << i << " " << pq.keyAt(i) << "deleted\n";
        }
        pq.displayIndexMinPQ();
        cin >> t;
    }
}*/
