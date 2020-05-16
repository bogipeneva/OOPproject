#ifndef _RECTANGLE_H
#define _RECTANGLE_H

#include "Shape.h"
class Rectangle :
	public Shape
{
private:
	int x;
	int y;
	int width;
	int height;

public:
	//constructors
	Rectangle(int _x = 1, int _y = 1, int _width = 2, int _height =1, const char* _fill = "");
	
	//setters
	void setX(int);
	void setY(int);
	void setWidth(int);
	void setHeight(int);

	//getters
	int getX()const { return x; };
	int getY()const { return y; };
	int getWidth()const { return width; };
	int getHeight()const { return height; };
	char* getShapeType()const { return "rectangle"; };

	void print()const;
	void translate(int, int);
	bool withinRectangle(int, int, int, int);
	bool withinCircle(int, int, int);
};
#endif
