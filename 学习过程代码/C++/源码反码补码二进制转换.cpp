#include <iostream>
#include<string>
#include <sstream>
#include <cctype> 
using namespace std;
//bool isNumber(const string& s) {
//	if (s.empty()) 
//	{
//		return false;
//	}
//	for (char c : s) 
//	{
//		if (!isdigit(c)) 
//		{
//			return false;
//		}
//	}
//	return true;
//}
//bool isNumber(const string& s)//判断整数和浮点数，但整数有位数限制
//{
//	if (s.empty())
//	{
//		return false;
//	}
//	size_t pos = s.find_first_not_of("0123456789.-"); // 找到第一个不是数字或'.'或'-'的字符位置
//	if (pos != string::npos) // 如果存在这样的字符，则说明不是数字
//	{
//		return false;
//	}
//	float num;
//	try
//	{
//		num = stof(s); // 将输入的字符串转换为float类型
//	}
//	catch (const invalid_argument&) {
//		return false; // 转换失败，说明不是小数
//	}
//	catch (const out_of_range&) {
//		return false; // 转换失败，说明不是小数
//	}
//	return true;
//}

//判断是否整数
bool isAllDigits(string str)//判断整数,无位数限制
{
	if (str[0]=='-' && str.length() > 1)//负数
	{
		for (char c : str.substr(1))
		{
			if (!isdigit(c) )
			{
				return false;  // 非数字，返回false
			}
		}
	}
	else if(str[0] == '+' && str.length() > 1)//正数
	{
		for (char c : str.substr(1))
		{
			if (!isdigit(c) )
			{
				return false;  // 非数字，返回false
			}
		}
	}
	else//没有正负号的其他情况
	{
		for (char c : str)
		{
			if (!isdigit(c))
			{
				return false;  // 非数字，返回false
			}
		}
	}
	return true;  // 所有字符都是数字，返回true
}

//判断是否是小数
bool isIoint(string str)
{
	int PointNum = 0;
	if (str[0]=='.'||(str[0]=='+'&&str[1]=='.')||(str[0] == '-' && str[1] == '.')||((str.length()==1)&&str[0]=='+')|| ((str.length() == 1) && str[0] == '-'))
	{
		//cout << "第一个就是小数点，或者只有单独一个正负号，或者正负号后面就是小数点" << endl;
		return false;
	}
	else if ((str.length() > 1) && ((str[0] == '+')||(str[0]=='-')))
	{
		for (char c : str.substr(1))
		{
			if (!isdigit(c))
			{
				if ((c != '.'))
				{
					//cout << "存在非数字并且不是小数点" << endl;
					return false;
				}
				if (c=='.')
				{
					PointNum++;
				}
			}
			if (PointNum > 1)
			{
				//cout << "存在多个小数点" << endl;
				return false;
			}
		}
	}
	else
	{
		for (char c : str)
		{
			if (!isdigit(c))
			{
				if ((c != '.'))
				{
					//cout << "存在非数字并且不是小数点" << endl;
					return false;
				}
				if (c == '.')
				{
					PointNum++;
				}
			}
			if (PointNum > 1)
			{
				//cout << "存在多个小数点" << endl;
				return false;
			}
		}
		
	}
	return true;
}

//将整数转成二进制源码，返回无符号位源码
string INTtoBinary(string n)
{
	string n1 = n;
	string result = "";
	string temp = "temp";
	while (temp.length() > 0)
	{
		temp = "";
		int i = 0;
		char ch;
		while (i < n.length())
		{
			ch = n[i] - '0';
			if (ch >= 2)
			{
				temp += static_cast<char>(ch / 2 + '0');
			}
			else if (ch == 0 || ch == 1)
			{
				if (temp.length() > 0)
					temp += '0';
			}

			if (ch % 2 == 1 && i < n.length() - 1)
			{
				n[i + 1] += 10;
			}

			i++;
		}
		result = static_cast<char>(ch % 2 + '0') + result;
		n = temp;
	}
	if (n1[0] == '-')
	{
		return ("-"+ result);
	}
	return ("+" + result);
}

//为无符号位源码添加符号位，返回1符号位源码
string SignBit(string n)
{
	string n1 = INTtoBinary(n);
	if (n1[0]=='+')
	{
		n1[0] = '0';
	}
	else if (n1[0] == '-')
	{
		n1[0] = '1';
	}
	return n1;
}

//将源码转为反码，返回1位符号位反码
string InverseCode(string n)
{
	string n1 = SignBit(n);
	if (n1[0] == '1')//负数
	{
		for (int i=1;i<n1.length();i++)
		{
			if (n1[i] == '0')
			{
				n1[i] = '1';
			}
			else if (n1[i] == '1')
			{
				n1[i] = '0';
			}
		}
		return n1;
	}
	return n1;
}

//将反码转为补码，返回1位符号位补码
string Complement(string n)
{
	if (n=="-0"||n=="+0")
	{
		return "0\n                    提示：-0、+0一般无意义，反码、补码一般统一为0";
	}
	string n1 = InverseCode(n);
	if (n1[0] == '1')//负数
	{
		if (n1[n1.length()-1] == '0') //末尾位0
		{
			n1[n1.length() - 1] = '1';
			return n1;
		}
		else if (n1[n1.length() - 1] == '1') //末尾为1
		{
			n1[n1.length() - 1] = '2';
			for (int i = n1.length() - 1; i > -1; i--) //开始进位
			{
				if (n1[i]=='2')
				{
					n1[i] = '0';
					n1[i - 1] = n1[i - 1] + 1;
				}
			}
		}
	}
	return n1;
}


void menu()
{
	string a;
	while (1)
	{
		cout << "请输入十进制数：";
		cin >> a;
		if (isAllDigits(a))
		{
			cout << endl << "最小位数：";
			cout << endl << "二进制 源码 无符号位： " << INTtoBinary(a) << endl;
			cout << "二进制 源码 1位符号位：" << SignBit(a) << endl;
			cout << "二进制 反码 1位符号位：" << InverseCode(a) << endl;
			cout << "二进制 补码 1位符号位：" << Complement(a) << endl << endl;
		}
		else if (isIoint(a))
		{
			cout << endl << "暂时不支持小数" << endl;
		}
		else
		{
			cout << endl << "非法输入，请重新输入" << endl;
		}
		system("pause");
		system("cls");
	}
}

int main()
{
	menu();
	return 0;
}

