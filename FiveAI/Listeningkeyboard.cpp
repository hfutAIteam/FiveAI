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
Vecposition Listeningkeyboard::getclick()      //基类监听函数
{
	if (MouseHit())
	{
		MOUSEMSG msg = GetMouseMsg();
		switch (msg.uMsg)
		{
		case WM_LBUTTONDOWN://左键按下 
			clickleft(msg);
			break;
		case WM_RBUTTONDOWN://右键按下
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

