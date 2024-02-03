#include <easyx.h>
#include<iostream>
class text_box
{
private:
	int left = 0, top = 0, right = 0, bottom = 0;	// 坐标
	char* text = NULL;								// 字符内容
	size_t maxlen = 0;								// 字符串最大内容长度

public:
	//初始化参数
	void initialize(int x1, int y1, int x2, int y2, int max)
	{
		this->maxlen = max+1;
		this->text = new char[this->maxlen];
		this->text[0] = 0;
		this->left = x1, this->top = y1, this->right = x2, this->bottom = y2;
		this->show();// 绘制用户界面
	}
	//析构释放内存
	~text_box()
	{
		if (this->text != NULL)
		{
			delete[] this->text;
		}
	}
	//获取字符内容
	char* get_text()
	{
		return this->text;
	}
	//判断鼠标坐标位置
	bool mousXY(int x, int y)
	{
		return (this->left <= x && x <= this->right && this->top <= y && y <= this->bottom);
	}
	//绘制未点击时界面
	void show()
	{
		//设置未点击时绘制参数
		setlinecolor(RGB(0, 0, 0));
		setbkcolor(RGB(255, 255, 255));
		setfillcolor(RGB(255, 255, 255));

		fillrectangle(this->left, this->top, this->right, this->bottom);
		outtextxy(this->left + 10, this->top + 5, this->text);
	}
	//处理鼠标消息，绘制点击时界面
	void onmessage()
	{
		setlinecolor(RGB(0, 108, 190));			// 设置画线颜色
		setbkcolor(RGB(230, 231, 232));			// 设置背景颜色
		setfillcolor(RGB(230, 231, 232));		// 设置填充颜色

		fillrectangle(this->left, this->top, this->right, this->bottom);
		outtextxy(this->left + 10, this->top + 5, this->text);

		int width = textwidth(this->text);	// 字符串总宽度
		int counter = 0;				// 光标闪烁计数器
		bool binput = true;				// 是否输入中

		ExMessage msg;
		while (binput)
		{
			while (binput && peekmessage(&msg, EX_MOUSE | EX_CHAR, false))	// 获取消息，但不从消息队列拿出
			{
				//如果鼠标左键按下
				if (msg.message == WM_LBUTTONDOWN)
				{
					// 如果鼠标点击文本框外面，结束文本输入
					if (msg.x < this->left || msg.x > this->right || msg.y < this->top || msg.y > this->bottom)
					{
						binput = false;
						clearrectangle(this->left + 10 + width + 1, this->top + 3, this->left + 10 + width + 1, this->bottom - 3);	// 擦光标
						this->show();
						return;
					}
				}
				//如果按下字符按键
				else if (msg.message == WM_CHAR)
				{
					size_t len = strlen(this->text);
					switch (msg.ch)
					{
					case '\b':				// 用户按退格键，删掉一个字符
						if (len > 0)
						{
							this->text[len - 1] = 0;
							width = textwidth(this->text);
							counter = 0;
							clearrectangle(this->left + 10 + width, this->top + 1, this->right - 1, this->bottom - 1);
						}
						break;
					case '\r':				// 用户按回车键，结束文本输入
					case '\n':
						binput = false;
						clearrectangle(this->left + 10 + width + 1, this->top + 3, this->left + 10 + width + 1, this->bottom - 3);	// 擦光标
						this->show();
						return;
					default:				// 用户按其它键，接受文本输入
						if (len < this->maxlen - 1)
						{
							text[len++] = msg.ch;
							text[len] = 0;

							clearrectangle(this->left + 10 + width + 1, this->top + 3, this->left + 10 + width + 1, this->bottom - 3);	// 清除画的光标
							width = textwidth(this->text);				// 重新计算文本像素宽度
							outtextxy(this->left + 10, this->top + 5, this->text);		// 输出新的字符串
						}
					}
				}
				peekmessage(NULL, EX_MOUSE | EX_CHAR);				// 从消息队列抛弃刚刚处理过的一个消息
			}
			// 绘制光标（光标闪烁周期为 20ms * 32）
			counter = (counter + 1) % 32;
			if (counter < 16)
			{
				setlinecolor(RGB(0, 0, 0));
				line(this->left + 10 + width + 1, this->top + 3, this->left + 10 + width + 1, this->bottom - 3);				// 画光标
			}
			else
			{
				clearrectangle(this->left + 10 + width + 1, this->top + 3, this->left + 10 + width + 1, this->bottom - 3);		// 擦光标
			}
			Sleep(20);// 延时 20ms
		}
		clearrectangle(this->left + 10 + width + 1, this->top + 3, this->left + 10 + width + 1, this->bottom - 3);	// 擦光标
		this->show();
	}
};

class EasyButton
{
private:
	int left = 0, top = 0, right = 0, bottom = 0;	// 控件坐标
	char* text = NULL;							// 控件内容
	void (*userfunc)() = NULL;						// 控件消息

public:
	void Create(int x1, int y1, int x2, int y2, const char* title, void (*func)())
	{
		text = new char[strlen(title) + 1];
		strcpy_s(text, strlen(title) + 1, title);
		left = x1, top = y1, right = x2, bottom = y2;
		userfunc = func;

		// 绘制用户界面
		Show();
	}

	~EasyButton()
	{
		if (text != NULL)
			delete[] text;
	}

	bool Check(int x, int y)
	{
		return (left <= x && x <= right && top <= y && y <= bottom);
	}

	// 绘制界面
	void Show()
	{
		int oldlinecolor = getlinecolor();
		int oldbkcolor = getbkcolor();
		int oldfillcolor = getfillcolor();

		setlinecolor(BLACK);			// 设置画线颜色
		setbkcolor(WHITE);				// 设置背景颜色
		setfillcolor(WHITE);			// 设置填充颜色
		fillrectangle(left, top, right, bottom);
		outtextxy(left + (right - left - textwidth(text) + 1) / 2, top + (bottom - top - textheight(text) + 1) / 2, text);

		setlinecolor(oldlinecolor);
		setbkcolor(oldbkcolor);
		setfillcolor(oldfillcolor);
	}

	void OnMessage()
	{
		if (userfunc != NULL)
			userfunc();
	}
};

text_box test1;
text_box test2;
text_box test3;
EasyButton ok;


void ok_Click()
{
	if (strcmp("123", test2.get_text()))
		MessageBox(GetHWnd(), "密码错误", "错误", MB_OK);
	else
	{
		char s[100] = "Hello, ";
		strcat_s(s, 100, test1.get_text());
		MessageBox(GetHWnd(), s, "Hello", MB_OK);
	}
}




int main()
{
	// 创建图形窗口
	initgraph(640, 480, 0);
	setbkcolor(RGB(225, 238, 238));
	cleardevice();

	settextcolor(BLACK);
	outtextxy(50, 55, "随意");
	outtextxy(50, 105, "密码123");


	//初始化2个示例文本框
	test1.initialize(120, 50, 400, 75, 10);
	test2.initialize(120, 100, 400, 125, 10);
	//初始化ok按钮
	ok.Create(320, 200, 400, 225, "OK", ok_Click);

	ExMessage msg;
	while (true)
	{
		msg = getmessage(EX_MOUSE);	// 获取鼠标消息
		if (msg.message == WM_LBUTTONDOWN)
		{
			// 判断1
			if (test1.mousXY(msg.x, msg.y))
			{
				test1.onmessage();
			}
			// 判断2
			if (test2.mousXY(msg.x, msg.y))
			{
				test2.onmessage();
			}
			//判断ok按钮
			if (ok.Check(msg.x, msg.y))
			{
				ok.OnMessage();
			}
		}
	}
	// 关闭绘图窗口
	closegraph();
	return 0;
}