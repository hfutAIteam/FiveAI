#include "Listeningkeyboard.h"
#include <graphics.h>
#include <iostream>
#include "Vecposition.h"
Listeningkeyboard::Listeningkeyboard()
{
}

Listeningkeyboard::~Listeningkeyboard()
{
}
Vecposition Listeningkeyboard::getclick()      //�����������
{
	if (MouseHit())
	{
		MOUSEMSG msg = GetMouseMsg();
		switch (msg.uMsg)
		{
		case WM_LBUTTONDOWN://������� 
			clickleft(msg);
			break;
		case WM_RBUTTONDOWN://�Ҽ�����
			clickright(msg);
			break;
		default:
			break;
		}
	}
	Sleep(5);
	return Vecposition();
}
Vecposition Listeningkeyboard::clickleft(MOUSEMSG msg) { return Vecposition(); }

void Listeningkeyboard::clickright(MOUSEMSG msg){}

