#include "StartActivity.h"
#include "area.h"
#include <iostream>
extern string model;

StartActivity::StartActivity()
{
	LOGFONT f;
	gettextstyle(&f);              //���������С
	f.lfHeight = 30;
	f.lfQuality = ANTIALIASED_QUALITY;   //����ݣ���Ȼ��Ҳ��֪��ʲô�ã�
	settextstyle(&f);

	alltop.settext("˫�˶�ս", "top");
	allcenter.settext("�˻���ս","top");
	allbottom.settext("�˳���Ϸ","top");

	gettextstyle(&f);
	f.lfHeight = 18;					//���������С
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

	if (msg.x > (512 - 100) && msg.x<(512 + 100) && msg.y>(200) && msg.y < (300))   //���˫�˶�ս
	{
		clearrectangle(0,0,480,70);
		model="doubleplay";
	}

	if (msg.x >(512 - 100) && msg.x<(512 + 100) && msg.y>(300) && msg.y < (400))     //if����˻���ս
	{
		


		model = "fightAI";
	}


	if (msg.x >(512 - 100) && msg.x<(512 + 100) && msg.y>(400) && msg.y < (500))   //���������Ϸ
	{
		cout<< "����������̽�������" << endl;
		model="quit";			//�˳���Ϸ
               
	}
	return Vecposition();
}
