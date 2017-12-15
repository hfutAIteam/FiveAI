#include "models.h"

int game[15][15];
int win = 0;
bool aifirst = true;
string  model = "NULL";

void models::start()
{
	cleardevice();							//������Ļ
	Vecposition chessposition;					//���ӵ����λ
	Listeningkeyboard listenkeyboard;
	Interface face;								//���̽���

	area rightall("rightall");
	chess c(-50, -50);								//��������
	c.drawcircle();
	while (!win) {
		chessposition = face.getclick();
		chess c = chess(chessposition.getx(), chessposition.gety());
		c.drawcircle();
	}

	char s[100];
	if (win == 1)			sprintf_s(s, "blackwin");		//���ʤ��
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
	cleardevice();							//������Ļ
	Vecposition chessposition;					//���ӵ����λ
	Listeningkeyboard listenkeyboard;
	Interface face;								//���̽���

	area head("head");
	//head.setheadline();				//д������������by��׿��
	//area rightall("rightall");
	AI ai;

	//�������ֺ���
	{
		LOGFONT f;
		gettextstyle(&f);              //���������С
		f.lfHeight = 30;
		f.lfQuality = ANTIALIASED_QUALITY;   //����ݣ���Ȼ��Ҳ��֪��ʲô�ã�
		settextstyle(&f);

		area alltop = area("alltop");
		area allbottom = area("allbottom");

		alltop.settext("������", "top");
		allbottom.settext("�Һ���", "top");


		gettextstyle(&f);
		f.lfHeight = 18;					//���������С
		settextstyle(&f);

		bool stop = false;

		while (!stop)
		{
			if (MouseHit())
			{
				MOUSEMSG msg = GetMouseMsg();
				switch (msg.uMsg)
				{
				case WM_LBUTTONDOWN://������� 
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

				duration = (double)(finish - start) / CLOCKS_PER_SEC; /*CLOCKS_PER_SEC����������ʾһ���ӻ��ж��ٸ�ʱ�Ӽ�ʱ��Ԫ*/

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

				duration = (double)(finish - start) / CLOCKS_PER_SEC; /*CLOCKS_PER_SEC����������ʾһ���ӻ��ж��ٸ�ʱ�Ӽ�ʱ��Ԫ*/

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
