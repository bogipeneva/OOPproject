#ifndef _ELLIPSE_H
#define _ELLIPSE_H

#include "Shape.h"
class Ellipse :
	public Shape
{
private:
	int rx;
	int ry;
	int cx;
	int cy;

public:
	//constructors
	Ellipse(int rx = 1, int ry = 1, int _cx = 1, int _cy = 1, const char* _fill = "", const char* _stroke = "", double _fillOpacity = 0, double _strokeOpacity = 0, int _strokeWith = 20);

	//setters
	void setRX(int);
	void setRY(int);
	void setCX(int);
	void setCY(int);


	//getters
	int getRX()const { return rx; };
	int getRY()const { return ry; }
	int getCX()const { return cx; };
	int getCY()const { return cy; };

	void print()const;
	void translate(int, int);
};

#endif
