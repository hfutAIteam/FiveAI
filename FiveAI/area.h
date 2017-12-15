#pragma once
#include <graphics.h>
#include <string>
#include "Listeningkeyboard.h"
using namespace std;
class area: public Listeningkeyboard 
{
public:
	area(string type);
	~area();
	Vecposition clickleft(MOUSEMSG msg);
	void clickright(MOUSEMSG msg);
	void setheadline();
	void settext(char c[], string type);
	RECT getrect();
private:
	int x1, x2, y1, y2;
	RECT normal ;
	string typ;

};


