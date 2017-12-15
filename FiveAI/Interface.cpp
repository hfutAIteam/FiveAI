#include "Interface.h"

extern int game[15][15];
Interface::Interface()
{

}

Interface:: ~Interface ()
{
}


void Interface::setline()     //����
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

void Interface::setnumber()       //��ʶ��������ĸ
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

Vecposition Interface::getclick()        //��дgetclick
{
	Vecposition vec;
	
		do 
		{
			if (MouseHit())
			{
			MOUSEMSG msg = GetMouseMsg();
			switch (msg.uMsg)
			{
			case WM_LBUTTONDOWN://������� 
				vec = clickleft(msg);
				break;
			case WM_RBUTTONDOWN://�Ҽ�����
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
	if (msg.x > 20 && msg.x < 730 && msg.y>60 && msg.y < 780)   //����������ƻ�ȡ�����λ
	{
		x = (msg.x-30 + 25) / 50 * 50;
		y = (msg.y-70 + 25) / 50 * 50;
		return Vecposition(x, y);
	}			
	else if (msg.x < 200 && msg.x>0 && msg.y > 0 && msg.y < 50)			//�����λΪ���¿�ʼ
	{

		return Vecposition(-150, -150);
	}

	else if (msg.x < 680 && msg.x>480 && msg.y > 0 && msg.y < 50)		//�����λΪ���˵�
	{

		return Vecposition(-250, -250);
	}
	//else if (msg.x > 1500)return Vecposition(-100, 0);		//x>1500��ִ������ָ��
	else return Vecposition(-50, -50);				//x���̷�Χ=30-730    y���̷�Χ=70-770
}






