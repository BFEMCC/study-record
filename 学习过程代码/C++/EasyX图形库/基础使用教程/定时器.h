#pragma once

#include <time.h>
//定时器 控制自动移动的东西
bool Timer(int duration, int id)
{
	static int startTime[10];
	int endTime = clock();
	if (endTime - startTime[id] > duration)
	{
		startTime[id] = endTime;
		return 1;
	}
	return 0;
}