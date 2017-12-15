#pragma once
#include<graphics.h>
#include "Vecposition.h"
class Listeningkeyboard
{
public:
	Listeningkeyboard();
	~Listeningkeyboard();
	virtual Vecposition getclick();
	virtual Vecposition clickleft(MOUSEMSG msg);
	virtual void clickright(MOUSEMSG msg);
private:

};

