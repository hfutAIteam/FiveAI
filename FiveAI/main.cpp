
#include <iostream>
#include <stdio.h>
#include "models.h"
extern string model;
int main()
{
	models gamemodel;
	Background background;								//���������ɽ���
	StartActivity *startactivity;
	startactivity = new StartActivity;					//��ʼ����
	while (model!="quit")
	{
		if (model == "doubleplay")			//˫�˶�ս����
		{
			delete startactivity;
			startactivity = NULL;
			gamemodel.start();	
		}
		else if (model == "fightAI")       //AI����
		{
			delete startactivity;
			startactivity = NULL;
			gamemodel. aimodel();
		}
		if (model == "NULL")
		{
			StartActivity *startactivity;					//��ʼ����
			startactivity = new StartActivity;
		}
		
	}
	 if (model == "quit")					//ѡ���˳�
	{
		delete startactivity;
		startactivity = NULL;
		closegraph();
	}
	
}
