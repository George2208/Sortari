#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
// count, bubble, quick, merge, radix
using namespace std;
ifstream f("date");

void rng(vector<int> &v, unsigned int interval, unsigned int range)
{
    srand((unsigned)time(NULL));
    for(unsigned int i=0; i<interval; i++)
        v.push_back(rand()%range);
}

void afis(vector<int> v){
    for(unsigned int i=0; i<v.size(); i++)
        cout<<v[i]<<' ';
    cout<<endl<<endl;
}

bool check(vector<int> v)
{
    for(unsigned int i=1; i<v.size(); i++)
        if(v[i]<v[i-1])
            return false;
    return true;
}

void countsort(vector<int> &v){
    int ind=0, c=*max_element(v.begin(), v.end())+1, fr[c]={0};
    for(unsigned int i=0; i<v.size(); i++)
        fr[v[i]]++;
    for(int i=0; i<c; i++)
    {
        while(fr[i])
        {
            v[ind++]=i;
            fr[i]--;
        }
    }
}

void bubblesort(vector<int> &v){
    unsigned int i,j;
    for(i=0; i<v.size(); i++)
        for(j=0; j<v.size()-i; j++)
            if(v[j]>v[j+1])
            {
                int aux=v[j+1];
                v[j+1]=v[j];
                v[j]=aux;
            }
}

void quicksort(vector<int> &v, int a=-1, int b=-2){
    if(a<0 || b<-1)
    {
        a=0;
        b=v.size()-1;
    }
    if(a<b)
    {
        int p=v[b];
        int i=a-1;
        for(int j=a; j<=b; j++)
        {
            if(v[j]<p)
            {
                i++;
                int aux=v[i];
                v[i]=v[j];
                v[j]=aux;
            }
        }
        int aux=v[i+1];
        v[i+1]=v[b];
        v[b]=aux;
        quicksort(v, a, i);
        quicksort(v, i+2, b);
    }
}

void mergesort(vector<int> &v, int a=-1, int b=-1){
    if(a<0 || b<0)
    {
        a=0;
        b=v.size();
    }
    if(a<b)
    {
        int m=(a+b)/2;
        mergesort(v, a, m);
        mergesort(v, m+1, b);
        int p=a, p1=0, p2=0, v1[m-a+1], v2[b-m];
        for(int i=a; i<=m; i++)
            v1[i-a]=v[i];
        for(int i=m+1; i<=b; i++)
            v2[i-m-1]=v[i];
        while(p1<m-a+1 && p2<b-m)
        {
            if(v1[p1]<=v2[p2])
                v[p++]=v1[p1++];
            else
                v[p++]=v2[p2++];
        }
        while(p1<m-a+1)
            v[p++]=v1[p1++];
        while(p2<b-m)
            v[p++]=v2[p2++];
    }
}

vector<int> radixsort_aux(vector<int> v, int nr, unsigned int b){
    if(nr==-1)
        return v;
    vector<int> l[b], rez;
    for(unsigned int i=0; i<v.size(); i++)
        l[int(v[i]/ceil(pow(b, nr)))%b].push_back(v[i]);
    for(unsigned int i=0; i<b; i++)
        if(l[i].size())
        {
            vector<int>aux=radixsort_aux(l[i], nr-1, b);
            rez.insert(rez.end(), aux.begin(), aux.end());
            aux.clear();
        }
    return rez;
}

void radixsort(vector<int> &v, unsigned int b=10){
    if(!v.size())
        return;
    int nr=-1, aux=*max_element(v.begin(), v.end());
    while(aux)
    {
        aux/=b;
        nr++;
    }
    v=radixsort_aux(v, nr, b);
    return;
}

int main()
{
    ifstream f("date");
    vector<int> v, k;
    unsigned int t1, t2, nrel, vabs, i=1;
    while(f>>nrel>>vabs)
    {
        cout<<"\nTest "<< i++ <<"("<<nrel<<" elemente max(v[i])="<<vabs<<"):\n";
        rng(v, nrel, vabs);
        k=v;
        t1=chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
        countsort(v);
        t2=chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
        if(check(v))
            cout<<"Countsort: "<<t2-t1<<" milisecunde.\n";
        else
            cout<<"countsort skipped\n";
        v=k;
        t1=chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
        bubblesort(v);
        t2=chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
        if(check(v))
            cout<<"Bubblesort: "<<t2-t1<<" milisecunde.\n";
        else
            cout<<"Bubblesort skipped\n";
        v=k;
        t1=chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
        quicksort(v);
        t2=chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
        if(check(v))
            cout<<"Quicksort: "<<t2-t1<<" milisecunde.\n";
        else
            cout<<"Quick skipped\n";
        v=k;
        t1=chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
        mergesort(v);
        t2=chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
        if(check(v))
            cout<<"Mergesort: "<<t2-t1<<" milisecunde.\n";
        else
            cout<<"Mergesort skipped\n";
        v=k;
        t1=chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
        radixsort(v);
        t2=chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
        if(check(v))
            cout<<"Radixsort: "<<t2-t1<<" milisecunde.\n";
        else
            cout<<"Radixsort skipped\n";
        v=k;
        t1=chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
        sort(v.begin(), v.end());
        t2=chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
        if(check(v))
            cout<<"STDsort: "<<t2-t1<<" milisecunde.\n";
        else
            cout<<"STDsort skipped\n";
    }
    return 0;
}
