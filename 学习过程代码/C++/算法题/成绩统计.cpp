/*
https://www.lanqiao.cn/problems/502/learning/
题目描述
小蓝给学生们组织了一场考试，卷面总分为 100 分，每个学生的得分都是一个 0 到 100 的整数。
如果得分至少是 60 分，则称为及格。如果得分至少为 85 分，则称为优秀。
请计算及格率和优秀率，用百分数表示，百分号前的部分四舍五入保留整 数。

输入描述
输入的第一行包含一个整数 n (1 ≤ n ≥ 10^4)，表示考试人数。

接下来 n 行，每行包含一个 0 至 100 的整数，表示一个学生的得分。

输出描述
输出两行，每行一个百分数，分别表示及格率和优秀率。百分号前的部分 四舍五入保留整数。

输入输出样例
示例
输入

7
80
92
56
74
88
100
0

输出

71%
43%

运行限制
最大运行时间：1s
最大运行内存: 256M
*/

//以下为c++代码
//内存：1608kb
//程序远行耗时：4ms


#include <iostream>
#include<iomanip>
using namespace std;
int main()
{
  float a,b,c=0,d=0;
  cin>>a;
  for(int i=0;i<a;i++)
  {
    cin>>b;
    if (b>=60 && b<85)
    {
      c=c+1;
    }
    else if(b>=85)
    {
      d=d+1;
    }
  }
  cout<<setiosflags(ios::fixed)<<setprecision(0)<<((c+d)*100)/a<<"%"<<endl;
  cout<<setiosflags(ios::fixed)<<setprecision(0)<<((d/a)*100)<<"%"<<endl;
  return 0;
}