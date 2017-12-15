#include "models.h"

int game[15][15];
int win = 0;
bool aifirst = true;
string  model = "NULL";

void models::start()
{
	cleardevice();							//清理屏幕
	Vecposition chessposition;					//棋子点击部位
	Listeningkeyboard listenkeyboard;
	Interface face;								//棋盘界面

	area rightall("rightall");
	chess c(-50, -50);								//更新棋盘
	c.drawcircle();
	while (!win) {
		chessposition = face.getclick();
		chess c = chess(chessposition.getx(), chessposition.gety());
		c.drawcircle();
	}

	char s[100];
	if (win == 1)			sprintf_s(s, "blackwin");		//输出胜方
	else if (win == -1)		sprintf_s(s, "whitewin");
	rightall.settext(s, "center");

	for (; chessposition.getx() != -250;)
	{
		chessposition = face.getclick();
		if (chessposition.getx() == -150)
			break;
		else if (chessposition.getx() == -250)
			break;
	}
	chess humanchess = chess(chessposition.getx(), chessposition.gety());
	humanchess.drawcircle();
	win = 0;
	if (chessposition.getx() == -250)
	{
		model = "NULL";
		cleardevice();
	}
}

void models::aimodel()
{
	cleardevice();							//清理屏幕
	Vecposition chessposition;					//棋子点击部位
	Listeningkeyboard listenkeyboard;
	Interface face;								//棋盘界面

	area head("head");
	//head.setheadline();				//写出连珠五子棋by李卓伦
	//area rightall("rightall");
	AI ai;

	//设置先手后手
	{
		LOGFONT f;
		gettextstyle(&f);              //设置字体大小
		f.lfHeight = 30;
		f.lfQuality = ANTIALIASED_QUALITY;   //抗锯齿（虽然我也不知道什么用）
		settextstyle(&f);

		area alltop = area("alltop");
		area allbottom = area("allbottom");

		alltop.settext("我先下", "top");
		allbottom.settext("我后下", "top");


		gettextstyle(&f);
		f.lfHeight = 18;					//设置字体大小
		settextstyle(&f);

		bool stop = false;

		while (!stop)
		{
			if (MouseHit())
			{
				MOUSEMSG msg = GetMouseMsg();
				switch (msg.uMsg)
				{
				case WM_LBUTTONDOWN://左键按下 
					if (msg.x > (512 - 100) && msg.x<(512 + 100) && msg.y>(200) && msg.y < (300))
						aifirst = false;
					if (msg.x >(512 - 100) && msg.x<(512 + 100) && msg.y>(400) && msg.y < (500))
						aifirst = true;
					stop = true;
					break;
				default:
					break;
				}
			}
		}
		stop = false;
	}


	while (model == "fightAI")
	{
		cleardevice();
		face.setline();
		face.setnumber();

		clock_t start, finish;
		double duration;


		if (aifirst == true)
		{
			while (!win) {
				start = clock();

				chessposition = ai.aiselect();
				chess aichess = chess(chessposition.getx(), chessposition.gety());
				aichess.drawcircle();
				ai.showscore();

				finish = clock();

				duration = (double)(finish - start) / CLOCKS_PER_SEC; /*CLOCKS_PER_SEC，它用来表示一秒钟会有多少个时钟计时单元*/

				char x[10];
				sprintf_s(x, "%f", duration);
				outtextxy(200, 20, x);

				if (win)	break;

				do {
					chessposition = face.getclick();
					if (chessposition.getx() == -150)
						break;
					if (chessposition.getx() == -250)
						break;
				} while (game[chessposition.getx() / 50][chessposition.gety() / 50] != 0);

				chess humanchess = chess(chessposition.getx(), chessposition.gety());
				humanchess.drawcircle();
				if (chessposition.getx() == -250)	break;
			}
			char s[100];
			if (win == 1)			sprintf_s(s, "blackwin");
			else if (win == -1)		sprintf_s(s, "whitewin");
			head.settext(s, "center");


			for (; chessposition.getx() != -250;)
			{
				chessposition = face.getclick();
				if (chessposition.getx() == -150)
					break;
				else if (chessposition.getx() == -250)
					break;
			}
			chess humanchess = chess(chessposition.getx(), chessposition.gety());
			humanchess.drawcircle();

			win = 0;

			if (chessposition.getx() == -250)
			{
				model = "NULL";
				cleardevice();
			}
		}


		if (aifirst == false)
		{
			while (!win) {
				do {
					chessposition = face.getclick();
					if (chessposition.getx() == -150)
						break;
					if (chessposition.getx() == -250)
						break;
				} while (game[chessposition.getx() / 50][chessposition.gety() / 50] != 0);

				chess humanchess = chess(chessposition.getx(), chessposition.gety());
				humanchess.drawcircle();
				if (chessposition.getx() == -250)	break;

				if (win)	break;



				start = clock();

				chessposition = ai.aiselect();
				chess aichess = chess(chessposition.getx(), chessposition.gety());
				aichess.drawcircle();
				ai.showscore();

				finish = clock();

				duration = (double)(finish - start) / CLOCKS_PER_SEC; /*CLOCKS_PER_SEC，它用来表示一秒钟会有多少个时钟计时单元*/

				char x[10];
				sprintf_s(x, "%f", duration);
				outtextxy(200, 20, x);



			}
			char s[100];
			if (win == 1)			sprintf_s(s, "blackwin");
			else if (win == -1)		sprintf_s(s, "whitewin");
			head.settext(s, "center");

			for (; chessposition.getx() != -250;)
			{
				chessposition = face.getclick();
				if (chessposition.getx() == -150)
					break;
				else if (chessposition.getx() == -250)
					break;
			}
			chess humanchess = chess(chessposition.getx(), chessposition.gety());
			humanchess.drawcircle();

			win = 0;

			if (chessposition.getx() == -250)
			{
				model = "NULL";
				cleardevice();
			}
		}
	}
}
