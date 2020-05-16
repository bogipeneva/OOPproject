#include "Circle.h"

#include<iostream>
#include<math.h>

Circle::Circle(int _r, int _cx, int _cy, const char* _fill)
	:Shape(_fill) {
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

bool Circle::withinRectangle(int rectX, int rectY, int rectWidth, int rectHeight) {
	return this->cx - this->r >= rectX 
		&& this->cy - this->r >= rectY 
		&& this->cx + this->r <= rectX + rectWidth 
		&& this->cy + this->r <= rectY + rectHeight;
}

bool Circle::withinCircle(int radius, int x, int y) {
	bool circleCenterIsInCircle = 
		sqrt((this->cx - x)*(this->cx - x) + (this->cy - y)*(this->cy - y)) <= radius;
	return circleCenterIsInCircle
		&& this->cx + this->r <= x + radius
		&& this->cx - this->r >= x - radius
		&& this->cy + this->r <= y + radius
		&& this->cy - this->r >= y - radius;
}

