#include "ConversionFunction.h"

std::wstring emc::charTowstring(char* charstr)
{
	std::string str = charstr;
	std::wstring result;
	int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), NULL, 0);
	if (len < 0)return result;
	wchar_t* buffer = new wchar_t[len + 1];
	if (buffer == NULL)return result;
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), buffer, len);
	buffer[len] = '\0';
	result.append(buffer);
	delete[] buffer;
	return result;
}

std::wstring emc::stringTowstring(std::string str)
{
    std::wstring result;
    int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), NULL, 0);
    if (len < 0)return result;
    wchar_t* buffer = new wchar_t[len + 1];
    if (buffer == NULL)return result;
    MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), buffer, len);
    buffer[len] = '\0';
    result.append(buffer);
    delete[] buffer;
    return result;
}

std::string emc::wstringTostring(std::wstring wstr)
{
	std::string result;
	int len = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), NULL, 0, NULL, NULL);
	if (len <= 0)return result;
	char* buffer = new char[len + 1];
	if (buffer == NULL)return result;
	WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), buffer, len, NULL, NULL);
	buffer[len] = '\0';
	result.append(buffer);
	delete[] buffer;
	return result;
}

bool emc::wstringWithOnlyNumbersToint(std::wstring str, int& intstr)
{
	/*
	*	如果end指向字符串的末尾，说明整个字符串都被成功转换了，转换成功。
	*	wstr.c_str()返回一个指向字符串首字符的指针，加上wstr.size()就是指向字符串的末尾。
	*	如果end不等于这个指针，说明有未能成功转换的字符，转换失败。
	*/
	wchar_t* end = nullptr;
	intstr = std::wcstol(str.c_str(), &end, 10);
	if (end == str.c_str() + str.size()) 
	{
		return true;
	}
	return false;
}

std::string emc::DecimalToBinary(std::string n)
{
	std::string result = "";
	std::string temp = "temp";
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
	return result;
}

int emc::RomanToint(std::string s)

{
	std::unordered_map<char, int> umap =
	{
		{'I', 1},
		{'V', 5},
		{'X', 10},
		{'L', 50},
		{'C', 100},
		{'D', 500},
		{'M', 1000}
	};
	int result = umap[s.back()];
	for (int i = s.length() - 2; i >= 0; i--)
	{
		if (umap[s[i]] < umap[s[i + 1]])
		{
			result -= umap[s[i]];
		}
		else
		{
			result += umap[s[i]];
		}
	}
	return result;
}


