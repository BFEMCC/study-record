/*
��Ŀ����
С����ѧ������֯��һ�����ԣ������ܷ�Ϊ 100 �֣�ÿ��ѧ���ĵ÷ֶ���һ�� 0 �� 100 ��������
�������ο��Ե���߷֡���ͷֺ�ƽ���֡�

��������
����ĵ�һ�а���һ������ n(1 �� n �� 10^4)����ʾ����������
������ n �У�ÿ�а���һ�� 0 �� 100 ����������ʾһ��ѧ���ĵ÷֡�

�������
������С�
��һ�а���һ����������ʾ��߷֡�
�ڶ��а���һ����������ʾ��ͷ֡�
�����а���һ��ʵ�����������뱣��������λС������ʾƽ���֡�

�����������
ʾ��
����

7
80
92
56
74
88
99
10

���

99
10
71.29

��������
�������ʱ�䣺1s
��������ڴ�: 256M
https://www.lanqiao.cn/problems/497/learning/
*/








#include <iostream>
#include<iomanip>
#include <algorithm>
#include <numeric>
using namespace std;

int main()
{
  int arr[10000]={0};
  int a=0;
  cin>>a;
  for(int i=0;i<a;i++)
  {
    cin>>arr[i];
  }
  float he=accumulate(arr,arr+10000,0);
  int m_ax=*max_element(arr,arr+(sizeof(arr)/sizeof(int)));
  int m_in=*min_element(arr,arr+(sizeof(arr)/sizeof(int)));
  for(int i=0;i<sizeof(arr)/sizeof(int);i++)
  {
	  if(arr[i]==m_in)
	  {
		  arr[i]=m_ax;
	  }
  }
  int m_in2=*min_element(arr,arr+(sizeof(arr)/sizeof(int)));
  cout<<m_ax<<endl<<m_in2<<endl;
  cout<<setiosflags(ios::fixed)<<setprecision(2)<<he/a<<endl;
  system("pause");
  return 0;
}