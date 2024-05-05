#include<graphics.h>

char b_d[3][3] =
{
	{'-','-','-'},
	{'-','-','-'},
	{'-','-','-'},
};

char c_p = 'O';

bool checkwin(char c)
{
	if (b_d[0][0] == c && b_d[0][1] == c && b_d[0][2] == c)
		return true;
	if (b_d[1][0] == c && b_d[1][1] == c && b_d[1][2] == c)
		return true;
	if (b_d[2][0] == c && b_d[2][1] == c && b_d[2][2] == c)
		return true;
	if (b_d[0][0] == c && b_d[1][1] == c && b_d[2][2] == c)
		return true;
	if (b_d[0][0] == c && b_d[1][0] == c && b_d[2][0] == c)
		return true;
	if (b_d[0][1] == c && b_d[1][1] == c && b_d[2][1] == c)
		return true;
	if (b_d[0][2] == c && b_d[1][2] == c && b_d[2][2] == c)
		return true;
	if (b_d[2][0] == c && b_d[1][1] == c && b_d[0][2] == c)
		return true;
	return false;
}
bool checkdraw()
{
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			if (b_d[i][j] == '-')
			{
				return false;
			}
		}
	}
	return true;
}
void drawboard()
{
	line(0, 200, 600, 200);
	line(0, 400, 600, 400);
	line(200, 0, 200, 600);
	line(400, 0, 400, 600);
}
void drawpiece()
{
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			switch (b_d[i][j])
			{
			case 'O':
				circle(200 * j + 100, 200 * i + 100,100);
					break;
			case 'X':
				line(200 * j, 200 * i, 200 * (1 + j), 200 * (1 + i));
				line(200 * (j + 1), 200 * i, 200 * j, 200 * (1 + i));
				break;
			case '-':
				break;
			default:
				break;
			}
		}
	}
}
void drawtext()
{
	static TCHAR str[64];
	_stprintf_s(str, _T("当前棋子类型：%c"),c_p);

	settextcolor(RGB(225, 175, 45));
	outtextxy(0, 0, str);
}
int main()
{
	initgraph(600, 600);

	bool running=true;
	ExMessage msg;
	BeginBatchDraw();
	while(running)
	{
		DWORD start_time = GetTickCount();
		while (peekmessage(&msg))
		{
			if (msg.message == WM_LBUTTONDOWN)
			{
				int x = msg.x;
				int y = msg.y;

				int index_x = x / 200;
				int index_y = y / 200;

				if (b_d[index_y][index_x] == '-')
				{
					b_d[index_y][index_x] = c_p;

					if (c_p == 'O')
					{
						c_p = 'X';
					}
					else
					{
						c_p = 'O';
					}
				}
			}
		}
		cleardevice();

		drawboard();
		drawpiece();
		drawtext();

		FlushBatchDraw();
		if (checkwin('X'))
		{
			MessageBox(GetHWnd(),_T("x 玩家获胜"),_T("游戏结束"),MB_OK);
			running = false;
		}
		else if (checkwin('O'))
		{
			MessageBox(GetHWnd(), _T("o 玩家获胜"), _T("游戏结束"), MB_OK);
			running = false;
		}
		else if (checkdraw())
		{
			MessageBox(GetHWnd(), _T("平局!"), _T("游戏结束"), MB_OK);
			running = false;
		}
		DWORD end_time = GetTickCount();
		DWORD delta_time = end_time - start_time;

		if (delta_time < 1000 / 60)
		{
			Sleep(1000 / 60 - delta_time);
		}
	}
	EndBatchDraw();

	return 0;
}