#pragma once
#include<graphics.h>
#include<stdlib.h>
#include<conio.h>
#include<iostream>
#include<stdio.h>
#include "Vecposition.h"
#include "area.h"

class Interface: public Listeningkeyboard
{
public:
	 Interface();
	 ~Interface();
	 void setline();
	 void setnumber();
	 Vecposition getclick();
	 Vecposition clickleft(MOUSEMSG msg);
	 
private:


};

