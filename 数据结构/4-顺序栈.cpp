#include <iostream>
using namespace std;

//顺序栈
template <class T1>
class Stack
{
public:
	Stack(const int size)//初始化
	{
		StackSize = size;
		base = new T1[StackSize];
		top = base;
		if (base == nullptr)
		{
			throw "分配内存失败";
		}
	}
	Stack(const Stack& other)//初始化
	{
		StackSize = other.StackSize;
		base = new T1[StackSize];
		top = base;
		if (base == nullptr)
		{
			throw "分配内存失败";
		}
	}

	void Push(const T1& e)//入栈
	{
		if (top - base == StackSize)//满栈扩容
		{	
			T1* tempbase = new T1[2 * StackSize];
			T1* temptop = tempbase;
			if (tempbase == nullptr)
			{
				throw "拓展内存失败";
			}
			for (int i = StackSize; i > 0; i--)
			{
				*temptop = *(top - i);
				temptop++;
			}
			delete[]base;
			base = tempbase;
			top = temptop;
			StackSize *= 2;
		}
		*top = e;
		top++;
	}
	
	void Pop()//出栈
	{
		if (base == top)
		{
			throw "栈为空";
		}
		top--;
	}
	T1& Top()//获取栈顶元素
	{
		if (base == top)
		{
			throw "栈为空";
		}
		return *(top - 1);
	}

	int Length()//获取元素数量
	{
		return top - base;
	}

	int Size()//获取栈的最大容量
	{
		return StackSize;
	}

	~Stack()
	{
		if (base != nullptr)
		{
			base = nullptr;
			top = nullptr;
			delete[]base;
		}
	}
private:
	int StackSize;
	T1* base = nullptr;//栈底指针
	T1* top = nullptr;//栈顶指针
};


int main()
{
	Stack<int> stack(10);
	for (int i = 0; i < 100; i++)
	{
		stack.Push(i);
	}
	for (int i = 0; i < 100; i++)
	{
		cout<<stack.Top()<<",";
		stack.Pop();
	}
	cout << endl;

	cout << stack.Length() << endl;
	cout << stack.Size() << endl;

	system("pause");
	return 0;
}
