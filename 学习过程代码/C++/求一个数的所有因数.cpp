#include <iostream>
#include <cstdio>
using namespace std;
int main()
{
    int x;
    cout<<"����һ��������:"<<endl;
    cin >>x ;
    cout<<"x������Ϊ"<<endl;
    for (int i=1;i<=x;i++)
    {
        if(x%i==0)
        cout<<i<<'\t';
    }
    cin.get();
    
    return 0;
}
