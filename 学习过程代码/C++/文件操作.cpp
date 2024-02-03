#pragma once
#include <iostream>
#include<fstream>//头文件包含
#include<string>
using namespace std;

class person
{
public:
	unsigned int age = 0;
	char name[64] = "";
};










void write() 
{
	//写文件
	ofstream ofs;//创建流对象
	ofs.open("test.txt", ios::out);//指定打开文件路径和打开方式
	ofs << "Hello world" << endl;//写入Hello world
	ofs.close();//关闭文件
}
//写二进制文件
void write_2()
{
	/*
	ofstream ofs;
	ofs.open("test2.txt", ios::out | ios::binary);
	*/
	//上述两个步骤可以合并为:
	ofstream ofs("test2.txt", ios::out | ios::binary);
	person 张三{ 20, "张三" };
	ofs.write((const char*)&张三, sizeof(张三));
	ofs.close();
}
//读二进制文件
void read_2()
{
	ifstream ifs("test2.txt", ios::in | ios::binary);
	if (!ifs.is_open())//判断文件是否打开成功
	{
		cout << "文件打开失败" << endl;
		return;
	}
	person p2;
	ifs.read((char*)&p2, sizeof(p2));
	ifs.close();
	cout << p2.name << "  " << p2.age << endl;
}
//读数据，四种方式
void read1()  
{
	ifstream ifs;//创建流对象
	ifs.open("test.txt", ios::in);//打开文件并
	if(!ifs.is_open())//判断文件是否打开成功
	{
		cout << "文件打开失败" << endl;
		return;
	}		
	//读数据
		//第一种，将文件中的内容全部放到字符数组中，注意：数组大小必须>=文件内容的字符数量，否则程序崩溃
	char buf[1024] = { 0 };
	while (ifs >> buf)
	{
		cout << buf ;
	}
	cout << endl;
	ifs.close();
}
void read2() 
{
	ifstream ifs;//创建流对象
	ifs.open("test.txt", ios::in);//打开文件并
	if (!ifs.is_open())//判断文件是否打开成功
	{
		cout << "文件打开失败" << endl;
		return;
	}
	//读数据
		//第二种，将文件中的内容一行一行的写入字符数组中，并根据数组大小，写入相应大小的内容
	char buf[1024] = { 0 };
	while (ifs.getline(buf, sizeof(buf)))//ifs下的getline()函数，参数一：数组首地址，参数二：数组大小
	{
		cout << buf << endl;
	}
	ifs.close();
}
void read3() 
{
	ifstream ifs;//创建流对象
	ifs.open("test.txt", ios::in);//打开文件并
	if (!ifs.is_open())//判断文件是否打开成功
	{
		cout << "文件打开失败" << endl;
		return;
	}
	//读数据
		//第三种，将文件中的内容写入string字符串中
	string buf;
	while (getline(ifs, buf)) //全局函数getline()，参数一：流，这里是文件读取流，参数二：字符串
	{
		cout << buf << endl;
	}
	ifs.close();
}
void read4() 
{
	ifstream ifs;//创建流对象
	ifs.open("test.txt", ios::in);//打开文件并
	if (!ifs.is_open())//判断文件是否打开成功
	{
		cout << "文件打开失败" << endl;
		return;
	}
	//读数据
		//第四种，将文件中的内容一个一个的读取并写入到char字符中，一个一个的输出，效率低
	char c;
	while ((c = ifs.get()) != EOF)//EOF		end of file	//ifs下的get()，函数，获取单个字符，并赋值给字符c，然后输出，并判断是否读取到文章尾部，到尾部则停止
	{
		cout << c;
	}
	ifs.close();
}

int main5()
{
	//write_2();
	//read1();
	//read2();
	//read3();
	//read4();
	//read_2();
	system("pause");
	return 0;
}

/*
操作文件的三大类：
1、ofstream：写操作
2、ifstream：读文件
3、fstream：读写文件

文件打开方式
ios::in			为读文件而打开文件
ios::out		为写文件而打开文件
ios::ate		初始位置：文件尾
ios::app		追加方式写文件
ios::trunc		如果文件存在先删除，在创建
ios::biary		二进制方式

注意：文件打开方式可以配合使用，利用 | 操作符
例如：用二进制方式写文件		ios::binary | ios::out
*/