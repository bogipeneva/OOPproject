#include "Circle.h"

#include<iostream>

Circle::Circle(int _r, int _cx, int _cy, const char* _fill, const char* _stroke, double _fillOpacity, double _strokeOpacity, int _strokeWith)
	:Shape(_fill, _stroke, _fillOpacity, _strokeOpacity, _strokeWith) {
	setR(_r);
	setCX(_cx);
	setCY(_cy);

}

void Circle::setR(int _r) {
	if (_r < 0) {
		std::cout << "Circle radius can not be negative!";
	}
	else
		this->r = _r;
}

void Circle::setCX(int _x) {
	this->cx = _x;
}

void Circle::setCY(int _y) {
	this->cy = _y;
}


void Circle::print()const {
	std::cout << "circle" << " " << this->r << " " << this->cx << " " << this->cy << " ";
	Shape::print();
}

void Circle::translate(int vertical, int horizontal) {
	setCX(this->cx + horizontal);
	setCY(this->cy + vertical);
}


