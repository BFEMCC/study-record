/*
题目描述
小蓝给学生们组织了一场考试，卷面总分为 100 分，每个学生的得分都是一个 0 到 100 的整数。
请计算这次考试的最高分、最低分和平均分。

输入描述
输入的第一行包含一个整数 n(1 ≤ n ≤ 10^4)，表示考试人数。
接下来 n 行，每行包含一个 0 至 100 的整数，表示一个学生的得分。

输出描述
输出三行。
第一行包含一个整数，表示最高分。
第二行包含一个整数，表示最低分。
第三行包含一个实数，四舍五入保留正好两位小数，表示平均分。

输入输出样例
示例
输入

7
80
92
56
74
88
99
10

输出

99
10
71.29

运行限制
最大运行时间：1s
最大运行内存: 256M
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