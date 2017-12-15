#include "Interface.h"

extern int game[15][15];
Interface::Interface()
{

}

Interface:: ~Interface ()
{
}


void Interface::setline()     //画线
{
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 20;
	settextstyle(&f);

	
	setcolor(BLACK);
	for (int i = 70; i <= 770; i += 50)
		line(30, i, 730, i);
	for (int j = 30; j <= 730; j += 50)
		line(j, 70, j, 770);

	gettextstyle(&f);
	f.lfHeight = 30;
	settextstyle(&f);
}

void Interface::setnumber()       //标识数字与字母
{
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 20;
	settextstyle(&f);


	int i, j;
	setcolor(BLACK);
	for (i = 1; i < 16; i++)        
	{
		char  num[5];
		sprintf_s(num, "%d", i);
		outtextxy(10, 770 - 50 * (i - 1), num);
	}
	for (j = 1; j < 16; j++)
	{
		char algbra[5];
		char x = (char)(j+64);
		sprintf_s(algbra, "%c", x);
		outtextxy(20 + 50 * (j - 1), 780, algbra);
	}

	gettextstyle(&f);
	f.lfHeight = 30;
	settextstyle(&f);


}

Vecposition Interface::getclick()        //重写getclick
{
	Vecposition vec;
	
		do 
		{
			if (MouseHit())
			{
			MOUSEMSG msg = GetMouseMsg();
			switch (msg.uMsg)
			{
			case WM_LBUTTONDOWN://左键按下 
				vec = clickleft(msg);
				break;
			case WM_RBUTTONDOWN://右键按下
				clickright(msg);
				break;
			default:
				break;
			}
		}
		} while (vec.getx() == -50);
		
	
		//Sleep(5);
		return Vecposition(vec.getx(),vec.gety());
}

Vecposition Interface::clickleft(MOUSEMSG msg)
{
	int x, y;
	if (msg.x > 20 && msg.x < 730 && msg.y>60 && msg.y < 780)   //四舍五入近似获取点击部位
	{
		x = (msg.x-30 + 25) / 50 * 50;
		y = (msg.y-70 + 25) / 50 * 50;
		return Vecposition(x, y);
	}			
	else if (msg.x < 200 && msg.x>0 && msg.y > 0 && msg.y < 50)			//点击部位为重新开始
	{

		return Vecposition(-150, -150);
	}

	else if (msg.x < 680 && msg.x>480 && msg.y > 0 && msg.y < 50)		//点击部位为主菜单
	{

		return Vecposition(-250, -250);
	}
	//else if (msg.x > 1500)return Vecposition(-100, 0);		//x>1500则执行其他指令
	else return Vecposition(-50, -50);				//x棋盘范围=30-730    y棋盘范围=70-770
}






