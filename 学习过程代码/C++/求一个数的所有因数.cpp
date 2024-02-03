#include <iostream>
#include <cstdio>
using namespace std;
int main()
{
    int x;
    cout<<"输入一个正整数:"<<endl;
    cin >>x ;
    cout<<"x的因数为"<<endl;
    for (int i=1;i<=x;i++)
    {
        if(x%i==0)
        cout<<i<<'\t';
    }
    cin.get();
    
    return 0;
}
