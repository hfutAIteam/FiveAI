#pragma once
#include<graphics.h>
#include"Listeningkeyboard.h"
#include "Interface.h"
#include "area.h"
#include "AI.h"
class chess :public Interface
{
public:
	chess(int _x = -50, int _y = -50);
	~chess();
	int getradius();	//���ذ뾶
	void drawcircle();   //����
	void clickleft();     //���һ�¾�����
	void drawcheck();    //����֮ǰ���һ��
	virtual void check();  // ����Ƿ�����ʤ������
	int getx();
	int gety();


private:
	const int radius = 20 ;
	int x, y;


};

