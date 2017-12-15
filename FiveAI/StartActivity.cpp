#include "StartActivity.h"
#include "area.h"
#include <iostream>
extern string model;

StartActivity::StartActivity()
{
	LOGFONT f;
	gettextstyle(&f);              //设置字体大小
	f.lfHeight = 30;
	f.lfQuality = ANTIALIASED_QUALITY;   //抗锯齿（虽然我也不知道什么用）
	settextstyle(&f);

	alltop.settext("双人对战", "top");
	allcenter.settext("人机对战","top");
	allbottom.settext("退出游戏","top");

	gettextstyle(&f);
	f.lfHeight = 18;					//设置字体大小
	settextstyle(&f);
	
	while (model=="NULL")
	{
		getclick();
	}
}

StartActivity::~StartActivity()
{

}

Vecposition StartActivity::clickleft(MOUSEMSG msg)
{

	if (msg.x > (512 - 100) && msg.x<(512 + 100) && msg.y>(200) && msg.y < (300))   //点击双人对战
	{
		clearrectangle(0,0,480,70);
		model="doubleplay";
	}

	if (msg.x >(512 - 100) && msg.x<(512 + 100) && msg.y>(300) && msg.y < (400))     //if点击人机对战
	{
		


		model = "fightAI";
	}


	if (msg.x >(512 - 100) && msg.x<(512 + 100) && msg.y>(400) && msg.y < (500))   //点击结束游戏
	{
		cout<< "输入任意键盘结束程序" << endl;
		model="quit";			//退出游戏
               
	}
	return Vecposition();
}
