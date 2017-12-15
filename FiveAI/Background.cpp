#include "Background.h"
#include <conio.h>
extern int game[15][15];
Background::Background()  //设置界面1024*768
{
	initgraph(2024, 800);
	setbkcolor(LIGHTGRAY);
	cleardevice();
}

Background::~Background()//关闭界面
{
	_getch();
	closegraph();
}

void Background::clean()				//清理棋盘状态
{
	setline();
	setnumber();
	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 15; j++)
			game[i][j] = 0;
}

