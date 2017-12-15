
#include <iostream>
#include <stdio.h>
#include "models.h"
extern string model;
int main()
{
	models gamemodel;
	Background background;								//背景与生成界面
	StartActivity *startactivity;
	startactivity = new StartActivity;					//开始界面
	while (model!="quit")
	{
		if (model == "doubleplay")			//双人对战界面
		{
			delete startactivity;
			startactivity = NULL;
			gamemodel.start();	
		}
		else if (model == "fightAI")       //AI界面
		{
			delete startactivity;
			startactivity = NULL;
			gamemodel. aimodel();
		}
		if (model == "NULL")
		{
			StartActivity *startactivity;					//开始界面
			startactivity = new StartActivity;
		}
		
	}
	 if (model == "quit")					//选择退出
	{
		delete startactivity;
		startactivity = NULL;
		closegraph();
	}
	
}
