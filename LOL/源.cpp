#include<iostream>
#include<graphics.h>

int main()
{
	int x = 300, y = 300;

	initgraph(1280, 720);

	BeginBatchDraw();

	while (true)
	{
		ExMessage msg;
		while (peekmessage(&msg))
		{
			if (msg.message = WM_MOUSEMOVE)
			{
				x = msg.x;
				y = msg.y;
			}
		}
		cleardevice();
		solidcircle(x, y, 100);
		FlushBatchDraw();
	}
	EndBatchDraw();
	return 0;
}