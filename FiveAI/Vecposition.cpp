#include "Vecposition.h"

Vecposition::Vecposition(int _x, int _y)
{
	x = _x;
	y = _y;
}

Vecposition ::~Vecposition()
{
}

int Vecposition::getx()
{
	return x;
}

int Vecposition::gety()
{
	return y;
}

void Vecposition::set()
{
	x++;
}
