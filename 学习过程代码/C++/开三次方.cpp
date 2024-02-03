#include<iostream>
#include<iomanip>
using namespace std;
float kaigenghaodayu1(float a)//封装二分法开立方函数，只适用于被开立方数大于1，用一个简单的数学变换就可以适用小于1的数
{
	float low=0;
	float high=a;
	float median=high/2;
	if (a>1)
	{
		for(int i=0;i<70;i++)//二分70次以确保精度
		{
			if(median*median*median<a)
			{
				low=median;
				median=(low+high)/2;
			}
			else if(median*median*median>a)
			{
				high=median;
				median=(low+high)/2;
			}
			else break;
		}
	}
	return median;
}
int main()
{
  float arr[100000]={0};
  int a;
  cin>>a;//输入测试数量
  for(int i=0;i<a;i++)
  {//输入被开立方数
  	cin>>arr[i];
  }
//输出结果时要分为>1,0~1,-1~0,<-1,一个简单的数学问题
  for(int i=0;i<a;i++)
  {
   if(arr[i]>1)
   {//>1结果
	  	cout<<setprecision(3)<<kaigenghaodayu1(arr[i])<<endl;//四舍五入保留3位小数 
   }
   else if(arr[i]<=1 && arr[i]>=0)
   {//0~1结果
	  	cout<<setiosflags(ios::fixed)<<setprecision(3)<<kaigenghaodayu1(arr[i]*10)/kaigenghaodayu1(10)<<endl;//四舍五入保留3位小数 
   }
   else if(arr[i]<0 && arr[i]>=-1)
   {//-1~0结果
      cout<<setiosflags(ios::fixed)<<setprecision(3)<<-(kaigenghaodayu1((-arr[i])*10)/kaigenghaodayu1(10))<<endl;//四舍五入保留3位小数 
	 }
   else 
   {//<-1结果
   cout<<setiosflags(ios::fixed)<<setprecision(3)<<-(kaigenghaodayu1((-arr[i])))<<endl;//四舍五入保留3位小数 
   }
  }
  system("pause");
	return 0;
}
