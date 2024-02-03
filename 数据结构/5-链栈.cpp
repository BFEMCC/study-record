#include <iostream>
using namespace std;

//链栈
template <class T1>class Stack
{
private:
	struct Node
	{
		Node* next{ nullptr };
		T1 date;
	};

	Node* top{ nullptr };
	int length{ 0 };

public:
	Stack() = default;

	Stack(const Stack<T1>& other) = delete;//禁用拷贝构造（写起来太麻烦了

	//入栈
	void Push(const T1& e)
	{
		Node* p = new Node;//生成新节点

		if (p == nullptr)
			throw "分配内存失败";

		if (top == nullptr)//如果头节点是空，第一次入栈
			p->next = nullptr;//栈底，指针域赋空
		else
			p->next = top;//新节点指针域指向原先的栈顶

		p->date = e;//设置新节点数据域
		top = p;//头节点指向新节点
		length++;
	}

	//出栈
	void Pop()
	{
		if (top == nullptr)
			throw "栈为空";		
		if (top->next != nullptr)//不是栈底
		{
			Node* p = top;
			top = top->next;
			delete p;
		}
		else//栈底
		{
			delete top;
			top = nullptr;
		}
		
		length--;
	}
	
	//获取栈顶
	T1 GetTop()
	{
		if (top == nullptr)
			throw "栈为空";
		return top->date;
	}

	//获取元素个数
	int lgenth()
	{
		return length;
	}

	// 判断栈是否为空
	bool IsEmpty() const
	{
		return top == nullptr;
	}

	//析构
	~Stack()
	{
		while (top != nullptr)
		{
			Node* p = top;
			top = top->next;
			delete p;
		}
	}

};

int main()
{
	Stack<int>* stack = new Stack<int>;
	stack->Push(1);
	stack->Push(2);
	cout << stack->GetTop() << endl;
	stack->Pop();
	cout << stack->lgenth() << endl;
	cout << stack->GetTop() << endl;

    system("pause");
}

