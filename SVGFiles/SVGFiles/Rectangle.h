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
	Rectangle(int _x = 1, int _y = 1, int _width = 2, int _height =1, const char* _fill = "", const char* _stroke = "", double _fillOpacity = 0, double _strokeOpacity = 0, int _strokeWith = 20);
	
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

	void print()const;
	void translate(int, int);
};
#endif
