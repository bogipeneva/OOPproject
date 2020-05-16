#ifndef _CIRCLE_H
#define _CIRCLE_H

#include "Shape.h"

class Circle :
	public Shape
{
private:
	int r;
	int cx;
	int cy;

public:
	//constructors
	Circle(int r=1, int _cx = 1, int _cy = 1, const char* _fill = "");

	//setters
	void setR(int);
	void setCX(int);
	void setCY(int);


	//getters
	int getR()const { return r; };
	int getCX()const { return cx; };
	int getCY()const { return cy; };
	char* getShapeType()const { return "circle"; };

	void print()const;
    void translate(int, int);
	bool withinRectangle(int, int, int, int);
	bool withinCircle(int, int, int);

};

#endif

