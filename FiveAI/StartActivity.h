#pragma once
#include <graphics.h>
#include "area.h"
class StartActivity:public Listeningkeyboard
{
public:
	StartActivity();
	~StartActivity();
	Vecposition clickleft(MOUSEMSG msg);
private:
	area alltop = area("alltop");
	area allcenter = area("allcenter");
	area allbottom = area("allbottom");
};

