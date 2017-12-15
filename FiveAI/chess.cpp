#include "chess.h"
extern int game[15][15];
extern int win;
extern int leavesNumber;
chess::chess(int _x, int _y)
{
	x = _x;
	y = _y;
}

chess::~chess()
{
}

void chess::drawcircle()			//画出棋盘和棋子并检查是否胜利
{
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 30;
	settextstyle(&f);

	area headleft("headleft");
	area headright("headright");
	area righthead("righthead");
	static Vecposition vecstep[255];
	static int step = 0;          //初始化步数
	step++;
	/*if (step == 1)
	{
		game[7][7] = 1;
		vecstep[step] = Vecposition(7 * 50 + 30, 7 * 50 + 70);
	}
	else*/
	{
		if (x == -150 || x == -250)
		{
			step = 0;
			setline();
			setnumber();

			for (int i = 0; i < 15; i++)
				for (int j = 0; j < 15; j++)
					game[i][j] = 0;

			for (int i = 0; i < 225; i++)
				vecstep[i] = -50;
		}

		else if (game[x / 50][y / 50] == 0) {
			if (step % 2 == 1) {					//根据步数判断是黑棋还是白棋
													//setfillcolor(BLACK);
				game[x / 50][y / 50] = 1;
			}
			else if (step % 2 == 0) {
				//setfillcolor(WHITE);
				game[x / 50][y / 50] = -1;
			}
			vecstep[step] = Vecposition(x + 30, y + 70);
		}
		else step--;
	}
	

	cleardevice();							//清理屏幕
	/*area head("head");
	head.setheadline();				//写出连珠五子棋by李卓伦*/
	setline();
	setnumber();
	headleft.settext("重新开始", "center");
	headright.settext("主菜单", "center");
	righthead.setheadline();
	char x[10];
	sprintf_s(x, "%d", leavesNumber);
	outtextxy(400, 20, x);
	leavesNumber = 0;

	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 15; j++)
		{
			if(game[i][j]==1)
				setfillcolor(BLACK);
			else if(game[i][j]==-1)
				setfillcolor(WHITE);
			else continue;
			fillcircle(i * 50 + 30, j * 50 + 70, radius);		    //棋盘原点为（30，70）

		}
	for (int i = 1; i < 255; i++)
	{
		if (vecstep[i].getx() == -50 && vecstep[i].gety() == -50)
			break;
		else
		{
			char s[4];
			sprintf_s(s, "%d", i);
			outtextxy(vecstep[i].getx(), vecstep[i].gety(), s);
		}

			
	}
	check();					//检查是否胜利
}



void chess::check()			//检查是否胜利
{	
	int i, j;
	//横排检查
	for (i = 1; i < 16; i++)
		for (j = 1; j < 12; j++){
			if (game[i - 1][j - 1] != 0 &&
				game[i - 1][j] == game[i - 1][j - 1] &&
				game[i - 1][j + 1] == game[i - 1][j - 1] &&
				game[i - 1][j + 2] == game[i - 1][j - 1] &&
				game[i - 1][j + 3] == game[i - 1][j - 1])
				win = game[i - 1][j - 1];
		}
	//竖排检查
	for (j = 1; j < 16; j++)
		for (i = 1; i < 12; i++)
		{
			if (game[i - 1][j - 1] != 0 &&
				game[i][j - 1] == game[i - 1][j - 1] &&
				game[i + 1][j - 1] == game[i - 1][j - 1] &&
				game[i + 2][j - 1] == game[i - 1][j - 1] &&
				game[i + 3][j - 1] == game[i - 1][j - 1])
			{
				win = game[i - 1][j - 1];
			}
		}
	//右斜检查
	for (i = 1; i < 12; i++)
		for (j = 1; j < 12;j++)
			if (game[i - 1][j - 1] != 0 &&
				game[i][j] == game[i - 1][j - 1] &&
				game[i + 1][j + 1] == game[i - 1][j - 1] &&
				game[i + 2][j + 2] == game[i - 1][j - 1] &&
				game[i + 3][j + 3] == game[i - 1][j - 1])
			{
				win = game[i - 1][j - 1];
			}
	//左斜检查
	for (i = 1; i < 12; i++)
		for (j = 5; j < 16;j++)
			if (game[i - 1][j - 1] != 0 &&
				game[i][j - 2] == game[i - 1][j - 1] &&
				game[i + 1][j - 3] == game[i - 1][j - 1] &&
				game[i + 2][j - 4] == game[i - 1][j - 1] &&
				game[i + 3][j - 5] == game[i - 1][j - 1])
			{
				win = game[i - 1][j - 1];
			}
}

int chess::getx()	
{
	return x;
}

int chess::gety()
{
	return y;
}

int chess::getradius()
{
	return radius;
}