#include "Background.h"
#include <conio.h>
extern int game[15][15];
Background::Background()  //���ý���1024*768
{
	initgraph(2024, 800);
	setbkcolor(LIGHTGRAY);
	cleardevice();
}

Background::~Background()//�رս���
{
	_getch();
	closegraph();
}

void Background::clean()				//��������״̬
{
	setline();
	setnumber();
	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 15; j++)
			game[i][j] = 0;
}

