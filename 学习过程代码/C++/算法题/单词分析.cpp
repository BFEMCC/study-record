/*
https://www.lanqiao.cn/problems/504/learning/
题目描述
小蓝正在学习一门神奇的语言，这门语言中的单词都是由小写英文字母组 成，有些单词很长，远远超过正常英文单词的长度。小蓝学了很长时间也记不住一些单词，他准备不再完全记忆这些单词，而是根据单词中哪个字母出现得最多来分辨单词。
现在，请你帮助小蓝，给了一个单词后，帮助他找到出现最多的字母和这 个字母出现的次数。

输入描述
输入一行包含一个单词，单词只由小写英文字母组成。
对于所有的评测用例，输入的单词长度不超过 1000。

输出描述
输出两行，第一行包含一个英文字母，表示单词中出现得最多的字母是哪 个。如果有多个字母出现的次数相等，输出字典序最小的那个。
第二行包含一个整数，表示出现得最多的那个字母在单词中出现的次数。

输入输出样例
示例 1

输入
lanqiao

输出
a
2

示例 2

输入
longlonglongistoolong

输出
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
