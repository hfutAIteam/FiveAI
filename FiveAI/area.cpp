#include "area.h"
#include <graphics.h>
#include <string>
#include <iostream>
#include "Vecposition.h"
using namespace std;
area::area(string type)                   /*把需要用的区域提前规划出来方面以后的使用*/
{
	if (type == "head") { x1 = 0; y1 = 0; x2 = 680; y2 = 70; }  //head标题
	else if (type == "headleft") { x1 = 0; y1 = 0; x2 = 200; y2 = 50; }
	else if (type == "headright") { x1 = 480; y1 = 0; x2 = 680; y2 = 50; }

	else if (type == "rightall") { x1 = 680; y1 = 0; x2 = 1024; y2 = 750; }    //右方所有地方
	else if (type == "top") { x1 = 680; y1 = 0; x2 = 1024; y2 = 100; }//右方上面
	else if (type == "bottom") { x1 = 680; y1 = 650; x2 = 1024; y2 = 750; }//右方下面
	else if (type == "center") { x1 = 680; y1 = 300; x2 = 1024; y2 = 400; }//右方中间

	else if (type == "alltop") { x1 = 512 - 100; y1 = 200; x2 = 512 + 100; y2 = 300; }				//1024, 750
	else if (type == "allcenter") { x1 = 512 - 100; y1 = 300; x2 = 512 + 100; y2 = 400; }
	else if (type == "allbottom") { x1 = 512 - 100; y1 = 400; x2 = 512 + 100; y2 = 500; }//这三个用于开始界面三个选项
	else if (type == "righthead") { x1 = 500; y1 = 0; x2 = 2000; y2 = 50; }
	normal = { x1,y1,x2,y2 };
}


area::~area()
{

}

Vecposition area::clickleft(MOUSEMSG msg)			//确认点击的是区域内的部位
{
	if (msg.x > (x1 - 10) && msg.x<(x2 + 10) && msg.y>(y1 - 10) && msg.y < (y2 + 10))
	{
		settext(" has click","bonttom");
	}
	return Vecposition();
}

void area::clickright(MOUSEMSG msg)
{

}

void area::setheadline()
{
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 30;
	settextstyle(&f);
	drawtext("连珠五子棋by李卓伦", &normal, DT_CENTER);
}



void area::settext(char c[], string type)
{
	if(type=="top")
		drawtext(c, &normal, DT_CENTER | DT_TOP);
	if (type == "bonttom")
		drawtext(c, &normal, DT_CENTER | DT_BOTTOM | DT_SINGLELINE);
	if(type=="center")
		drawtext(c, &normal, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}



RECT area::getrect()
{
	return normal;
}
