/*
https://www.lanqiao.cn/problems/504/learning/
��Ŀ����
С������ѧϰһ����������ԣ����������еĵ��ʶ�����СдӢ����ĸ�� �ɣ���Щ���ʺܳ���ԶԶ��������Ӣ�ĵ��ʵĳ��ȡ�С��ѧ�˺ܳ�ʱ��Ҳ�ǲ�סһЩ���ʣ���׼��������ȫ������Щ���ʣ����Ǹ��ݵ������ĸ���ĸ���ֵ�������ֱ浥�ʡ�
���ڣ��������С��������һ�����ʺ󣬰������ҵ�����������ĸ���� ����ĸ���ֵĴ�����

��������
����һ�а���һ�����ʣ�����ֻ��СдӢ����ĸ��ɡ�
�������е���������������ĵ��ʳ��Ȳ����� 1000��

�������
������У���һ�а���һ��Ӣ����ĸ����ʾ�����г��ֵ�������ĸ���� ��������ж����ĸ���ֵĴ�����ȣ�����ֵ�����С���Ǹ���
�ڶ��а���һ����������ʾ���ֵ������Ǹ���ĸ�ڵ����г��ֵĴ�����

�����������
ʾ�� 1

����
lanqiao

���
a
2

ʾ�� 2

����
longlonglongistoolong

���
o
6

*/

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
int main()
{
	string shuru;
	cin>>shuru;
	int num[26]={0};
	for (int i = 0; i < shuru.length(); i++)
    {
        switch (shuru[i])
        {
        case 'a': num[0]++; break;
        case 'b': num[1]++; break;
        case 'c': num[2]++; break;
        case 'd': num[3]++; break;
        case 'e': num[4]++; break;
        case 'f': num[5]++; break;
        case 'g': num[6]++; break;
        case 'h': num[7]++; break;
        case 'i': num[8]++; break;
        case 'j': num[9]++; break;
        case 'k': num[10]++; break;
        case 'l': num[11]++; break;
        case 'm': num[12]++; break;
        case 'n': num[13]++; break;
        case 'o': num[14]++; break;
        case 'p': num[15]++; break;
        case 'q': num[16]++; break;
        case 'r': num[17]++; break;
        case 's': num[18]++; break;
        case 't': num[19]++; break;
        case 'u': num[20]++; break;
        case 'v': num[21]++; break;
        case 'w': num[22]++; break;
        case 'x': num[23]++; break;
        case 'y': num[24]++; break;
        case 'z': num[25]++; break;         
        }
    }
	int M=*max_element(num,num+26);
	if(num[0]==M)
	{
		cout<<"a"<<endl;
	}
	else if(num[1]==M)
	{
		cout<<"b"<<endl;
	}
	else if(num[2]==M)
	{
		cout<<"c"<<endl;
	}
	else if(num[3]==M)
	{
		cout<<"d"<<endl;
	}
	else if(num[4]==M)
	{
		cout<<"e"<<endl;
	}
	else if(num[5]==M)
	{
		cout<<"f"<<endl;
	}
	else if(num[6]==M)
	{
		cout<<"g"<<endl;
	}
	else if(num[7]==M)
	{
		cout<<"h"<<endl;
	}
	else if(num[8]==M)
	{
		cout<<"i"<<endl;
	}
	else if(num[9]==M)
	{
		cout<<"j"<<endl;
	}
	else if(num[10]==M)
	{
		cout<<"k"<<endl;
	}
	else if(num[11]==M)
	{
		cout<<"l"<<endl;
	}
	else if(num[12]==M)
	{
		cout<<"m"<<endl;
	}
	else if(num[13]==M)
	{
		cout<<"n"<<endl;
	}
	else if(num[14]==M)
	{
		cout<<"o"<<endl;
	}
	else if(num[15]==M)
	{
		cout<<"p"<<endl;
	}
	else if(num[16]==M)
	{
		cout<<"q"<<endl;
	}
	else if(num[17]==M)
	{
		cout<<"r"<<endl;
	}
	else if(num[18]==M)
	{
		cout<<"s"<<endl;
	}
	else if(num[19]==M)
	{
		cout<<"t"<<endl;
	}
	else if(num[20]==M)
	{
		cout<<"u"<<endl;
	}
	else if(num[21]==M)
	{
		cout<<"v"<<endl;
	}
	else if(num[22]==M)
	{
		cout<<"w"<<endl;
	}
	else if(num[23]==M)
	{
		cout<<"x"<<endl;
	}
	else if(num[24]==M)
	{
		cout<<"y"<<endl;
	}
	else if(num[25]==M)
	{
		cout<<"z"<<endl;
	}
	cout<<M<<endl;
        return 0;
}
