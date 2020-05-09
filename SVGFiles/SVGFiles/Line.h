#pragma once
#include "Shape.h"
class Line :
	public Shape
{
private:
	int x1;
	int y1;
	int x2;
	int y2;

public:
	//constructors
	Line(int _x1 = 1, int _y1 = 1, int _x2 = 2, int _y2 = 1, const char* _fill = "");

	//setters
	void setX1(int);
	void setY1(int);
	void setX2(int);
	void setY2(int);

	//getters
	int getX1()const { return x1; };
	int getY1()const { return y1; };
	int getX2()const { return x2; };
	int getY2()const { return y2; };

	void print()const;
	void translate(int, int);
};

