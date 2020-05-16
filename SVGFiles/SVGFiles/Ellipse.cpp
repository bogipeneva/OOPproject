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

bool Ellipse::withinRectangle(int rectX, int rectY, int rectWidth, int rectHeight) {
	return this->cx - this->rx >= rectX
		&& this->cy - this->ry >= rectY
		&& this->cx + this->rx <= rectX + rectWidth
		&& this->cy + this->ry <= rectY + rectHeight;
}

bool Ellipse::withinCircle(int radius, int x, int y) {
	bool circleCenterIsInCircle =
		sqrt((this->cx - x)*(this->cx - x) + (this->cy - y)*(this->cy - y)) <= radius;
	return circleCenterIsInCircle
		&& this->cx + this->rx <= x + radius
		&& this->cx - this->rx >= x - radius
		&& this->cy + this->ry <= y + radius
		&& this->cy - this->ry >= y - radius;
}