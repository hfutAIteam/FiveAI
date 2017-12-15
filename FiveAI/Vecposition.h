#pragma once
#include <iostream>
class Vecposition 
{
public:
	Vecposition(int _x = -50, int _y = -50);
	~Vecposition ();
	int getx();
	int gety();
	void set();
private:
	int x, y;
};


