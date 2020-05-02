#include "Line.h"
#include<iostream>

Line::Line(int _x1, int _y1, int _x2, int _y2, const char* _fill, const char* _stroke, double _fillOpacity, double _strokeOpacity, int _strokeWith)
	:Shape(_fill, _stroke, _fillOpacity, _strokeOpacity, _strokeWith) {
	setX1(_x1);
	setY1(_y1);
	setX2(_x2);
	setY2(_y2);
}

void Line::setX1(int _x1) {
	this->x1 = _x1;
}

void Line::setY1(int _y1) {
	this->y1 = _y1;
}

void Line::setX2(int _x2) {
	this->x2 = _x2;
}

void Line::setY2(int _y2) {
	this->y2 = _y2;
}
void Line::print()const {
	std::cout << "Line" << " " << this->x1 << " " << this->y1 << " " << this->x2 << " " << this->y2 << " ";
	Shape::print();
}

void Line::translate(int vertical, int horizontal) {
	setX1(this->x1 + horizontal);
	setY1(this->y1 + vertical);
	setX2(this->x2 + horizontal);
	setY2(this->y2 + vertical);
}
