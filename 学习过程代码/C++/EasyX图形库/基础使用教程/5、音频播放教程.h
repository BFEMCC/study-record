#pragma once
/*-----------用于音乐播放----------*/

#include<Windows.h>//还需要包含<windows.h>头文件，但EasyX库的头文件已经包含，可以不用添加

/*这两个需要在，<Windows.h>或EasyX头文件后面*/
#include<mmsystem.h>//多媒体设备接口头文件
#pragma comment(lib,"winmm.lib")//加载静态库

void PlayMusic()
{
	mciSendString("open ./音乐文件/洛天依_乐正绫_霜雪千年.mp3 alias 霜雪千年", 0, 0, 0);
	mciSendString("play 霜雪千年 repeat", 0, 0, 0);
	if (GetAsyncKeyState(VK_SPACE))
	{
		mciSendString("close 霜雪千年", 0, 0, 0);
	}


}

/*
* 第一步：打开音乐，加载音乐
mciSendString("open ./你想要播放的音乐的路径(相对或绝对) alias 自定义名称,0,0,0")		

//后三个一般0，0，0即可，alias：取别名，将你想要播放的音乐取一个别名，可以是中文，以后调用可以使用别名，否则每次调用都要使用完整的相对或绝对路径

*第二步：播放音乐
mciSendString("play ./你想要播放的音乐的路径(相对或绝对",0,0,0)			//后三个一般0，0，0即可

或者，使用alias后的自定义名称

mciSendString("play 自定义名称0,0,0")

在路径或自定义名称后面加上 repeat 可以循环播放
即：		mciSendString("play 自定义名称 repeat,0,0,0")


*关闭音乐
mciSendString("close 自定义名称或路径",0,0,0)


*/