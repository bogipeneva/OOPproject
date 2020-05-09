#include "Ellipse.h"

#include<iostream>



Ellipse::Ellipse(int _rx, int _ry, int _cx, int _cy, const char* _fill)
	:Shape(_fill) {
	setRX(_rx);
	setRY(_ry);
	setCX(_cx);
	setCY(_cy);

}

void Ellipse::setRX(int _rx) {
	if (_rx < 0) {
		std::cout << "Ellipse radius can not be negative!";
	}
	else
		this->rx = _rx;
}

void Ellipse::setRY(int _ry) {
	if (_ry < 0) {
		std::cout << "Ellipse radius can not be negative!";
	}
	else
		this->ry = _ry;
}

void Ellipse::setCX(int _x) {
	this->cx = _x;
}

void Ellipse::setCY(int _y) {
	this->cy = _y;
}


void Ellipse::print()const {
	std::cout << "ellipse" << " " << this->rx << " " << this->ry << " " << this->cx << " " << this->cy << " ";
	Shape::print();
}

void Ellipse::translate(int vertical, int horizontal) {
	setCX(this->cx + horizontal);
	setCY(this->cy + vertical);
}
