#include "Shape.h"

#include <iostream>
#include <string.h>

void Shape::setFill(char const* _fill)
{
	int len = strlen(_fill) + 1;
	if (len < 50)
		strcpy_s(this->fill, len, _fill);
	else
		std::cout << "Too much length!";
}

void Shape::setStroke(char const* _stroke)
{
	int len = strlen(_stroke) + 1;
	if (len < 50)
		strcpy_s(this->stroke, len, _stroke);
	else
		std::cout << "Too much length!";
}

void Shape::setFillOpacity(double _fillOpacity) {
	this->fillOpacity = _fillOpacity;
}

void Shape::setStrokeOpacity(double _strokeOpacity) {
	this->strokeOpacity = _strokeOpacity;
}

void Shape::setStrokeWidth(int _strokeWidth) {
	this->strokeWidth = _strokeWidth;
}

Shape::Shape(const char* _fill, const char* _stroke, double _fillOpacity, double _strokeOpacity, int _strokeWith) {
	setFill(_fill);
	setStroke(_stroke);
	setFillOpacity(_fillOpacity);
	setStrokeOpacity(_strokeOpacity);
	setStrokeWidth(_strokeWith);
}

void Shape::print()const {
	std::cout << this->fill << " " <<
		this->stroke << " " <<
		this->fillOpacity << " " <<
		this->strokeOpacity << " " <<
		this->strokeWidth <<
		std::endl;
}



