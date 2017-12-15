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
	int getradius();	//返回半径
	void drawcircle();   //下棋
	void clickleft();     //点击一下就下棋
	void drawcheck();    //下棋之前检查一下
	virtual void check();  // 检查是否满足胜利条件
	int getx();
	int gety();


private:
	const int radius = 20 ;
	int x, y;


};

